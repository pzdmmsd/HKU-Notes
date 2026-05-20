#!/bin/bash

#cat "$1" | grep "/product/" | cut -f1,4 | sort | uniq
file="$1"
lines=$(grep "/products/" "$file")
filt=$(echo "$lines" | cut -f1,4)
echo "$filt" | sort | uniq