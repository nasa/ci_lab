/*******************************************************************************
**
**      GSC-18128-1, "Core Flight Executive Version 6.7"
**
**      Copyright (c) 2006-2019 United States Government as represented by
**      the Administrator of the National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      Licensed under the Apache License, Version 2.0 (the "License");
**      you may not use this file except in compliance with the License.
**      You may obtain a copy of the License at
**
**        http://www.apache.org/licenses/LICENSE-2.0
**
**      Unless required by applicable law or agreed to in writing, software
**      distributed under the License is distributed on an "AS IS" BASIS,
**      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**      See the License for the specific language governing permissions and
**      limitations under the License.
**
** File: ci_lab_app.c
**
** Purpose:
**   This file contains the source code for the Command Ingest task.
**
*******************************************************************************/

/*
**   Include Files:
*/

#include "ci_lab_app.h"
#include "ci_lab_perfids.h"
#include "ci_lab_msgids.h"
#include "ci_lab_msg.h"
#include "ci_lab_events.h"
#include "ci_lab_version.h"

/*
** CI global data...
*/

bool               CI_SocketConnected = false;
ci_hk_tlm_t        CI_HkTelemetryPkt;
CFE_SB_PipeId_t    CI_CommandPipe;
CFE_SB_MsgPtr_t    CIMsgPtr;
int                CI_SocketID;
struct sockaddr_in CI_SocketAddress;
uint8              CI_IngestBuffer[CI_MAX_INGEST];
CFE_SB_Msg_t *     CI_IngestPointer = (CFE_SB_Msg_t *)&CI_IngestBuffer[0];

static CFE_EVS_BinFilter_t CI_EventFilters[] = {/* Event ID    mask */
                                                {CI_SOCKETCREATE_ERR_EID, 0x0000}, {CI_SOCKETBIND_ERR_EID, 0x0000},
                                                {CI_STARTUP_INF_EID, 0x0000},      {CI_COMMAND_ERR_EID, 0x0000},
                                                {CI_COMMANDNOP_INF_EID, 0x0000},   {CI_COMMANDRST_INF_EID, 0x0000},
                                                {CI_INGEST_INF_EID, 0x0000},       {CI_INGEST_ERR_EID, 0x0000}};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* CI_Lab_AppMain() -- Application entry point and main process loop          */
/* Purpose: This is the Main task event loop for the Command Ingest Task      */
/*            The task handles all interfaces to the data system through      */
/*            the software bus. There is one pipeline into this task          */
/*            The task is sceduled by input into this pipeline.               */
/*            It can receive Commands over this pipeline                      */
/*            and acts accordingly to process them.                           */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void CI_Lab_AppMain(void)
{
    int32  status;
    uint32 RunStatus = CFE_ES_RunStatus_APP_RUN;

    CFE_ES_PerfLogEntry(CI_MAIN_TASK_PERF_ID);

    CI_TaskInit();

    /*
    ** CI Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == true)
    {
        CFE_ES_PerfLogExit(CI_MAIN_TASK_PERF_ID);

        /* Pend on receipt of command packet -- timeout set to 500 millisecs */
        status = CFE_SB_RcvMsg(&CIMsgPtr, CI_CommandPipe, 500);

        CFE_ES_PerfLogEntry(CI_MAIN_TASK_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            CI_ProcessCommandPacket();
        }

        /* Regardless of packet vs timeout, always process uplink queue      */
        if (CI_SocketConnected)
        {
            CI_ReadUpLink();
        }
    }

    CFE_ES_ExitApp(RunStatus);

} /* End of CI_Lab_AppMain() */

/*
** CI delete callback function.
** This function will be called in the event that the CI app is killed.
** It will close the network socket for CI
*/
void CI_delete_callback(void)
{
    OS_printf("CI delete callback -- Closing CI Network socket.\n");
    close(CI_SocketID);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* CI_TaskInit() -- CI initialization                                         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CI_TaskInit(void)
{
    CFE_ES_RegisterApp();

    CFE_EVS_Register(CI_EventFilters, sizeof(CI_EventFilters) / sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_EventFilter_BINARY);

    CFE_SB_CreatePipe(&CI_CommandPipe, CI_PIPE_DEPTH, "CI_LAB_CMD_PIPE");
    CFE_SB_Subscribe(CI_LAB_CMD_MID, CI_CommandPipe);
    CFE_SB_Subscribe(CI_LAB_SEND_HK_MID, CI_CommandPipe);

    if ((CI_SocketID = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        CFE_EVS_SendEvent(CI_SOCKETCREATE_ERR_EID, CFE_EVS_EventType_ERROR, "CI: create socket failed = %d", errno);
    }
    else
    {
        memset(&CI_SocketAddress, 0, sizeof(CI_SocketAddress));
        CI_SocketAddress.sin_family      = AF_INET;
        CI_SocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        CI_SocketAddress.sin_port        = htons(cfgCI_PORT);

        if ((bind(CI_SocketID, (struct sockaddr *)&CI_SocketAddress, sizeof(CI_SocketAddress)) < 0))
        {
            CFE_EVS_SendEvent(CI_SOCKETBIND_ERR_EID, CFE_EVS_EventType_ERROR, "CI: bind socket failed = %d", errno);
        }
        else
        {
            CI_SocketConnected = true;
#ifdef _HAVE_FCNTL_
            /*
            ** Set the socket to non-blocking
            ** This is not available to vxWorks, so it has to be
            ** Conditionally compiled in
            */
            fcntl(CI_SocketID, F_SETFL, O_NONBLOCK);
#endif
        }
    }

    CI_ResetCounters();

    /*
    ** Install the delete handler
    */
    OS_TaskInstallDeleteHandler(&CI_delete_callback);

    CFE_SB_InitMsg(&CI_HkTelemetryPkt, CI_LAB_HK_TLM_MID, CI_LAB_HK_TLM_LNGTH, true);

    CFE_EVS_SendEvent(CI_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION, "CI Lab Initialized.  Version %d.%d.%d.%d",
                      CI_LAB_MAJOR_VERSION, CI_LAB_MINOR_VERSION, CI_LAB_REVISION, CI_LAB_MISSION_REV);

} /* End of CI_TaskInit() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  CI_ProcessCommandPacket                                            */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the CI command*/
/*     pipe. The packets received on the CI command pipe are listed here:     */
/*                                                                            */
/*        1. NOOP command (from ground)                                       */
/*        2. Request to reset telemetry counters (from ground)                */
/*        3. Request for housekeeping telemetry packet (from HS task)         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void CI_ProcessCommandPacket(void)
{
    CFE_SB_MsgId_t MsgId;
    MsgId = CFE_SB_GetMsgId(CIMsgPtr);

    switch (MsgId)
    {
        case CI_LAB_CMD_MID:
            CI_ProcessGroundCommand();
            break;

        case CI_LAB_SEND_HK_MID:
            CI_ReportHousekeeping();
            break;

        default:
            CI_HkTelemetryPkt.ci_command_error_count++;
            CFE_EVS_SendEvent(CI_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR, "CI: invalid command packet,MID = 0x%x",
                              MsgId);
            break;
    }

    return;

} /* End CI_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CI_ProcessGroundCommand() -- CI ground commands                            */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void CI_ProcessGroundCommand(void)
{
    uint16 CommandCode;

    CommandCode = CFE_SB_GetCmdCode(CIMsgPtr);

    /* Process "known" CI task ground commands */
    switch (CommandCode)
    {
        case CI_NOOP_CC:
            CI_HkTelemetryPkt.ci_command_count++;
            CFE_EVS_SendEvent(CI_COMMANDNOP_INF_EID, CFE_EVS_EventType_INFORMATION, "CI: NOOP command");
            break;

        case CI_RESET_COUNTERS_CC:
            CI_ResetCounters();
            break;

        /* default case already found during FC vs length test */
        default:
            break;
    }

    return;

} /* End of CI_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  CI_ReportHousekeeping                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the CI task  */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void CI_ReportHousekeeping(void)
{
    CI_HkTelemetryPkt.SocketConnected = CI_SocketConnected;
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *)&CI_HkTelemetryPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *)&CI_HkTelemetryPkt);
    return;

} /* End of CI_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  CI_ResetCounters                                                   */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void CI_ResetCounters(void)
{
    /* Status of commands processed by CI task */
    CI_HkTelemetryPkt.ci_command_count       = 0;
    CI_HkTelemetryPkt.ci_command_error_count = 0;

    /* Status of packets ingested by CI task */
    CI_HkTelemetryPkt.IngestPackets = 0;
    CI_HkTelemetryPkt.IngestErrors  = 0;

    CFE_EVS_SendEvent(CI_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION, "CI: RESET command");
    return;

} /* End of CI_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CI_ReadUpLink() --                                                         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void CI_ReadUpLink(void)
{
    socklen_t addr_len;
    int       i;
    int       status;

    addr_len = sizeof(CI_SocketAddress);

    memset(&CI_SocketAddress, 0, sizeof(CI_SocketAddress));

    for (i = 0; i <= 10; i++)
    {
        status = recvfrom(CI_SocketID, (char *)&CI_IngestBuffer[0], sizeof(CI_IngestBuffer), MSG_DONTWAIT,
                          (struct sockaddr *)&CI_SocketAddress, &addr_len);

        if ((status < 0) && (errno == EWOULDBLOCK))
            break; /* no (more) messages */
        else
        {
            if (status <= CI_MAX_INGEST)
            {
				CFE_ES_PerfLogEntry(CI_SOCKET_RCV_PERF_ID);
				CI_HkTelemetryPkt.IngestPackets++;
				CFE_SB_SendMsg(CI_IngestPointer);
				CFE_ES_PerfLogExit(CI_SOCKET_RCV_PERF_ID);
            }
            else
            {
                CI_HkTelemetryPkt.IngestErrors++;
            }
        }
    }

    return;

} /* End of CI_ReadUpLink() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* CI_VerifyCmdLength() -- Verify command packet length                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool CI_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
{
    bool   result       = true;
    uint16 ActualLength = CFE_SB_GetTotalMsgLength(msg);

    /*
    ** Verify the command packet length...
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID   = CFE_SB_GetMsgId(msg);
        uint16         CommandCode = CFE_SB_GetCmdCode(msg);

        CFE_EVS_SendEvent(CI_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "Invalid msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d", MessageID, CommandCode,
                          ActualLength, ExpectedLength);
        result = false;
        CI_HkTelemetryPkt.ci_command_error_count++;
    }

    return (result);

} /* End of CI_VerifyCmdLength() */
