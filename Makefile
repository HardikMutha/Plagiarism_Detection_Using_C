# Shell
SHELL = /bin/bash

# compiler
CC = gcc

# compiler flags
CFLAGS = -Wall
CFLAGS2 = `pkg-config --cflags --libs poppler-glib`
CFLAGS3 = -lm

# source files
SRCS1 = TextPlagiarism/txt_comparison.c
SRCS2 = CPlagiarism/Tokenizer/flex_script.c
SRCS3 = CPlagiarism/generateOutputs.c
SRCS4 = CPlagiarism/c_comparison.c


# helper files
HLP1 = TextPlagiarism/PDF_Parser/pdf_parser.c
HLP2 = CPlagiarism/Tokenizer/lexical_analyzer.l
HLP3 = CPlagiarism/DLL/dll.c
HLP4 = CPlagiarism/SLL/sll.c
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
# 		-> compile generateOutputs into output_generator
# 		-> compile c_comparison with dll, sll, pbPlots and supportLib
# 		-> execute output_generator with argument <dir_name>
# 		-> list all files in Outputs/Tests and write them in Outputs/FileNames.txt
# 		-> execute c_comparison with arguments <test_dir> and <dir_name>

all:

ifeq ($(TYPE), txt)
# txt files
	$(CC) -w $(SRCS1) $(HLP1) $(HLP5) $(HLP6) -o $(TARGET1) $(CFLAGS2) $(CFLAGS3) 
	./$(TARGET1) $(DIR)

else ifeq ($(TYPE), $(filter $(TYPE), c C))
# c files
	$(CC) $(CFLAGS) $(SRCS2) -o $(TARGET2)
	$(CC) $(CFLAGS) $(SRCS3) -o $(TARGET3)
	$(CC) -w $(SRCS4) $(HLP3) $(HLP4) $(HLP5) $(HLP6) -o $(TARGET4) $(CFLAGS3)
	./$(TARGET3) $(DIR)
	ls Outputs/Tests > Outputs/FileNames.txt
	./$(TARGET4) $(TEST_DIR) $(DIR)

else
	echo "Invalid type"
	exit 1
endif

clean:
	rm -rf $(LEX1) $(LEX2) Outputs/FileNames Outputs/Tests/*
