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
		java ${1%.*}
	elif [ $2 = "kt" ]; then
		java -jar $1;
	elif [ $2 = "py" ]; then
		python $1;
	else
		echo "Error: Unknown file type"
		exit 1
	fi

	if [ $? != 0 ]; then
		echo "Error: Execution failed!"
		exit 2
	fi
}

# run($1=out_file, $2=lang)
run() {
	echo "Log: Start running"

	start_time=$(date +%s%N)

    if [ -e data.in ]; then
        run_out $1 $2 < data.in
    else
        run_out $1 $2
    fi

	end_time=$(date +%s%N)

	echo "Log: Execution time: $(( (end_time - start_time) / 1000000))ms"
}

# examples are after statements
# the default type is C++ source file
path=$1;					# test.cc
file_name=${path%.*};	# test
extension=${path##*.};	# cc
out_file=$file_name.out;	# test.out

# use normal extension as language type
lang="cpp";

if [ $extension = "c" ]; then
	lang="c"
	out_file=$file_name.exe	# be different to C++ out file
elif [ $extension = "java" ]; then
	lang="java"
	out_file=$file_name.class
elif [ $extension = "kt" ]; then
	lang="kt"
	out_file=$file_name.jar
elif [ $extension = "py" ]; then
	lang="py"
	out_file=$path	# Python has no out file
elif [[ ! "cc|cpp" =~ $extension ]]; then
	echo "Error: Unknow file type!"
	exit 1
fi

if [[ "c|cpp" =~ $extension ]] && [[ ! $out_file =~ "/*" ]]; then
	out_file=./$out_file
fi

if [ -e $out_file ]; then
    source_time=$(stat -c %Y  $path);
    out_time=$(stat -c %Y $out_file);

    if [ $source_time -lt $out_time ]; then
		echo "Log: Reuse compiled file & Start running"
        run $out_file $lang
        exit 0
    fi
fi

if [[ ! "py|java" =~ $lang ]]; then
	echo -e "Log: Start compiling\n"
fi

# compile($1=path, $2=out_file, $3=lang)
compile() {
	path=$1
	out_file=$2
	lang=$3

	if [ $lang = "py" ]; then
		return 0
	fi

	start_time=$(date +%s%N)

	if [ $lang = "cpp" ]; then
		g++ $path -Wall -O2 -o $out_file
	elif [ $lang = "c" ]; then
		gcc $path -Wall -O2 -o $out_file
	elif [ $lang = "java" ]; then
		javac $path
	elif [ $lang = "kt" ]; then
		kotlinc $path -include-runtime -d $out_file
	fi

	if [ $? != 0 ]; then
		return 3
	fi

	end_time=$(date +%s%N)

	echo -e "Log: Compilation time: $(( (end_time - start_time) / 1000000 ))ms\n"
}

compile $path $out_file $lang && run $out_file $lang
