#!/bin/bash

run_test() {
    echo "Running test with input file: $1"
    echo -e ' \t '

    a=$(./array.exe < "tests/$1.txt")
    result="${a: -2}"
    #echo "$result"
    if [ "$result" -eq 1 ]; then
        echo -e "Test $1 \033[102mpassed\033[0m"
    else
        echo -e "Test $1 \033[101mfailed\033[0m"
    fi

    echo -e ' \t '
}

input=("Usual_case" "Example_1" "Example_2" "Example_3" "All_Null"
"Duplicate_elements")

for input_file in "${input[@]}"; do
    run_test "$input_file"
done