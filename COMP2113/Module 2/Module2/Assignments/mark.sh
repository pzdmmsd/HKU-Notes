#!/bin/bash
allStudents=$(ls)
for student in $allStudents
do
    if [ -d "$student" ]
    then 
        cd $student
        if [ -f "assign.cpp" ]
        then
            g++ assign.cpp -o assign.o 2>error.txt
            if [ -f "assign.o" ]
            then
                ./assign.o < ../input.txt > output.txt 
                result=`diff output.txt ../correct.txt`
                if [ -n "$result" ]
                then
                    echo "$student: Wrong answer."
                else
                    echo "$student: Correct!"
                fi
            else
                echo "$student: Cannot be compiled."
            fi
        fi
        cd ..
    fi
done