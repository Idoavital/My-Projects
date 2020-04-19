#!/bin/bash

echo "building c file"

/bin/rm c_exe cpp_exe

g++ -g -D_DEBUG -o cpp_exe cpp2csrc_new.cpp
gcc -g -D_DEBUG -o c_exe cpp_to_c_ex.c

if [ -f c_exe ]
then
{    
    echo "executing"

    ./c_exe > c_exe.txt
    ./cpp_exe > cpp_exe.txt
    #meld c_exe.txt cpp_exe.txt &
}
fi
