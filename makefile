SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
FLAG = -Wall -Wextra -Werror
FOLDER=tests_grep/
TEST_GREP_FILES = $(FOLDER)test_1_grep.txt $(FOLDER)test_2_grep.txt
TEST_GREP_FLAGS = -e -i -v -c -l -n -h -s -o
FILE = test.txt
s21_grep:grep.c parse_flags.c regex.c function.c
	gcc grep.c parse_flags.c regex.c function.c -o s21_grep

1:grep.c parse_flags.c regex.c function.c
	gcc -Wall -Werror -Wextra -std=c11 grep.c parse_flags.c regex.c function.c -o s21_grep	

2:prog4.c
	gcc prog4.c

3:grep.c parse_flags.c regex.c
	gcc grep_debug.c parse_flags.c regex.c -o s21_grep	

test:
	 -diff <(./s21_grep He $(FILE)) <(grep He $(FILE))
	 -diff <(./s21_grep -v He $(FILE)) <(grep -v He $(FILE))
	 -diff <(./s21_grep -i He $(FILE)) <(grep -i He $(FILE))
	 -diff <(./s21_grep -iv He $(FILE)) <(grep -iv He $(FILE))
	 -diff <(./s21_grep -in He $(FILE)) <(grep -in He $(FILE))
	 -diff <(./s21_grep -ie He $(FILE)) <(grep -ie He $(FILE))
	 -diff <(./s21_grep -ince "^he" $(FILE)) <(grep -ince "^he" $(FILE))
	 -diff <(./s21_grep -lh se $(FILE)) <(grep -lh se $(FILE))

	-diff <(./s21_grep $(FILE)) <(grep $(FILE))
	-diff <(./s21_grep $(FILE)) <(grep $(FILE))

extended_test_grep1:
	@echo "Running test: grep -f filepattern $(FOLDER)test_1_grep.txt"
	@./s21_grep -f $(FOLDER)pattern.txt $(FOLDER)test_1_grep.txt > s21_grep_output.txt
	@grep -f $(FOLDER)pattern.txt $(FOLDER)test_1_grep.txt > grep_output.txt
	@diff s21_grep_output.txt grep_output.txt

extended_test_grep2:
	@echo "Running test: grep -e pattern -e pattern -e pattern $(FOLDER)test_2_grep.txt"
	@ ./s21_grep -e hh -e And -e lol $(FOLDER)test_2_grep.txt > s21_grep_output.txt
	@grep -e hh -e And -e lol $(FOLDER)test_2_grep.txt > grep_output.txt
	@diff s21_grep_output.txt grep_output.txt

extended_test_grep3:
	@echo "Running test: grep -h pattern $(FOLDER)test_2_grep.txt $(FOLDER)test_1_grep.txt"
	@./s21_grep -h hh $(FOLDER)test_2_grep.txt $(FOLDER)test_1_grep.txt > s21_grep_output.txt
	@grep -h hh $(FOLDER)test_2_grep.txt $(FOLDER)test_1_grep.txt > grep_output.txt
	@diff s21_grep_output.txt grep_output.txt

extended_test_grep4:
	@echo "Running test: grep -s pattern $(FOLDER)test_2_grep.txt $(FOLDER)test_1_grep.txt"
	@./s21_grep -s hh $(FOLDER)test_2_grep.txt $(FOLDER)test_1_grep.txt > s21_grep_output.txt
	@grep -s hh $(FOLDER)test_2_grep.txt $(FOLDER)test_1_grep.txt > grep_output.txt
	@diff s21_grep_output.txt grep_output.txt

flags:
	gcc -Wall -Werror -Wextra -std=c11 grep.c parse_flags.c regex.c

debug:
	gcc -fsanitize=address grep.c parse_flags.c regex.c function.c

