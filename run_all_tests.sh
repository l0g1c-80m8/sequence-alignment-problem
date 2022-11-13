#!/bin/bash

rm -rf ./build
mkdir build
cd ./build || exit
cmake ..
make

cd ..

for i in {1..15}
do
   echo "Running test $i (basic)"
   ./build/seq "./src/datapoints/in$i.txt" "./src/datapoints/out$i.b.txt" "basic"
   echo "Running test $i (efficient)"
   ./build/seq "./src/datapoints/in$i.txt" "./src/datapoints/out$i.e.txt" "efficient"
done