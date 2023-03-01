if [ ! -d "./build/" ];
then  mkdir build
fi

pushd build > /dev/null		
cmake .. > /dev/null
make > /dev/null
popd > /dev/null
./build/Ants


