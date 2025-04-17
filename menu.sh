#!/bin/bash
while true; do
  echo "1) Print Database"
  echo "2) Print Block By Hash"
  echo "3) Print Block By Height"
  echo "4) Export Data To .csv"
  echo "5) Refresh Database (last N blocks)"
  echo "6) Exit"
  read -p "Enter Your Choice (1 – 6): " choice

  case "$choice" in
    1) 
      echo "Printing Database: "
      ./findByHash	##enter here the relevant cpp exe 
      ;;
    2)
      read -p "Enter Block Hash: " blk_hash
      echo "Printing Block Hash: $blk_hash"
      ./refreshDb "$blk_hash"	##enter here the relevant cpp exe
      ;;
    3)
      read -p "Enter Block Height: " blk_height
      echo "Printing Block Height: $blk_height"
      ./refreshDb "$blk_height"	##enter here the relevant cpp exe
      ;;
    4)
      read -p "Enter Number Of Blocks To Import To The Database .csv File: " count
      ./refreshDb "$count"	##enter here the relevant cpp exe
      ;;
    5)
      read -p "Enter Number Of Blocks To Refresh To The Database .csv File: " count
      ./refreshDb "$count"	##enter here the relevant cpp exe
      ;;
    6)
      echo "Goodbye!"; break
      ;;
    *)
      echo
      echo "Please choose 1 through 5, or 6 to exit."
      ;;
  esac
  echo
done
