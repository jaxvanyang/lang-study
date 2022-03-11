int_shifts_are_arithmetic : int_shifts_are_arithmetic.c
	gcc -Wall -o int_shifts_are_arithmetic int_shifts_are_arithmetic.c

solution_2_61 : solution_2_61.c
	gcc -Wall -o solution_2_61 solution_2_61.c

replace_byte : replace_byte.c
	gcc -Wall -o replace_byte replace_byte.c

mix_words : mix_words.c
	gcc -Wall -o mix_words mix_words.c

is_little_endian : is_little_endian.c
	gcc -Wall -o is_little_endian is_little_endian.c

show_bytes : show_bytes.c
	gcc -Wall -o show_bytes show_bytes.c

.PHONY : clean

clean :
	- rm *.out *.o *.s show_bytes is_little_endian mix_words \
		replace_byte solution_2_61 int_shifts_are_arithmetic
	- del *.exe *.o *.s show_bytes is_little_endian mix_words \
		replace_byte solution_2_61 int_shifts_are_arithmetic
