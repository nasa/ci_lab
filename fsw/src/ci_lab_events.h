/************************************************************************
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
** File: ci_lab_events.h
**
** Purpose: 
**  Define CI Lab Events IDs
**
** Notes:
**
*************************************************************************/
#ifndef _ci_lab_events_h_
#define _ci_lab_events_h_


#define CI_RESERVED_EID              0
#define CI_SOCKETCREATE_ERR_EID      1 
#define CI_SOCKETBIND_ERR_EID        2
#define CI_STARTUP_INF_EID           3 
#define CI_COMMAND_ERR_EID           4
#define CI_COMMANDNOP_INF_EID        5 
#define CI_COMMANDRST_INF_EID        6
#define CI_INGEST_INF_EID            7
#define CI_INGEST_ERR_EID            8
#define CI_MOD_PDU_FILESIZE_CMD_EID  9
#define CI_CORRUPT_CHECKSUM_CMD_EID  10
#define CI_DROP_PDU_CMD_EID          11
#define CI_CAPTUREPDU_CMD_EID        12
#define CI_INVALID_MSGID_ERR_EID     13
#define CI_STOP_PDUCAPTURE_CMD_EID   14
#define CI_NOCAPTURE_ERR_EID         15
#define CI_LEN_ERR_EID               16

#endif /* _ci_lab_events_h_ */

/************************/
/*  End of File Comment */
/************************/
