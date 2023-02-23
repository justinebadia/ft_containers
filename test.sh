#!/bin/bash

# -D<macroname>=<value>
#Adds an implicit #define into the predefines buffer which is read before the source file is preprocessed.
#


cpp_dir="tests"
obj_dir="objs"
log_dir="tests/logs"
output_dir="tests/output"
diff_dir="tests/diff"
err="errors.log"

flags="-Wall -Wextra -Werror -std=c++98"
container="$PWD/$1"

#checking if directory exists and delete it

if [ -d "$output_dir" ];then
	rm -rf $output_dir
fi 

if [ -d "$log_dir" ]; then
	rm -rf $log_dir
fi 

if [ -d "$diff_dir" ]; then
	rm -rf $diff_dir
fi 

if [ -d "$err" ]; then
	rm -rf $err
fi 

mkdir -p "$output_dir"
mkdir -p "$log_dir"
mkdir -p "$diff_dir"



# real = elapsed time from start to the end of the call
# user = amount of cpu time spent in user-mode code within the process
# sys = amount of time spent in the kernel within the process
# time -p is a command that runs another command and measures its execution time.
# bash -c invokes a new instance of the Bash shell and runs the following command inside it.
#
check_time()
{
	printf "FT_ :  \n"
	time -p bash -c "for (( i=0; i<2000; i++ )); do ./"$output_dir/ft_$b.out" > "$log_dir/ft_$b"; done;"
	printf "STD_ :  \n"
	time -p bash -c "for (( i=0; i<2000; i++ )); do ./"$output_dir/std_$b.out" > "$log_dir/std_$b"; done;"
}

run_container()
{
	c="$cpp_dir"/"$(basename $container)".cpp
	b=$(basename "${c%.cpp}")
	clang++ "$c" -DNAMESPACE=ft -o "$output_dir/ft_$b.out" 2>> "$err"
	clang++ "$c" -DNAMESPACE=std -o "$output_dir/std_$b.out" 2>> "$err"

	./"$output_dir/ft_$b.out" > "$log_dir/ft_$b" 2>> "$err"
	./"$output_dir/std_$b.out" > "$log_dir/std_$b" 2>> "$err"
	diff -u "$log_dir/ft_$b" "$log_dir/std_$b" > "$diff_dir/ft_$b_diff"

	# check_time

}

echo -n "" > $err

# checking the number of arguments
if [ $# == 1 ]; then
	if [ $1 == "stack" ]; then
		run_container
	elif [ $1 == "vector" ]; then
		run_container
	elif [ $1 == "map" ]; then
		run_container
	else
		echo -n "not a container"
	fi
else
	echo -n "choose one container: vector, map, stack"
fi