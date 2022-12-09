g++ -std=c++14 efficient_linux.cpp CSequenceAligner.cpp CUtils.cpp -o efficient

./efficient "$1" "$2"

rm ./efficient
