#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 {problem_directory} {solution_name}"
    exit
fi

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

total_score=0
total_test_cases=0

for i in $(ls $1/inputs); do
    echo "Running test case $i"
    if diff <(./$1/solutions/$2 < $1/inputs/$i) <(cat $1/outputs/$i); then
        echo -e "  Test case $i ${GREEN}passed${NC}"
        total_score=$((total_score + 1))
    else
        echo -e "  Test case $i ${RED}failed${NC}"
    fi
    total_test_cases=$((total_test_cases + 1))
done

echo "Total score: $total_score / $total_test_cases"
