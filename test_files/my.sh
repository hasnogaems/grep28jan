#!/bin/bash

s21_command="./s21_grep"
sys_command="grep"
files=("test_0_grep.txt" "test_1_grep.txt" "test_2_grep.txt" "test_3_grep.txt" "test_4_grep.txt" "test_5_grep.txt" "test_6_grep.txt" "test_7_grep.txt")

SUCCESS=0
FAIL=0
COUNTER=0

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    "${s21_command}" $param > "${s21_command}.log"
    "${sys_command}" $param > "${sys_command}.log"
    DIFF="$(diff -s "${s21_command}.log" "${sys_command}.log")"
    let "COUNTER++"
    if [ "$DIFF" == "Files ${s21_command}.log and ${sys_command}.log are identical" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm -f "${s21_command}.log" "${sys_command}.log"
}

for var in "e" "i" "v" "c" "l" "o" "h" "n"
do
    for file in "${files[@]}"
    do
        run_test "-var" "$file" "$file"
        run_test "-var" "$file" "-var" "$file" "$file"
    done
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"






