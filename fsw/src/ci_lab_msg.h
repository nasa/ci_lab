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
** File: ci_lab_msg.h
**
** Purpose: 
**  Define CI Lab Messages and info
**
** Notes:
**
*******************************************************************************/
#ifndef _ci_lab_msg_h_
#define _ci_lab_msg_h_

/*
** CI_Lab command codes
*/
#define CI_NOOP_CC                 0
#define CI_RESET_COUNTERS_CC       1
#define CI_MODIFY_PDU_FILESIZE_CC  2
#define CI_CORRUPT_PDU_CHECKSUM_CC 3
#define CI_DROP_PDUS_CC            4
#define CI_CAPTURE_PDUS_CC         5
#define CI_STOP_PDU_CAPTURE_CC     6

/*************************************************************************/
/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
   uint8          CmdHeader[CFE_SB_CMD_HDR_SIZE];

} CI_NoArgsCmd_t;

/*
** Type definition (Capture PDUs command structure)
*/
typedef struct
{
   uint8          CmdHeader[CFE_SB_CMD_HDR_SIZE];
   CFE_SB_MsgId_t PDUMsgID;  /* Message ID of the downlinked PDUs to capture */

} CI_CapturePDUCmd_t;

/*
** Type definition (Modify PDU file size command structure)
*/
typedef struct
{
   uint8	CmdHeader[CFE_SB_CMD_HDR_SIZE];
   uint16	Direction;  /* Add or Subtract */
   uint16	Amount;     /* The value to add or subtract from the file size*/

} CI_ModifyFileSizeCmd_t;

/*
** Type definition (Drop PDU command structure)
*/
typedef struct
{
   uint8	CmdHeader[CFE_SB_CMD_HDR_SIZE];
   uint8	PDUType;     /* The Type of PDU to capture and drop */
   uint8	PDUsToDrop;  /* The # of rcvd PDUs of the type to drop */

} CI_DropPDUCmd_t;


/*************************************************************************/
/*
** Type definition (CI_Lab housekeeping)...
*/
typedef struct {

    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              ci_command_error_count;
    uint8              ci_command_count;
    uint8              ci_xsums_enabled;
    uint8              SocketConnected;
    uint8              FDPdusDropped;
    uint8              EOFPdusDropped;
    uint8              FINPdusDropped;
    uint8              ACKPdusDropped;
    uint8              MDPdusDropped;
    uint8              NAKPdusDropped;
    uint8              spare[2];
    uint32             IngestPackets;
    uint32             IngestErrors;
    uint32             PDUsCaptured;

}   OS_PACK ci_hk_tlm_t  ;

#define CI_LAB_HK_TLM_LNGTH           sizeof ( ci_hk_tlm_t )

#endif /* _ci_lab_msg_h_ */

/************************/
/*  End of File Comment */
/************************/
