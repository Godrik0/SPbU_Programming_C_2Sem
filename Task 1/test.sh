#!/bin/bash

format_test_file() {
    line_count_first=0

    while IFS= read -r line || [[ -n "$line" ]]; do
        if [[ -z "$line" ]]; then
            break
        fi
        ((line_count_first++))
    done < "tests/$1.txt"

    line_count_second=$(awk 'END{print NR}' "tests/$1.txt")
    line_count_second=$((line_count_second - line_count_first - 1))

    columns=$(awk '{print NF}' "tests/$1.txt" | sort -nu | tail -n 1)

    echo "$line_count_first" > "tests/temp.txt"
    awk -v columns="$columns" -v line_count_second="$line_count_second" '{
        if (NF == 0) {
            printf "%d\n", line_count_second;
        } else {
            printf "%d\n", NF; 
            for(i=1; i<=NF; i++) {
                printf "%d\n", $i; 
            }
        }
    }' "tests/$1.txt" >> "tests/temp.txt"
}

run_test() {
    echo "Running test with input file: $1"
    echo -e ' \t '

    format_test_file "$1"

    a=$(./array.exe < "tests/temp.txt")
    
    result="${a: -2}"
    if [ "$result" -eq 1 ]; then
        echo -e "Test $1 \033[102mpassed\033[0m"
    else
        echo -e "Test $1 \033[101mfailed\033[0m"
    fi

    echo -e ' \t '
}

input=("Usual_case" "Example_1" "Example_2_fail" "Example_3_fail" "All_Null"
"Duplicate_elements" "Letter_array" "Double_array")

for input_file in "${input[@]}"; do
   run_test "$input_file"
done

rm "tests/temp.txt"