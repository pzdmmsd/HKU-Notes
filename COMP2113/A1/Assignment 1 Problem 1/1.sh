#!/bin/bash

file="$1"

if [ ! -f "$file" ]; then
    echo "Total requests: 0"
    echo "Successful requests: 0"
    echo "Client errors: 0"
    echo "Server errors: 0"
    echo "Top 3 endpoints:"
    exit 0
fi

total_requests=$(awk 'END {print NR}' "$file")
successful_requests=$(awk '{print $5}' "$file" | grep -E "2[0-9]{2}" | awk 'END {print NR}')
client_errors=$(awk '{print $5}' "$file" | grep -E "4[0-9]{2}" | awk 'END {print NR}')
server_errors=$(awk '{print $5}' "$file" | grep -E "5[0-9]{2}" | awk 'END {print NR}')
echo "Total requests: $total_requests"
echo "Successful requests: $successful_requests"
echo "Client errors: $client_errors"
echo "Server errors: $server_errors"
echo "Top 3 endpoints:"
awk '{print $4}' "$file" | sort | uniq -c | sort -rn | head -n 3 | awk '{print $2 " " $1}'