/*******************************************************************************
**
**      GSC-18128-1, "Core Flight Executive Version 6.6"
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
** File: ci_lab_app.h
**
** Purpose:
**   This file is main hdr file for the Command Ingest lab application.
**
*******************************************************************************/

#ifndef _ci_lab_app_h_
#define _ci_lab_app_h_

/*
** Required header files...
*/
#include "network_includes.h"
#include "common_types.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include "osapi.h"
#include "ccsds.h"

#include <string.h>
#include <errno.h>
#include <unistd.h>

/****************************************************************************/

#define cfgCI_PORT                      1234
#define CI_MAX_INGEST                    768
#define CI_PIPE_DEPTH                     32

/************************************************************************
** Type Definitions
*************************************************************************/
typedef struct
{
    uint8   Octet1;
    uint16  PDataLen;
    uint8   Octet4;
    uint16  SrcEntityId;
    uint32  TransSeqNum;
    uint16  DstEntityId;

}OS_PACK CF_PDU_Hdr_t;

/****************************************************************************/
/*
** Local function prototypes...
**
** Note: Except for the entry point (CI_task_main), these
**       functions are not called from any other source module.
*/
void CI_task_main(void);
void CI_TaskInit(void);
void CI_ProcessCommandPacket(void);
void CI_ProcessGroundCommand(void);
void CI_ReportHousekeeping(void);
void CI_ResetCounters(void);
void CI_ModifyFileSizeCmd(CFE_SB_MsgPtr_t msg);
void CI_CorruptChecksumCmd(CFE_SB_MsgPtr_t msg);
void CI_DropPDUCmd(CFE_SB_MsgPtr_t msg);
void CI_CapturePDUsCmd(CFE_SB_MsgPtr_t msg);
void CI_StopPDUCaptureCmd(CFE_SB_MsgPtr_t msg);
void CI_ProcessPDU(void);
void CI_ReadUpLink(void);

bool CI_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);

#endif /* _ci_lab_app_h_ */
