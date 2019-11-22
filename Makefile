 all: 
		 gcc -g -Wall -Werror -fsanitize=address searchtest.c multitest_proc.c -o searchtest -std=c99 -lm
clean:
	 	rm -f *o searchtest        
    
    