g++ -std=c++14 basic_linux.cpp CSequenceAligner.cpp CUtils.cpp -o basic

./basic "$1" "$2"

rm ./basic
