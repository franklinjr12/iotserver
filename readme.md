

# Requirements
linux OS, gcc, cmake, clang, clang-format, Boost

# For compiling project
cmake -S . --build build

# For running
./build/app.exe

# For compile and run if success
cmake -S . --build build && ./build/app.exe

# For compiling examples
g++ -I$BOOSTFOLDER -L$BOOSTFOLDER/lib -o build/connect.exe examples/connect.cpp -lboost_system -pthread && ./build/connect.exe