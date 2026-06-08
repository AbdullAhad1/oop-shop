#!/bin/sh
cd "$(dirname "$0")"
make -s
./build/shop
