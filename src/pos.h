// Copyright (c) 2015-2016 The BlackCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COIN_POS_H
#define COIN_POS_H

#include "pos.h"
#include "txdb.h"
#include "validation.h"
#include "arith_uint256.h"
#include "consensus/validation.h"
#include "hash.h"
#include "timedata.h"
#include "chainparams.h"
#include "script/sign.h"
#include "wallet/wallet.h"
#include <stdint.h>

using namespace std;

/** Compute the hash modifier for proof-of-stake */
uint256 ComputeStakeModifier(const CBlockIndex* pindexPrev, const uint256& kernel);

struct CStakeCache{
    CStakeCache(CBlockHeader blockFrom_, CDiskTxPos txindex_, const CTransaction txPrev_) : blockFrom(blockFrom_), txindex(txindex_), txPrev(txPrev_){
    }
    CBlockHeader blockFrom;
    CDiskTxPos txindex;
    const CTransaction txPrev;
};

// Check whether the coinstake timestamp meets protocol
bool CheckCoinStakeTimestamp(int64_t nTimeBlock, int64_t nTimeTx);
bool CheckStakeBlockTimestamp(int64_t nTimeBlock);
bool CheckPoSKernel(CBlockIndex* pindexPrev, unsigned int nBits, uint32_t nTime, const COutPoint& prevout, uint32_t* pBlockTime = NULL);

bool CheckStakeKernelHash(const CBlockIndex* pindexPrev, unsigned int nBits, CBlockIndex& blockFrom,  const CCoins* txPrev, const COutPoint& prevout, unsigned int nTimeTx);
bool IsConfirmedInNPrevBlocks(const CDiskTxPos& txindex, const CBlockIndex* pindexFrom, int nMaxDepth, int& nActualDepth);
bool CheckProofOfStake(CBlockIndex* pindexPrev, const CTransaction& tx, unsigned int nBits, CValidationState &state);
void CacheKernel(std::map<COutPoint, CStakeCache>& cache, const COutPoint& prevout);
bool VerifySignature(const CTransaction& txFrom, const CTransaction& txTo, unsigned int nIn, unsigned int flags, int nHashType);

uint64_t GetCoinAgeByTime(int64_t timespan, int64_t nValue  );
bool TransactionGetCoinAge(CTransaction& transaction, uint64_t& nCoinAge);

CAmount GetProofOfStakeReward(const CBlockIndex* pindexPrev, int64_t nCoinAge, int64_t nFees);
bool CheckStake(CBlock* pblock, CWallet& wallet, const CChainParams& chainparams);
#endif // COIN_POS_H
