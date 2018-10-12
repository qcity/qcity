// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

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

/** Flags for nSequence and nLockTime locks */
enum {
    /* Interpret sequence numbers as relative lock-time constraints. */
    LOCKTIME_VERIFY_SEQUENCE = (1 << 0),

    /* Use GetMedianTimePast() instead of nTime for end point timestamp. */
    LOCKTIME_MEDIAN_TIME_PAST = (1 << 1),
};



static const  int64_t POO_START_TIME = 1537237800;//2018-09-18 2:30 UTC
static const  int64_t POS_START_TIME = 1538629136;//2018-10-04 6:00 UTC
// static const uint8_t ONLINE_BLOCK_VERSION = 0xA0;
static const int VERSION_BLOCK_SIG =  1024;
static const int32_t TX_VERSION_STAKE=3;


static char * pnSeedOnline_main[] = {
    "YQw9rPR1cpFLRYeyKgT99NggNFJUifv5T5",
    "Yidn1vWNioXdcoB1LwxwQiXLWBWhW3Cmov",
    "YVuDDD2Xyd8T2xvPyH5Z6FMrR6JERFkyhe"
};
static char * pnSeedOnline_test[] = {
    "DKjp6aHVaYj4pvq55bvXn3ztHCuRf7mDd3",// priv key, cMsDP5veTZ3xi6WDMx42A8PiLN4q7Ab4XosNwR9tJfCaRnARsjPM
    "DNu5hkU6zR67NcMve3y8hm9RxoPRfzRzXX",//cQhUWWb5WcPLvWAmxVb8BmrMsJHXHERwRFxjqJgi2L27xMwnQMbJ
    "DMsSUUUYJZS6Qetd67QTVpymhMCwxiURMy" // cUoyTGecyA1Reg4NqBmCjFahb6U9tMwiZaHR5oZ8t1ZHWKtqPu2w
};

#endif // BITCOIN_CONSENSUS_CONSENSUS_H
