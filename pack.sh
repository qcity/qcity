#!/bin/sh
coin=qcity
version=0.14.6
platform=`uname -a | awk '{print tolower($1)}'`
arch=`uname -m`

if test "${platform}" = "linux" ; then
    if test "${arch}" = "x86_64" ; then
        tarball_name="${coin}-${version}-linux64.tar.gz"
    elif test "${arch}" = "x86_32" ; then
        tarball_name="${coin}-${version}-linux32.tar.gz"
    fi
elif test "${platform}" = "darwin" ; then
    tarball_name="${coin}-${version}-osx64.tar.gz"
else
    echo "${coin} binary distribution not available for platform and architecture"
    exit -1
fi
bitcoin_dir=${coin}-${version}
rm -Rf tmp/*
rm -Rf ${tarball_name}

mkdir -p tmp/${coin}

cp src/${coin}-cli          tmp/${coin}/${coin}-cli
cp src/${coin}-tx           tmp/${coin}/${coin}-tx
cp src/${coin}d             tmp/${coin}/${coin}d
cp src/test/test_bitcoin    tmp/${coin}/test_${coin}
cp src/wallet-utility       tmp/${coin}/
cp src/qt/${coin}-qt        tmp/${coin}/${coin}-qt
cp ${coin}.conf             tmp/${coin}/${coin}.conf
cd tmp
tar -zcvf ../${tarball_name} ./
cd ../
