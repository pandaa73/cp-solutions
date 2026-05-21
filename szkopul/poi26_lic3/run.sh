#!/bin/bash

# Uzycie:
#   ./run.sh <program_lub_komenda> [plik_wejsciowy]
# Przyklad:
#   ./run.sh ./licb107.e
#   ./run.sh ../prog/licb107.e in/lic0a.in
#   ./run.sh "python3 ../prog/lic2.py" in/lic0b.in

if [[ $# -lt 1 || $# -gt 2 ]]; then
	echo "Uzycie: $0 <program_lub_komenda> [plik_wejsciowy]" >&2
	exit 1
fi

cmd="$1"
input_file="${2:-input.in}"

./licsoc.e "$cmd" "$input_file"