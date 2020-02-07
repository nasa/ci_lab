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

/*************************************************************************/
/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];

} CI_NoArgsCmd_t;

/*
 * Neither the Noop nor ResetCounters command
 * have any payload, but should still "reserve" a unique
 * structure type to employ a consistent handler pattern.
 *
 * This matches the pattern in CFE core and other modules.
 */
typedef CI_NoArgsCmd_t  CI_NoopCmd_t;
typedef CI_NoArgsCmd_t  CI_ResetCountersCmd_t;


/*************************************************************************/
/*
** Type definition (CI_Lab housekeeping)...
*/
typedef struct
{
    uint8  CommandErrorCounter;
    uint8  CommandCounter;
    uint8  EnableChecksums;
    uint8  SocketConnected;
    uint8  Spare1[8];
    uint32 IngestPackets;
    uint32 IngestErrors;
    uint32 Spare2;

} CI_HkTlm_Payload_t;

typedef struct
{
    uint8  TlmHeader[CFE_SB_TLM_HDR_SIZE];
    CI_HkTlm_Payload_t Payload;
} OS_PACK ci_hk_tlm_t;

#define CI_LAB_HK_TLM_LNGTH sizeof(ci_hk_tlm_t)

#endif /* _ci_lab_msg_h_ */

/************************/
/*  End of File Comment */
/************************/
