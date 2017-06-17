// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xef;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0x99;
        pchMessageStart[3] = 0x11;
        nDefaultPort = 33074;
        nRPCPort = 33075;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // Hashed MainNet Genesis Block Output
        // block.hashMerkleRoot == 8434ce23dac87d96599789d44eb6a1a575321c38dd4306350b2f3408cca42a61
        // block.nTime = 1496286000
        // block.nNonce = 528013
        // block.GetHash = 000008c90aa0f4f96b44d6df2c414152c64de6f6668fa16c8a00b5d397bbb66d
        //
        const char* pszTimestamp = "Time to Get a Drone? - Dariusz - June 1, 2017 - The Merkle";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1496286000, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1496286000;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 528013;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000008c90aa0f4f96b44d6df2c414152c64de6f6668fa16c8a00b5d397bbb66d"));
        assert(genesis.hashMerkleRoot == uint256("0x8434ce23dac87d96599789d44eb6a1a575321c38dd4306350b2f3408cca42a61"));

        vFixedSeeds.clear();
        vSeeds.clear();

        /** REQUIRED IN QT 5.6+  (To compile on Qt5.5.1 and lower comment out below) */
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,73);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,95);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x50)(0xE7)(0xFC)(0x0A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x50)(0x9E)(0x4)(0x2F).convert_to_container<std::vector<unsigned char> >();

        // BitcoinPlanet dns seeds
         // vSeeds.push_back(CDNSSeedData("Seed01",  "127.0.0.1"));
         // vSeeds.push_back(CDNSSeedData("Seed02",  "127.0.0.1"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 0x7fffffff;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xed;
        pchMessageStart[1] = 0xfd;
        pchMessageStart[2] = 0x91;
        pchMessageStart[3] = 0x10;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        nDefaultPort = 33072;
        nRPCPort = 33073;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1496286000+120; // Sat, 11 Mar 2017 01:28:20 GMT
        genesis.nNonce = 112;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // Hashed TestNet Genesis Block Output
        // block.hashMerkleRoot == 8434ce23dac87d96599789d44eb6a1a575321c38dd4306350b2f3408cca42a61
        // block.nTime = 1496286120
        // block.nNonce = 112
        // block.GetHash = 00d951238c0e5ef1101218d632c11151803933675ad50cf0e712ff2ce35da638
        //

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00d951238c0e5ef1101218d632c11151803933675ad50cf0e712ff2ce35da638"));

        vFixedSeeds.clear();
        vSeeds.clear();

        /** REQUIRED IN QT 5.6+  (To compile on Qt5.5.1 and lower comment out below) */
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,86);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,81);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,61);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x1D)(0x9B)(0x7F)(0x74).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x1D)(0xC0)(0xFC)(0x28).convert_to_container<std::vector<unsigned char> >();

        // BitcoinPlanet dns seeds
        // vSeeds.push_back(CDNSSeedData("Seed01",  "0.0.0.0"));
        // vSeeds.push_back(CDNSSeedData("Seed02",  "0.0.0.0"));

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xff;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0x99;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1496286000+90;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 33071;
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 8434ce23dac87d96599789d44eb6a1a575321c38dd4306350b2f3408cca42a61
        block.nTime = 1496286090
        block.nNonce = 8
        block.GetHash = b9c4b5093f47484d5e9a2bf6750e5a6abf66cabd83178764ed04775f0e565c5b
        */

        assert(hashGenesisBlock == uint256("0xb9c4b5093f47484d5e9a2bf6750e5a6abf66cabd83178764ed04775f0e565c5b"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
