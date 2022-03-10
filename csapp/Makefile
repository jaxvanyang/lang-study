replace_byte : replace_byte.c
	gcc -o replace_byte replace_byte.c

mix_words : mix_words.c
	gcc -o mix_words mix_words.c

is_little_endian : is_little_endian.c
	gcc -o is_little_endian is_little_endian.c

show_bytes : show_bytes.c
	gcc -o show_bytes show_bytes.c

.PHONY : clean

clean :
	- rm *.out *.o *.s show_bytes is_little_endian mix_words replace_byte
