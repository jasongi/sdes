#!/bin/bash
printf "\n-------------\nVariable Decs:\n-------------\n\n"
set -v
KEY='1010111010'
PLAINTEXT='testfile_SDES.txt'
OUTPUT=$PLAINTEXT'-encryted-with-'$KEY'.txt'
DEOUTPUT=$PLAINTEXT'-decrypted-with-'$KEY'.txt'
set +v
printf "\n"
make sdes
make s_DES_test
make key_gen_test
printf "\nRunning Tests:\n"
./key_gen_test
printf '\n'
./s_DES_test
printf "\nRunning encryption:\n./sdes -e $PLAINTEXT $OUTPUT $KEY\n"
./sdes -e $PLAINTEXT $OUTPUT $KEY
printf "\n\nRunning decryption:\n./sdes -d $OUTPUT $DEOUTPUT $KEY\n"
./sdes -d $OUTPUT $DEOUTPUT $KEY
printf "\nRunning diff analysis:\ndiff -s $PLAINTEXT $DEOUTPUT\n"
diff -s $PLAINTEXT $DEOUTPUT
printf "\n-----------\nAll Done! HD plz\n-----------\n\n"
