

# Requirements
linux OS, gcc, cmake, clang, clang-format, Boost

# For configuring cmake
cmake -S . --build build

# For compiling project
cmake --build build

# For running
./build/app.exe

# For compile and run if success
cmake --build build && ./build/app.exe

# For compiling examples
g++ -I$BOOSTFOLDER -L$BOOSTFOLDER/lib -o build/connect.exe examples/connect.cpp -lboost_system -pthread && ./build/connect.exe

g++ -I/home/franklin/iotserver/include -I$BOOSTFOLDER -L$BOOSTFOLDER/lib src/main.cpp src/receiver.cpp -lboost_system -pthread -g