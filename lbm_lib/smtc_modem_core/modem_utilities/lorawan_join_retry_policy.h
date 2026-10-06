/* SPDX-License-Identifier: BSD-3-Clause-Clear */

/**
 * @file lorawan_join_retry_policy.h
 * @brief Pure timing helpers for bounded application join recovery waits.
 *
 * The limits include the scheduler and transmission protocol manager jitters
 * when application recovery controls the wait. The MAC earliest-join deadline
 * is never shortened; regional restrictions and radio availability can require
 * longer waits.
 */

#ifndef LORAWAN_JOIN_RETRY_POLICY_H
#define LORAWAN_JOIN_RETRY_POLICY_H

#include <stdbool.h>
#include <stdint.h>

#define LORAWAN_JOIN_RETRY_SCHEDULER_JITTER_MAX_SECONDS 5U
#define LORAWAN_JOIN_RETRY_TX_JITTER_MIN_MS 500U
#define LORAWAN_JOIN_RETRY_TX_JITTER_MAX_MS 6000U
#define LORAWAN_JOIN_RETRY_JITTER_BUDGET_SECONDS \
    ( LORAWAN_JOIN_RETRY_SCHEDULER_JITTER_MAX_SECONDS + \
      ( ( LORAWAN_JOIN_RETRY_TX_JITTER_MAX_MS + 999U ) / 1000U ) )
#define LORAWAN_JOIN_RETRY_FIRST_HOUR_SECONDS 3600U

#if defined( LORAWAN_JOIN_RETRY_MAX_DELAY_SECONDS ) || defined( LORAWAN_JOIN_FIRST_HOUR_MAX_DELAY_SECONDS )
#if !defined( LORAWAN_JOIN_RETRY_MAX_DELAY_SECONDS ) || !defined( LORAWAN_JOIN_FIRST_HOUR_MAX_DELAY_SECONDS )
#error "Both LoRaWAN join retry limits must be defined together"
#endif
#if ( LORAWAN_JOIN_RETRY_MAX_DELAY_SECONDS < LORAWAN_JOIN_RETRY_JITTER_BUDGET_SECONDS ) || \
    ( LORAWAN_JOIN_FIRST_HOUR_MAX_DELAY_SECONDS < LORAWAN_JOIN_RETRY_JITTER_BUDGET_SECONDS )
#error "LoRaWAN join retry limits must leave room for both jitters"
#endif
/* The supervisor converts seconds to milliseconds using signed 32-bit timing. */
#if ( LORAWAN_JOIN_RETRY_MAX_DELAY_SECONDS > 2147483U ) || \
    ( LORAWAN_JOIN_FIRST_HOUR_MAX_DELAY_SECONDS > 2147483U )
#error "LoRaWAN join retry limits exceed the supported timer range"
#endif
#define LORAWAN_JOIN_RETRY_POLICY_ENABLED 1
#else
#define LORAWAN_JOIN_RETRY_POLICY_ENABLED 0
#endif

static inline uint32_t lorawan_join_retry_active_limit_seconds( uint32_t global_max_s, uint32_t first_hour_max_s,
                                                               uint32_t first_join_timestamp_s, uint32_t now_s,
                                                               bool first_attempt_pending )
{
    if( first_attempt_pending || ( ( uint32_t ) ( now_s - first_join_timestamp_s ) <
                                  LORAWAN_JOIN_RETRY_FIRST_HOUR_SECONDS ) )
    {
        return ( first_hour_max_s < global_max_s ) ? first_hour_max_s : global_max_s;
    }
    return global_max_s;
}

static inline uint32_t lorawan_join_retry_base_budget_seconds( uint32_t limit_s )
{
    return ( limit_s > LORAWAN_JOIN_RETRY_JITTER_BUDGET_SECONDS )
               ? limit_s - LORAWAN_JOIN_RETRY_JITTER_BUDGET_SECONDS
               : 0U;
}

static inline uint32_t lorawan_join_retry_cap_delay_seconds( uint32_t delay_s, uint32_t limit_s )
{
    const uint32_t budget_s = lorawan_join_retry_base_budget_seconds( limit_s );
    return ( delay_s < budget_s ) ? delay_s : budget_s;
}

/**
 * @brief Schedule a retry no earlier than the MAC deadline.
 *
 * Only the additional application recovery delay is capped. The MAC deadline
 * remains authoritative even when it exceeds the active phase's limit.
 * Unsigned subtraction supports timer wrap; a deadline in the past contributes
 * no delay. The supported future deadline range is at most INT32_MAX seconds.
 */
static inline uint32_t lorawan_join_retry_schedule_time_seconds( uint32_t now_s, uint32_t mac_deadline_s,
                                                                uint32_t recovery_delay_s, uint32_t jitter_s,
                                                                uint32_t limit_s )
{
    uint32_t remaining_s = mac_deadline_s - now_s;
    if( remaining_s > INT32_MAX )
    {
        remaining_s = 0U;
    }
    const uint32_t recovery_s = lorawan_join_retry_cap_delay_seconds( recovery_delay_s, limit_s );
    const uint32_t delay_s    = ( remaining_s > recovery_s ) ? remaining_s : recovery_s;
    const uint32_t bounded_jitter_s = ( jitter_s < LORAWAN_JOIN_RETRY_SCHEDULER_JITTER_MAX_SECONDS )
                                          ? jitter_s
                                          : LORAWAN_JOIN_RETRY_SCHEDULER_JITTER_MAX_SECONDS;
    return now_s + delay_s + bounded_jitter_s;
}

#endif /* LORAWAN_JOIN_RETRY_POLICY_H */
