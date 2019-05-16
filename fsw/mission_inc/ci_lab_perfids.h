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
** File:
**   $Id: ci_lab_perfids.h 1.3 2010/09/20 12:27:19GMT-05:00 wmoleski Exp  $
**
** Purpose: 
**  Define CI Lab Performance IDs
**
** Notes:
**
** $Log: ci_lab_perfids.h  $
** Revision 1.3 2010/09/20 12:27:19GMT-05:00 wmoleski 
** Modified the CI_LAB, SCH_LAB and TO_LAB applications to use unique message IDs and Pipe Names. The "_LAB"
** was added to all definitions so that a mission can use these "Lab" apps as well as their own mission apps together.
** Revision 1.2 2008/04/30 13:07:44EDT rjmcgraw 
** Member moved from ci_lab_perfids.h in project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/ci_lab/fsw/platform_inc/project.pj to ci_lab_perfids.h in project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/ci_lab/fsw/mission_inc/project.pj.
** Revision 1.1 2008/04/30 12:07:44ACT rjmcgraw 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/ci_lab/fsw/platform_inc/project.pj
**
*************************************************************************/
#ifndef _ci_lab_perfids_h_
#define _ci_lab_perfids_h_


#define CI_MAIN_TASK_PERF_ID            21
#define CI_SOCKET_RCV_PERF_ID           24

#endif /* _ci_lab_perfids_h_ */

/************************/
/*  End of File Comment */
/************************/
