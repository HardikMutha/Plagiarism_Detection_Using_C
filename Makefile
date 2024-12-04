# Shell
SHELL = /bin/bash

# compiler
CC = gcc

# compiler flags
CFLAGS = -Wall
CFLAGS2 = `pkg-config --cflags --libs poppler-glib`
CFLAGS3 = -lm

# source files
SRCS1 = Proto_1_txt_file/txt_comparison.c
SRCS2 = Proto_2_c_file/Tokenizer/flex_script.c
SRCS3 = Proto_2_c_file/generateOutputs.c
SRCS4 = Proto_2_c_file/c_comparison.c


# helper files
HLP1 = Proto_1_txt_file/PDF_Parser/pdf_parser.c
HLP2 = Proto_2_c_file/Tokenizer/lexical_analyzer_copy.l
HLP3 = Proto_2_c_file/DLL/dll.c
HLP4 = Proto_2_c_file/SLL/sll.c
HLP5 = GraphPlot/PbPlots/pbPlots.c
HLP6 = GraphPlot/PbPlots/supportLib.c
TEST_DIR = Outputs/Tests

# lexer byproducts
LEX1 = lexer
LEX2 = lex.yy.c

# target files
TARGET1 = Outputs/txt_comparison
TARGET2 = Outputs/flex_tool
TARGET3 = Outputs/output_generator
TARGET4 = Outputs/c_comparison

#arguments
TYPE = $(type)
DIR = $(directory)

# execution:
# 	- For text files:
# 		-> compile txt_comparison with pdf_parser
# 		-> execute txt_comparison with argument <dir_name>
#
# 	- For c files:
# 		-> compile flex_script into flex_tool
# 		-> compile c_comparison
# 		-> store files in given directory to an array
# 		-> execute flex_tool with argument <dir_name> and lexical_analyzer
# 		-> execute c_comparison with argument <dir_name> (Tests)
# 		   { Tests: Directory in which the files will be stored after lexical analysis (outputs) }
# 		   { names of these files will be stored in Filenames.txt }
# (change karaychay c execution explanation)
all:

ifeq ($(TYPE), txt)
# txt files
	$(CC) $(CFLAGS) $(SRCS1) $(HLP1) -o $(TARGET1) $(CFLAGS2)
	./$(TARGET1) $(DIR)

else ifeq ($(TYPE), c)
# c files
	$(CC) $(CFLAGS) $(SRCS2) -o $(TARGET2)
	$(CC) $(CFLAGS) $(SRCS3) -o $(TARGET3)
	$(CC) -w $(SRCS4) $(HLP3) $(HLP4) $(HLP5) $(HLP6) -o $(TARGET4) $(CFLAGS3)
	./$(TARGET3) $(DIR)
	ls Outputs/Tests > Outputs/FileNames.txt
	./$(TARGET4) $(TEST_DIR)

else
	echo "Invalid type"
	exit 1
endif

clean:
	rm -rf $(LEX1) $(LEX2)
