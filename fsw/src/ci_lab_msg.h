/**
 * @file
 *  Define CI Lab Messages and info
 */
#ifndef CI_LAB_MSG_H
#define CI_LAB_MSG_H

/*
** CI_LAB command codes
*/
#define CI_LAB_NOOP_CC           0
#define CI_LAB_RESET_COUNTERS_CC 1

/*************************************************************************/
/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHeader;

} CI_LAB_NoArgsCmd_t;

/*
 * Neither the Noop nor ResetCounters command
 * have any payload, but should still "reserve" a unique
 * structure type to employ a consistent handler pattern.
 *
 * This matches the pattern in CFE core and other modules.
 */
typedef CI_LAB_NoArgsCmd_t CI_LAB_NoopCmd_t;
typedef CI_LAB_NoArgsCmd_t CI_LAB_ResetCountersCmd_t;

/*************************************************************************/
/*
** Type definition (CI_LAB housekeeping)...
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

} CI_LAB_HkTlm_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t TelemetryHeader;
    CI_LAB_HkTlm_Payload_t    Payload;
} CI_LAB_HkTlm_t;

#endif
