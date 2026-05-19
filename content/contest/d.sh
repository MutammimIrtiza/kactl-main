#!/usr/bin/env bash
if ! g++ -std=c++23 -DLOCAL -Wshadow -Wall -g \
 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG \
 -fmax-errors=2 code.cpp -o a.out 
then
    exit 1
fi
echo
echo Input:
cat $1
echo
echo Output:
./a.out < $1
echo