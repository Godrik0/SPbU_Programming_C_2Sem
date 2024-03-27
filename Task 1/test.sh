#!/bin/bash

run_test() {
    echo "Running test with input file: $1"
    echo -e ' \t '

    a=$(./array.exe < "tests/$1.txt")
    result="${a: -2}"
    #echo "$result"
    if [ "$result" -eq 1 ]; then
        echo "Test $1 passed"
    else
        echo "Test $1 failed"
    fi

    echo -e ' \t '
}

input=("Usual_case")

for input_file in "${input[@]}"; do
    run_test "$input_file"
done