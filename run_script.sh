#!/bin/bash
for i in {0..29}
do
   ./build/ES grn10 lsoda de 1050000 $i >> de-output10-testing-limits2.txt &
done

exit

