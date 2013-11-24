#! /bin/bash

base="${1%%.h}"
struct=$base
if [ -n "$2" ]; then
    struct=$2
fi
echo ${base}__.c
echo $struct
mkdir -p gen
rm -f gen/${base_ll}.h gen/${base}_ll.c
sed s/ll/"$struct"/ <ucll.c >gen/${base}_ll.c
sed s/ll/"$struct"/ <ucll.h >gen/${base}_ll.h
sed -i "" s/\\/\\/INCLUDE/"#include \"$1\""/ gen/${base}_ll.h
sed -i "" s/\\/\\/INCLUDE/"#include \"$base_ll.h\""/ gen/${base}_ll.c
set -i "" s/SOMETHING/`echo $base | tr '[:lower:]' '[:upper:]'`_H/ gen/${base}_ll.h

