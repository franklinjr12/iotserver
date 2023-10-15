

# Requirements
linux OS, gcc, cmake, clang, clang-format, Boost

# For compiling examples:
g++ -I$BOOSTFOLDER -L$BOOSTFOLDER/lib -o build/connect.exe examples/connect.cpp -lboost_system -pthread && ./build/connect.exe