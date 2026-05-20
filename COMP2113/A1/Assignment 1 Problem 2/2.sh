#!/bin/bash

file="$1"

if [ ! -f "$file" ]; then
    exit 1
fi

given=$(head -n 1 "$file" | tr -d '\r' | xargs)
num=$(tail -n +2 "$file" | cut -d':' -f2- | grep "$given" | wc -l)
echo "The number of dishes that contain the given ingredient: $num"