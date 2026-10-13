/**
 * \file      smtc_real_defs.h
 *
 * \brief     Region Abstraction Layer (REAL) API types definition
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2021. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef REAL_DEFS_H
#define REAL_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>
#include <stdbool.h>
#include "ral_defs.h"

#if defined( REGION_EU_868 )
#include "region_eu_868_defs.h"
#endif
#if defined( REGION_AS_923 )
#include "region_as_923_defs.h"
#endif
#if defined( REGION_US_915 )
#include "region_us_915_defs.h"
#endif
#if defined( REGION_AU_915 )
#include "region_au_915_defs.h"
#endif
#if defined( REGION_WW_2G4 )
#include "region_ww_2g4_defs.h"
#endif
#if defined( REGION_CN_470 )
#include "region_cn_470_defs.h"
#endif
#if defined( REGION_IN_865 )
#include "region_in_865_defs.h"
#endif
#if defined( REGION_KR_920 )
#include "region_kr_920_defs.h"
#endif
#if defined( REGION_RU_864 )
#include "region_ru_864_defs.h"
#endif
#if defined( REGION_CN_470_RP_1_0 )
#include "region_cn_470_rp_1_0_defs.h"
#endif

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

#ifndef LORAWAN_FAILURE_DIAGNOSTICS
#define LORAWAN_FAILURE_DIAGNOSTICS 0
#endif

#ifndef LORAWAN_JOIN_BANK_PREFERENCE
#define LORAWAN_JOIN_BANK_PREFERENCE 0
#endif

#if defined( RP2_101 )
#define RP_VERSION_REVISION ( 2 )
#define RP_VERSION_MAJOR ( 1 )
#define RP_VERSION_MINOR ( 0 )
#define RP_VERSION_PATCH ( 1 )
#elif defined( RP2_103 )
#define RP_VERSION_REVISION ( 2 )
#define RP_VERSION_MAJOR ( 1 )
#define RP_VERSION_MINOR ( 0 )
#define RP_VERSION_PATCH ( 3 )
#else
#error "RP_VERSION (LoRaWAN Regional Parameter version) must be defined: RP2_101 or RP2_103"
#endif

#define SMTC_REAL_PING_SLOT_PERIODICITY_DEFAULT 7  // Default ping slot period (128s)

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

typedef enum smtc_real_region_types_e
{
    SMTC_REAL_REGION_UNKNOWN = 0,
#if defined( REGION_EU_868 )
    SMTC_REAL_REGION_EU_868 = 1,
#endif
#if defined( REGION_AS_923 )
    SMTC_REAL_REGION_AS_923 = 2,
#endif
#if defined( REGION_US_915 )
    SMTC_REAL_REGION_US_915 = 3,
#endif
#if defined( REGION_AU_915 )
    SMTC_REAL_REGION_AU_915 = 4,
#endif
#if defined( REGION_CN_470 )
    SMTC_REAL_REGION_CN_470 = 5,
#endif
#if defined( REGION_WW_2G4 )
    SMTC_REAL_REGION_WW_2G4 = 6,
#endif
#if defined( REGION_AS_923 )
    SMTC_REAL_REGION_AS_923_GRP2 = 7,
#endif
#if defined( REGION_AS_923 )
    SMTC_REAL_REGION_AS_923_GRP3 = 8,
#endif
#if defined( REGION_IN_865 )
    SMTC_REAL_REGION_IN_865 = 9,
#endif
#if defined( REGION_KR_920 )
    SMTC_REAL_REGION_KR_920 = 10,
#endif
#if defined( REGION_RU_864 )
    SMTC_REAL_REGION_RU_864 = 11,
#endif
#if defined( REGION_CN_470_RP_1_0 )
    SMTC_REAL_REGION_CN_470_RP_1_0 = 12,
#endif
#if defined( RP2_103 )
#if defined( REGION_AS_923 )
    SMTC_REAL_REGION_AS_923_GRP4 = 13,
#endif
#endif
} smtc_real_region_types_t;

/**
 * API return status
 */
typedef enum smtc_real_status_e
{
    SMTC_REAL_STATUS_OK = 0,
    SMTC_REAL_STATUS_UNSUPPORTED_FEATURE,
    SMTC_REAL_STATUS_UNKNOWN_VALUE,
    SMTC_REAL_STATUS_ERROR,
} smtc_real_status_t;

/**
 * API return status
 */
enum smtc_real_no_downlink_limit_e
{
    SMTC_REAL_ADR_BACKOFF_END = 0,
    SMTC_REAL_NO_RX_USER_THRESHOLD,
};

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

static const uint8_t smtc_real_region_list[] = {
#if defined( REGION_EU_868 )
    SMTC_REAL_REGION_EU_868,
#endif
#if defined( REGION_AS_923 )
    SMTC_REAL_REGION_AS_923,
#endif
#if defined( REGION_US_915 )
    SMTC_REAL_REGION_US_915,
#endif
#if defined( REGION_AU_915 )
    SMTC_REAL_REGION_AU_915,
#endif
#if defined( REGION_CN_470 )
    SMTC_REAL_REGION_CN_470,
#endif
#if defined( REGION_WW_2G4 )
    SMTC_REAL_REGION_WW_2G4,
#endif
#if defined( REGION_AS_923 )
    SMTC_REAL_REGION_AS_923_GRP2,
#endif
#if defined( REGION_AS_923 )
    SMTC_REAL_REGION_AS_923_GRP3,
#endif
#if defined( REGION_IN_865 )
    SMTC_REAL_REGION_IN_865,
#endif
#if defined( REGION_KR_920 )
    SMTC_REAL_REGION_KR_920,
#endif
#if defined( REGION_RU_864 )
    SMTC_REAL_REGION_RU_864,
#endif
#if defined( REGION_CN_470_RP_1_0 )
    SMTC_REAL_REGION_CN_470_RP_1_0,
#endif
#if defined( RP2_103 )
#if defined( REGION_AS_923 )
    SMTC_REAL_REGION_AS_923_GRP4,
#endif
#endif
};

static const uint8_t SMTC_REAL_REGION_LIST_LENGTH =
    sizeof( smtc_real_region_list ) / sizeof( smtc_real_region_list[0] );

/**
 * Max EIRP table definition
 */
static const uint8_t smtc_real_max_eirp_dbm_from_idx[] = {
    8, 10, 12, 13, 14, 16, 18, 20, 21, 24, 26, 27, 29, 30, 33, 36
};

typedef struct smtc_real_ctx_s
{
    uint32_t* tx_frequency_channel_ctx;
    uint32_t* rx1_frequency_channel_ctx;
    uint8_t*  channel_index_enabled_ctx;
    uint8_t*  unwrapped_channel_mask_ctx;
    uint8_t*  min_tx_dr_channel_ctx;
    uint8_t*  max_tx_dr_channel_ctx;
    uint16_t* dr_bitfield_tx_channel_ctx;
    uint8_t*  dr_distribution_init_ctx;
    uint8_t*  dr_distribution_ctx;
    uint8_t*  join_dr_distribution_ctx;
    uint8_t*  custom_dr_distribution_init_ctx;
    uint8_t   sync_word_ctx;
    bool      uplink_dwell_time_ctx;
    bool      downlink_dwell_time_ctx;
} smtc_real_ctx_t;

typedef struct smtc_real_const_s
{
    uint8_t         const_number_of_tx_channel;
    uint8_t         const_number_of_rx_channel;
    uint8_t         const_number_of_boot_tx_channel;
    uint8_t         const_number_of_channel_bank;
    uint8_t         const_join_accept_delay1;
    uint8_t         const_received_delay1;
    uint8_t         const_tx_power_dbm;
    uint8_t         const_max_tx_power_idx;
    uint8_t         const_adr_ack_limit;
    uint8_t         const_adr_ack_delay;
    const uint8_t*  const_datarate_offsets;
    const uint8_t*  const_datarate_backoff;
    uint8_t         const_ack_timeout;
    uint32_t        const_freq_min;
    uint32_t        const_freq_max;
    uint32_t        const_rx2_freq;
    uint8_t         const_frequency_factor;
    int32_t         const_frequency_offset_hz;
    uint8_t         const_rx2_dr_init;
    uint8_t         const_sync_word_private;
    uint8_t         const_sync_word_public;
    uint8_t*        const_sync_word_gfsk;
    uint8_t*        const_sync_word_lr_fhss;
    uint8_t         const_min_tx_dr;
    uint8_t         const_min_tx_dr_limit;
    uint8_t         const_min_rx_dr;
    uint8_t         const_max_tx_dr;
    uint8_t         const_max_rx_dr;
    uint8_t         const_number_rx1_dr_offset;
    uint16_t        const_dr_bitfield;
    uint16_t        const_default_tx_dr_bit_field;
    uint8_t         const_number_of_tx_dr;
    bool            const_tx_param_setup_req_supported;
    bool            const_new_channel_req_supported;
    bool            const_dtc_supported;
    bool            const_lbt_supported;
    uint32_t        const_lbt_sniff_duration_ms;
    int16_t         const_lbt_threshold_dbm;
    uint32_t        const_lbt_bw_hz;
    const uint8_t*  const_max_payload_m;
    ral_lora_cr_t   const_coding_rate;
    uint8_t         const_dtc_number_of_band;
    const uint16_t* const_dtc_by_band;
    const uint32_t* const_dtc_frequency_range_by_band;
    const uint8_t*  const_mobile_longrange_dr_distri;
    const uint8_t*  const_mobile_lowpower_dr_distri;
    const uint8_t*  const_default_dr_distri;
    cf_list_type_t  const_cf_list_type_supported;
    uint8_t         const_beacon_dr;
    uint32_t        const_beacon_frequency;
    uint32_t        const_ping_slot_frequency;
    bool            const_uplink_dwell_time;
} smtc_real_const_t;

#if LORAWAN_FAILURE_DIAGNOSTICS
typedef enum smtc_real_diagnostic_mask_source_e
{
    MASK_SOURCE_UNKNOWN = 0,
    MASK_SOURCE_DEFAULT,
    MASK_SOURCE_POST_JOIN,
    MASK_SOURCE_CFLIST,
    MASK_SOURCE_LINK_ADR,
    MASK_SOURCE_OTHER
} smtc_real_diagnostic_mask_source_t;

typedef struct smtc_real_diagnostic_s
{
    bool          valid;
    bool          fallback;
    uint16_t      trials;
    uint16_t      supported_dr_mask;
    uint8_t       input_adr_dr;
    uint8_t       output_dr;
    dr_strategy_t strategy_before;
    dr_strategy_t strategy_after;
    bool          cflist_mask_applied;
    uint8_t       mask_source;
} smtc_real_diagnostic_t;
#endif

#if LORAWAN_JOIN_BANK_PREFERENCE
#define SMTC_REAL_JOIN_PREFERENCE_BANK_MAX 7      // Physical US915 banks, each with 8 x 125 kHz + 1 x 500 kHz
#define SMTC_REAL_JOIN_PREFERENCE_BANK_NONE 0xFF  // No preferred bank armed

typedef enum smtc_real_join_preference_attempt_e
{
    SMTC_REAL_JOIN_PREFERENCE_NONE = 0,
    SMTC_REAL_JOIN_PREFERENCE_SELECTED,
    SMTC_REAL_JOIN_PREFERENCE_TRANSMITTED,
} smtc_real_join_preference_attempt_t;

typedef struct smtc_real_join_preference_s
{
    bool     active;             // Preference armed for the current join session
    uint8_t  bank;               // Physical US915 bank [0:7] or SMTC_REAL_JOIN_PREFERENCE_BANK_NONE
    uint8_t  attempts_remaining; // Preferred bank selections still allowed
    uint8_t  failures_remaining; // Completed failed transmissions needed to prove exhaustion
    smtc_real_join_preference_attempt_t attempt_state;
} smtc_real_join_preference_t;

typedef struct smtc_real_first_join_tx_s
{
    uint32_t frequency_hz; // Zero until the first actual join TX of this session
    uint8_t  data_rate;
    bool     used_preference;
} smtc_real_first_join_tx_t;
#endif

typedef struct smtc_real_s
{
    smtc_real_region_types_t region_type;
    smtc_real_const_t        real_const;
    smtc_real_ctx_t          real_ctx;

#if LORAWAN_FAILURE_DIAGNOSTICS
    smtc_real_diagnostic_t diagnostic;
#endif

#if LORAWAN_JOIN_BANK_PREFERENCE
    smtc_real_join_preference_t join_preference;
    smtc_real_first_join_tx_t   first_join_tx;
#endif

    union smtc_real_region_u
    {
#if defined( REGION_EU_868 )
        region_eu868_context_t eu868;
#endif
#if defined( REGION_AS_923 )
        region_as923_context_t as923;
#endif
#if defined( REGION_US_915 )
        region_us915_context_t us915;
#endif
#if defined( REGION_AU_915 )
        region_au915_context_t au915;
#endif
#if defined( REGION_CN_470 )
        region_cn470_context_t cn470;
#endif
#if defined( REGION_WW_2G4 )
        region_ww_2g4_context_t ww_2g4;
#endif
#if defined( REGION_IN_865 )
        region_in865_context_t in865;
#endif
#if defined( REGION_KR_920 )
        region_kr920_context_t kr920;
#endif
#if defined( REGION_RU_864 )
        region_ru864_context_t ru864;
#endif
#if defined( REGION_CN_470_RP_1_0 )
        region_cn470_rp_1_0_context_t cn470_rp_1_0;
#endif
    } region;

} smtc_real_t;

#ifdef __cplusplus
}
#endif

#endif  // __RAL_DEFS_H__

/* --- EOF ------------------------------------------------------------------ */
