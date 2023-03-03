if [ -d "./src/build/" ]; then
  cd ./src/build &&
  rm -rf *
fi
cmake .. &&
make &&
../../server
