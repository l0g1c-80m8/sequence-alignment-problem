if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters"
    exit 1;
fi

rm -rf ./build
mkdir build
cd ./build || exit
cmake ..
make

cd ..
./build/seq "$1" "efficient"
