set -e
rm -rf build/
mkdir -p build
cd build
cmake ..
make
cd ..
./build/app.exe