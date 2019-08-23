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
** File: ci_lab_defs.h
**
** Purpose: 
**  Define CI Lab Definitions that other apps may need to use
**
** Notes:
**
*******************************************************************************/
#ifndef _ci_lab_defs_h_
#define _ci_lab_defs_h_

/*
** Definitions
*/
/* File Size Command argument values */
#define PDU_SIZE_ADD		0
#define PDU_SIZE_SUBTRACT	1

/* PDU Type argument values */
#define FILE_DATA_PDU	0
#define EOF_PDU		1
#define FIN_PDU		2
#define ACK_PDU		3
#define META_DATA_PDU	4
#define NAK_PDU		5

#endif /* _ci_lab_defs_h_ */

/************************/
/*  End of File Comment */
/************************/
