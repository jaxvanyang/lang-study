# Just like Code Runner
# Reference: https://stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash

run_out() {
    if [ -e data.in ]; then
        ./$1 < data.in
    else
        ./$1
    fi
}

full_name=$1;
file_name=${full_name%.*};
extension=${full_name##*.};
out_file=$file_name.out;

if [ ! -e $full_name ]; then
    echo "Error: file not exist!";
    exit 1;
fi

if [ -e $out_file ]; then
    source_time=$(stat -c %Y  $full_name);
    out_time=$(stat -c %Y $out_file);
    if [ $source_time -lt $out_time ]; then
        run_out $out_file
        exit 0
    fi
fi

g++ $full_name -Wall -O2 -o $out_file && run_out $out_file