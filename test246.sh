#!/bin/sh

# テスト回数
NUMBER=10

# 最小値テスト
./prob246.exe min | tail -n 2

# 最大値テスト
./prob246.exe max | tail -n 2

# ランダム値テスト
for i in `seq 1 $NUMBER`; do
    echo "test No.$i"
    ./prob246.exe random | tail -n 2
    sleep 1s
done
