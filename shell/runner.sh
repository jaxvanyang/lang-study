# Just like Code Runner
# Reference: https://stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash

run_out() {
	if [ $2 = "kt" ]; then
		java -jar $1;
	else
		# TODO: remove ./
		./$1;
	fi
}

run() {
    if [ -e data.in ]; then
        run_out $1 $2 < data.in
    else
        run_out $1 $2
    fi
}

full_name=$1;
file_name=${full_name%.*};
extension=${full_name##*.};
export out_file=$file_name.out;
export lang="cpp";

if [ $extension = "kt" ]; then
	out_file=$file_name.jar
	lang="kt"
fi

if [ ! -e $full_name ]; then
    echo "Error: file not exist!";
    exit 1;
fi

if [ -e $out_file ]; then
    source_time=$(stat -c %Y  $full_name);
    out_time=$(stat -c %Y $out_file);
    if [ $source_time -lt $out_time ]; then
        run $out_file $lang
        exit 0
    fi
fi

if [ $lang = "cpp" ]; then
	g++ $full_name -Wall -O2 -o $out_file && run $out_file $lang;
elif [ $lang = "kt" ]; then
	kotlinc $full_name -include-runtime -d $out_file && run $out_file $lang;
fi
