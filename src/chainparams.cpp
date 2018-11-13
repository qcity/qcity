// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2010 Satoshi Nakamoto
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"
#include "arith_uint256.h"

#include "base58.h"

bool fSearchGenesis = true;

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nTime = nTime;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) 
                                    << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].SetEmpty();                                    
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "QCITY START NEW FUTURE  11/1/2017";
    const CScript genesisOutputScript = CScript() << 
        ParseHex("04f287634e609ef2c8c912b3d6d4064a4f8fb27d077d168ac206e4dca365d278d45f647cedb0c2a28856def63895d1946d99250526b523358219dc5714aae8d81a") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        uint32_t GEN_TIME = 1509494400;
        unsigned int NOUNCE = 404568;
        consensus.BIP34Height = 0;
        consensus.BIP65Height = 0; // bab3041e8977e0dc3eeff63fe707b92bde1dd449d8efafb248c27c8264cc311a
        consensus.BIP66Height = 0; // 7aceee012833fa8952f8835d8b1b3ae233cd6ab08fdb27a771d2bd7bdc491894
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 1 * 1 * 60 * 60; // 1 hour  sec
        consensus.nPowTargetSpacing = 1 * 60;//1min
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6048; // 75% of 8064
        consensus.nMinerConfirmationWindow = 5760; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 0; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 0; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 0; // January 31st, 2018

        //  // Deployment of PoO
        // consensus.vDeployments[Consensus::DEPLOYMENT_POO].bit = VERSION_BLOCK_SIG;
        // consensus.vDeployments[Consensus::DEPLOYMENT_POO].nStartTime = 2537237800; // January 28, 2017
        // consensus.vDeployments[Consensus::DEPLOYMENT_POO].nTimeout = 0; // January 31st, 2018
        consensus.nStakeTimestampMask = 0xf; // 15
        consensus.nProofOfOnlineInterval = 10;// 
        consensus.nStakeMinAge = 8 * 60 * 60; // 8 hours

        consensus.COINBASE_MATURITY = COINBASE_MATURITY;

        consensus.POO_START_TIME = 1541030400; // 11/01/2018 @ 0:00:00   ( seoul 11/01/2018 9:00:00)
        consensus.POS_START_TIME = 1541030400; // 11/01/2018 @ 0:00:00   ( seoul 11/01/2018 9:00:00)


        // The best chain should have at least this much work.
        // consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000006805c7318ce2736c0");
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000042daec57b49294");
        // By default assume that the signatures in ancestors of this block are valid.
        //consensus.defaultAssumeValid = uint256S("0x1673fa904a93848eca83d5ca82c7af974511a7e640e22edc2976420744f2e56a"); //1155631
        //consensus.defaultAssumeValid = uint256S("0x338dabdb0743eaf486664a9cbe2df3a36ea4c3d31b3cbf9c75d3f05ea33cf4ac");// 547850
        consensus.defaultAssumeValid = uint256S("0x2e56baaa3879c80328725b3f06c1c5963ac9a52afff339e805143f54f8d3c0e2");// 604230
        
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x71;//q
        pchMessageStart[1] = 0x74;//c
        pchMessageStart[2] = 0x63;//t
        pchMessageStart[3] = 0x79;//y
        nDefaultPort = 13301;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(GEN_TIME,NOUNCE, 0x1e0fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        uint256 hashGenesis = uint256S("0x8b3aa1f1d87b9533d9d36b63875c0c97d833cd5cd8585c05030783a515a3345b");
        uint256 hashMerkelRoot = uint256S("0xab3a00e260205f753521e80d1efa70d4f9a7aadc88070e10f5145e1aecccde80");
        
        assert(consensus.hashGenesisBlock == hashGenesis);
        assert(genesis.hashMerkleRoot == hashMerkelRoot);

        vSeeds.clear();
        // Note that of those with the service bits flag, most only support a subset of possible options
        
        vSeeds.push_back(CDNSSeedData("seed1", "qct001.bitchk.com",true));
        vSeeds.push_back(CDNSSeedData("seed2", "seed-qct.bitchk.com",true));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);//C
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,87);//c
        vOnlinePubKeys = std::vector<CBitcoinAddress *>();
        
        for(int i =0;i<ARRAYLEN( pnSeedOnline_test);i++){
            CBitcoinAddress* addr = new CBitcoinAddress(pnSeedOnline_main[i]);
            vOnlinePubKeys.push_back( addr);
        }
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,204);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0x8b3aa1f1d87b9533d9d36b63875c0c97d833cd5cd8585c05030783a515a3345b"))
            (  100000, uint256S("0x2d4a93e029c50e73ac20bb67a0669dc8e9247edb5eba01ead782ac25c1ca48f4"))
            (  200000, uint256S("0xf9bd1441095d0670f75948d9a91efc861844e07d4c643565a5a6c7003d1a81c2"))
            (  300000, uint256S("0x13f7a9b32259e07a963bcbfb073fb533781d0a9466c3821314eb22721b2e7a15"))
            (  400000, uint256S("0x49dfeb021332055258293761bf5ff306e602cd1fd03cb40c5fb00fafe24dd48a"))
            (  545000, uint256S("0x16e2f0bf0bc03428efa29c79fb90401317549853c3844ec4a0f1da142a17cd39"))
            (  604230, uint256S("0x2e56baaa3879c80328725b3f06c1c5963ac9a52afff339e805143f54f8d3c0e2"))
            
        };

        chainTxData = ChainTxData{
            // Data as of block b44bc5ae41d1be67227ba9ad875d7268aa86c965b1d64b47c35be6e8d5c352f4 (height 1155626).
            GEN_TIME, // * UNIX timestamp of last known number of transactions
            0,  // * total number of transactions between genesis and that timestamp
                    //   (the tx=... number in the SetBestChain debug.log lines)
            0.00     // * estimated number of transactions per second after that timestamp
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        uint32_t GEN_TIME = 1509495401;
        unsigned int NOUNCE = 130445;
        consensus.BIP34Height = 0;
        // consensus.BIP34Hash = uint256S("8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573");
        consensus.BIP65Height = 76; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.BIP66Height = 76; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 1 * 1 * 60 * 60; // 1 hour  sec
        consensus.nPowTargetSpacing = 1 * 60;//1min
     //   consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 0; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 0; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 0; // January 31st, 2018
 
  // Deployment of PoO
        consensus.vDeployments[Consensus::DEPLOYMENT_POO].bit = VERSION_BLOCK_SIG;
        consensus.vDeployments[Consensus::DEPLOYMENT_POO].nStartTime = 2537237800; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_POO].nTimeout = 0; // January 31st, 2018

        consensus.nStakeTimestampMask = 0xf; // 15
        consensus.nProofOfOnlineInterval = 10;// 
        consensus.nStakeMinAge = 1 * 60 * 60; // 1 hours
        consensus.COINBASE_MATURITY = COINBASE_MATURITY / 10; // 500 / 10 = 50 for fast test

        consensus.POO_START_TIME = 1539741033; // 10/17/2018 @ 1:50:00   gmt +9( seoul 10/15/2018 15:00:00)
        consensus.POS_START_TIME = 1539583200; // 10/15/2018 @ 9:00:00   gmt +9( seoul 10/15/2018 18:00:00)

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x43a16a626ef2ffdbe928f2bc26dcd5475c6a1a04f9542dfc6a0a88e5fcf9bd4c"); //8711

        pchMessageStart[0] = 0x51;
        pchMessageStart[1] = 0x43;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x59;
        nDefaultPort = 13311;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(GEN_TIME,NOUNCE, 0x1e0fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        uint256 hashGenesis = uint256S("0xf47f333675ef7872069b81c29eb84003174ea12a42db657dd133c4ca8d9d6b80");
        uint256 hashMerkelRoot = uint256S("0xa5c3358ed9bfe4c7397875af02a9cca111bc4bf3d5ce742ca22a8617bcd379cc");
        
        assert(consensus.hashGenesisBlock == hashGenesis);
        assert(genesis.hashMerkleRoot == hashMerkelRoot);

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("dns001", "qct001.bitchk.com",true));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,30);//C
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,89);//c
        vOnlinePubKeys = std::vector<CBitcoinAddress *>();
        
        for(int i =0;i<ARRAYLEN( pnSeedOnline_test);i++){
            CBitcoinAddress* addr = new CBitcoinAddress(pnSeedOnline_test[i]);
            vOnlinePubKeys.push_back( addr);
        }
        
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0xf47f333675ef7872069b81c29eb84003174ea12a42db657dd133c4ca8d9d6b80"))
        };

        chainTxData = ChainTxData{
            // Data as of block b44bc5ae41d1be67227ba9ad875d7268aa86c965b1d64b47c35be6e8d5c352f4 (height 1155626).
            GEN_TIME, // * UNIX timestamp of last known number of transactions
            0,  // * total number of transactions between genesis and that timestamp
                    //   (the tx=... number in the SetBestChain debug.log lines)
            0.00     // * estimated number of transactions per second after that timestamp
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        uint32_t GEN_TIME = 1509494402;
        unsigned int NOUNCE = 1185451;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        // consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 2.5 * 60;
     //   consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x51;
        pchMessageStart[1] = 0x43;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x59;
        nDefaultPort = 13321;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(GEN_TIME,NOUNCE, 0x1e0fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        uint256 hashGenesis = uint256S("0x059fe092401d4bde9b38de8ee3b92c3352bec2ab055d66f0b9fb418a101d2efd");
        uint256 hashMerkelRoot = uint256S("0xf3a2dc7f5ac46d618c3ddce4ba5d2bb5bbfef05eb95fc962fd95f5a4c2f068a1");
        
        assert(consensus.hashGenesisBlock == hashGenesis);
        assert(genesis.hashMerkleRoot == hashMerkelRoot);

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x059fe092401d4bde9b38de8ee3b92c3352bec2ab055d66f0b9fb418a101d2efd"))
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,30);//C
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,89);//c
        
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
