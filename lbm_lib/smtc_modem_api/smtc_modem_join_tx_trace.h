#ifndef SMTC_MODEM_JOIN_TX_TRACE_H
#define SMTC_MODEM_JOIN_TX_TRACE_H

#include <stdbool.h>
#include <stdint.h>

#define SMTC_MODEM_JOIN_TX_TRACE_CAPACITY 64U

/** One join request confirmed by the radio planner's TX_DONE event. */
typedef struct smtc_modem_join_tx_trace_record_s
{
    uint32_t sequence;                 //!< One-based actual transmission index in this explicit join session
    uint32_t tx_done_timestamp_ms;     //!< Radio TX_DONE timestamp on the wrapping modem milliseconds clock
    uint32_t frequency_hz;
    uint32_t airtime_ms;               //!< Radio planner's measured airtime for this transmission
    uint32_t next_join_deadline_seconds; //!< MAC retry deadline on the wrapping modem seconds clock
    uint16_t dev_nonce;
    uint8_t  data_rate;
    uint8_t  bank;                     //!< Physical US915 bank [0:7], or 0xFF for an unmapped channel/region
    bool     used_preference;
    bool     next_join_deadline_valid; //!< False until a failed attempt finishes its receive windows
    bool     join_backoff_bypassed;    //!< Runtime or build-time join duty-cycle bypass at transmission
} smtc_modem_join_tx_trace_record_t;

/** Runtime snapshot; the latest count records are ordered oldest to newest. */
typedef struct smtc_modem_join_tx_trace_s
{
    uint32_t session_id; //!< Increments for accepted explicit join requests; resets when the stack is initialized
    uint32_t total;      //!< Number of actual join transmissions since the latest accepted explicit join request
    uint32_t dropped;    //!< Oldest records discarded when capacity is exceeded
    uint8_t  count;
    smtc_modem_join_tx_trace_record_t records[SMTC_MODEM_JOIN_TX_TRACE_CAPACITY];
} smtc_modem_join_tx_trace_t;

#endif
