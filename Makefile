# Shell
SHELL := /bin/bash

# compiler
CC = gcc

# compiler flags
CFLAGS = -Wall
CFLAGS2 = `pkg-config --cflags --libs poppler-glib`
CFLAGS3 = -w

# source files
SRCS1 = Proto_1_txt_file/txt_comparison.c
SRCS2 = Proto_2_c_file/Tokenizer/flex_script.c
SRCS3 = Proto_2_c_file/c_comparison.c

# helper files
HLP1 = Proto_1_txt_file/PDF_Parser/pdf_parser.c
HLP2 = Proto_2_c_file/Tokenizer/lexical_analyzer_copy.l
HLP3 = Proto_2_c_file/DLL/dll.c
HLP4 = Proto_2_c_file/SLL/sll.c

# lexer byproducts
LEX1 = lexer
LEX2 = lex.yy.c
LEX3 = output.txt
LEXG = Proto_2_c_file/Tokenizer/

# outputs for c comparison
O1 = Outputs/output1.txt
O2 = Outputs/output2.txt

# target files
TARGET1 = Outputs/txt_comparison
TARGET2 = Outputs/flex_tool
TARGET3 = Outputs/c_comparison

# arguments
FILE1 = $(f1)
FILE2 = $(f2)

# execution:
# 	- checking for file formats
# 	- compiling for required file format 
# 	- execution with using arguments
#
# - txt file:
#  		-> compile txt_comparison with pdf_parser (with required flags)
#  		-> execute with arguments
#
# - C file:
#   	-> compile flex_tool (with required flags)
#   	-> execute with lexical_analyzer_copy and arguments (one by one)
#   	-> first execute for first argument then second
#   	-> for first execution output1.txt created
#   	-> for second execution output2.txt created
#   	-> compile c_comparison with dll and sll (with required flags)
#		-> execute with created output1.txt and output2.txt files
#
#

all: check_build

check_build: $(FILE1) $(FILE2)
	@if [ -z "$(FILE1)" ] || [ -z "$(FILE2)" ]; then \
		echo "Usage: make FILE1=<file1> FILE2=<file2>"; \
		exit 1; \
	else \
		if [[ "$(FILE1)" == *.txt || "$(FILE1)" == *.pdf ]] && [[ "$(FILE2)" == *.txt || "$(FILE2)" == *.pdf ]]; then \
			$(CC) $(SRCS1) $(HLP1) $(CFLAGS) $(CFLAGS2) -o $(TARGET1); \
			$(TARGET1) $(FILE1) $(FILE2); \
		elif [[ "$(FILE1)" == *.c ]] && [[ "$(FILE2)" == *.c ]]; then \
			$(CC) $(CFLAGS3) $(SRCS2) -o $(TARGET2); \
			$(TARGET2) $(HLP2) $(FILE1); \
			mv $(LEX3) $(O1); \
			$(TARGET2) $(HLP2) $(FILE2); \
			mv $(LEX3) $(O2); \
			$(CC) $(SRCS3) $(HLP3) $(HLP4) $(CFLAGS) -o $(TARGET3); \
			$(TARGET3) $(O1) $(O2); \
			rm -f $(LEX1) $(LEX2); \
		else \
			echo "File formats are not valid"; \
			exit 1; \
		fi; \
	fi; \
	 

# clean
clean:
	rm -f $(O1) $(O2) $(TARGET1) $(TARGET2) $(TARGET3)
