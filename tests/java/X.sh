#!/bin/bash
./build-origin.sh
./rmtmp.sh
./transformer.sh
./encrypt_SGXindex.sh
cd replaceOutput
java test.Test
