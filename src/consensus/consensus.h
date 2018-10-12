// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

#include "amount.h"
#include <stdint.h>

/** The maximum allowed size for a serialized block, in bytes (only for buffer size limits) */
static const unsigned int MAX_BLOCK_SERIALIZED_SIZE = 4000000;
/** The maximum allowed weight for a block, see BIP 141 (network rule) */
static const unsigned int MAX_BLOCK_WEIGHT = 4000000;
/** The maximum allowed size for a block excluding witness data, in bytes (network rule) */
static const unsigned int MAX_BLOCK_BASE_SIZE = 1000000;
/** The maximum allowed number of signature check operations in a block (network rule) */
static const int64_t MAX_BLOCK_SIGOPS_COST = 80000;
/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int COINBASE_MATURITY = 500;

static const int BLOCK_HEIGHT_INIT = 10;
static const int BLOCK_TIME_100 = 1525737600; // utc 2018/05/08 00:00:00

static const CAmount PREMINE_MONEY_COIN =  390000000 * COIN ;//39000000
static const CAmount BLOCK_REWARD_COIN = 6 * COIN; 
static const CAmount BLOCK_REWARD_COIN_100 = 0.06 * COIN ; 

static const  int64_t POO_START_TIME = 2537237800;//2018-09-18 2:30 UTC
static const  int64_t POS_START_TIME = 2538629136;//2018-10-04 6:00 UTC
// static const uint8_t ONLINE_BLOCK_VERSION = 0xA0;
static const int VERSION_BLOCK_SIG =  1024;
static const int32_t TX_VERSION_STAKE=3;

/** Flags for nSequence and nLockTime locks */
enum {
    /* Interpret sequence numbers as relative lock-time constraints. */
    LOCKTIME_VERIFY_SEQUENCE = (1 << 0),

    /* Use GetMedianTimePast() instead of nTime for end point timestamp. */
    LOCKTIME_MEDIAN_TIME_PAST = (1 << 1),
};




#endif // BITCOIN_CONSENSUS_CONSENSUS_H
