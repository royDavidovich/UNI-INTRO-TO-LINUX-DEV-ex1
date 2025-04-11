#!/bin/bash

if [ ! "$1" ]; then
  echo "Insert as parameter for the script how many blocks you want to get"
  exit 1
fi

NUM_BLOCKS=$1
CSV_FILE="./res.csv"

echo "hash,height,total,time,relayed_by,prev_block" > "$CSV_FILE"

current_hash=$(curl -s https://api.blockcypher.com/v1/btc/main | grep '"hash"' | grep -o -E "[0-9a-f]{64}")

for (( i=0; i<NUM_BLOCKS; i++ )); do

  block_data=$(curl -s "https://api.blockcypher.com/v1/btc/main/blocks/$current_hash")

  hash=$(echo "$block_data" | grep '"hash"' | grep -o -E "[0-9a-f]{64}")
  height=$(echo "$block_data" | grep '"height"' | grep -o -E "[0-9]+")
  total=$(echo "$block_data" | grep '"total"' | grep -o -E "[0-9]+")
  time=$(echo "$block_data" | grep '"time"' | grep -o -E "[0-9:TZ-]{20}")
  relayed_by=$(echo "$block_data" | grep '"relayed_by"' | grep -o -E "[0-9]+[0-9\.:]+")
  prev_block=$(echo "$block_data" | grep '"prev_block"' | grep -o -E "[0-9a-f]{64}")

  echo "$hash,$height,$total,$time,$relayed_by,$prev_block" >> "$CSV_FILE"

  current_hash=$prev_block
done

echo "updated '$CSV_FILE' directory"
