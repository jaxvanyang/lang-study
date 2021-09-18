#!/bin/bash

# Just like Code Runner
# Reference: https://stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash

# Support language:
# 1. C
# 2. C++
# 3. Java
# 4. Kotlin
# 5. Python

if [ $# -lt 1 ]; then
	echo "Please name a file\
		Usage: runner.sh <source_file>"
	exit 3
fi

if [ ! -e $1 ]; then
    echo "Error: file not exist!"
    exit 2
fi

# run_out($1=out_file, $2=lang)
run_out() {
	if [[ "c|cpp" =~ $2 ]]; then
		$1
	elif [ $2 = "java" ]; then
		java $1
	elif [ $2 = "kt" ]; then
		java -jar $1;
	elif [ $2 = "py" ]; then
		python $1;
	else
		echo "Error: Unknown file type"
		exit 1
	fi
}

# run($1=out_file, $2=lang)
run() {
    if [ -e data.in ]; then
        run_out $1 $2 < data.in
    else
        run_out $1 $2
    fi
}

# examples are after statements
# the default type is C++ source file
full_name=$1;				# test.cc
file_name=${full_name%.*};	# test
extension=${full_name##*.};	# cc
out_file=$file_name.out;	# test.out

# use normal extension as language type
lang="cpp";

if [ $extension = "c" ]; then
	lang="c"
elif [ $extension = "java" ]; then
	out_file=$full_name	# Java can run a single source file like python
	lang="java"
elif [ $extension = "kt" ]; then
	out_file=$file_name.jar
	lang="kt"
elif [ $extension = "py" ]; then
	out_file=$full_name	# Python has no out file
	lang="py"
elif [[ ! "cc|cpp" =~ $extension ]]; then
	echo "Error: Unknow file type!"
	exit 1
fi

if [[ "c|cpp" =~ $extension ]] && [[ ! $out_file =~ "/*" ]]; then
	out_file=./$out_file
fi

if [ -e $out_file ]; then
    source_time=$(stat -c %Y  $full_name);
    out_time=$(stat -c %Y $out_file);

    if [ $source_time -lt $out_time ]; then
		echo -e "Log: Reuse compiled file & Start running\n"
        run $out_file $lang
        exit 0
    fi
fi

if [[ ! "py|java" =~ $lang ]]; then
	echo -e "Log: Start compiling\n"
fi

log_1() {
	echo -e "Log: Start running\n"
}

if [ $lang = "cpp" ]; then
	g++ $full_name -Wall -O2 -o $out_file && log_1 && run $out_file $lang
elif [ $lang = "c" ]; then
	gcc $full_name -Wall -O2 -o $out_file && log_1 && run $out_file $lang
elif [ $lang = "java" ]; then
	log_1 && run $out_file $lang
elif [ $lang = "kt" ]; then
	kotlinc $full_name -include-runtime -d $out_file && log_1 && run $out_file $lang
elif [ $lang = "py" ]; then
	log_1 && run $out_file $lang
fi
