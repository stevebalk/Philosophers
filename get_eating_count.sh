#!/bin/bash
awk '{sub(/^[0-9]+ /, ""); print}' "outfile" | grep eating | sort | uniq -c | sort