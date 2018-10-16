// Copyright (c) 2018-2018 The QCityCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "poo.h"

#include "chain.h"
#include "chainparams.h"
#include "clientversion.h"
#include "coins.h"
#include "hash.h"
#include "primitives/transaction.h"
#include "uint256.h"
#include "util.h"
#include "validation.h"
#include <stdio.h>
#include "consensus/consensus.h"
#include "wallet/wallet.h"
#include "base58.h"
using namespace std;


bool GetBlockPublicKey(const CBlock& block, std::vector<unsigned char>& vchPubKey)
{
    if (block.IsProofOfWork())
        return false;

    if (block.vchBlockSig.empty())
        return false;

    
    vector<vector<unsigned char> > vSolutions;
    txnouttype whichType;
    
    const CTxOut& txout = block.IsProofOfOnline()? block.vtx[0]->vout[1]:block.vtx[1]->vout[1];

    if (!Solver(txout.scriptPubKey, whichType, vSolutions))
        return false;

    if (whichType == TX_PUBKEY)
    {
        vchPubKey = vSolutions[0];
        return true;
    }
    else
    {
        // Block signing key also can be encoded in the nonspendable output
        // This allows to not pollute UTXO set with useless outputs e.g. in case of multisig staking

        const CScript& script = txout.scriptPubKey;
        CScript::const_iterator pc = script.begin();
        opcodetype opcode;
        vector<unsigned char> vchPushValue;

        if (!script.GetOp(pc, opcode, vchPubKey))
            return false;
        if (opcode != OP_RETURN)
            return false;
        if (!script.GetOp(pc, opcode, vchPubKey))
            return false;
        if (!IsCompressedOrUncompressedPubKey(vchPubKey))
            return false;
        return true;
    }

    return false;
}


bool IsOnlineKey(CPubKey& pubkey) {
    for (size_t i=0; i<Params().OnlinePubKeys().size(); ++i) 
    {
        CBitcoinAddress * addr = Params().OnlinePubKeys()[i];
        CKeyID keyID;
        if(addr->GetKeyID(keyID)){
            if(pubkey.GetID()==keyID ){
                return true;
            }
        }
    }
    return false;
}
/**
 *  블럭의 서명을 확인한다.
 * 
 */
bool CheckBlockSignature(const CBlock& block)//, const uint256& hash)
{
    if (block.IsProofOfWork()){//online block 이 아니면
        return block.vchBlockSig.empty();
    }
    
    std::vector<unsigned char> vchPubKey;
    if(!GetBlockPublicKey(block, vchPubKey))
    {
        LogPrint("poo" ,"GetBlockPubKey fail... \n");
        return false;
    }
    CPubKey pubKey(vchPubKey);
    if(block.IsProofOfOnline() ) {
        if(!IsOnlineKey(pubKey)) {
            LogPrint("poo" ,"Not Allow PubKey \n");
            return false;
        }  
    }
    return pubKey.Verify(block.GetHashWithoutSign(), block.vchBlockSig);
}

// Check kernel hash target and coinonline signature TODO
bool CheckProofOfOnline(CBlockIndex* pindexPrev, const CTransaction& tx, unsigned int nBits, CValidationState& state)
{
    // vin size()==0 and vin prevout == null and vout.size()==1 
    if (!tx.IsCoinOnline())
        return error("CheckProofOfOnline() : called on non-coinstake %s", tx.GetHash().ToString());
    return true;
}


// Check whether the coinstake timestamp meets protocol
bool CheckCoinOnlineTimestamp(int64_t nTimeBlock, int64_t nTimeTx)
{
    const Consensus::Params& params = Params().GetConsensus();

    if(! (nTimeBlock == nTimeTx) && ((nTimeTx & params.nStakeTimestampMask) == 0)){
        DbgMsg( "%d %d %d " ,nTimeBlock ,nTimeTx ,nTimeTx & params.nStakeTimestampMask);
        return false;
    }else{
        return true;
    }
}

// Simplified version of CheckCoinOnlineTimestamp() to check header-only timestamp
bool CheckCoinOnlineTimestamp(int64_t nTimeBlock)
{
    return CheckCoinOnlineTimestamp(nTimeBlock, nTimeBlock);
}