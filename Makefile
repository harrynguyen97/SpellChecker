# Put your project's name right here
# This will generate an execitive file whose name $(PROJECT_NAME)
PROJ_NAME = main

CC = g++

# Directory of object libraries
LIB_OBJ_DIR = lib/build

# Directory of library source file
LIB_SRC_DIR = lib/src

# Directory of header used for library source file
LIB_INC_DIR = lib/inc

# General flags for CPP compiler
CPP_FLAGS = -O2 -Wall -DNDEBUG -I$(LIB_INC_DIR) $(EXTRA_OPTIONS) 

# Flags for generate object library
LIB_FLAGS = -c 

# Flags for debugging
DEBUG_FLAGS = -g -Wall -I$(LIB_INC_DIR)

# Flag for output executive file
OUTPUT_FLAGS = -o

# Get all source files in /lib/src and its subdirectories 
SOURCE_LIBS = $(wildcard $(LIB_SRC_DIR)/**/*.cpp $(LIB_SRC_DIR)/*.cpp)

# Get all header files in lib/inc and its subdirectories
HEADER_LIBS = $(wildcard $(LIB_INC_DIR)/**/*.hpp $(LIB_INC_DIR)/*.hpp)

# Get all object files by substituting .cpp by .o
# More info: See "patsubst in Makefile"
OBJ_LIBS = $(patsubst $(LIB_SRC_DIR)/%.cpp, $(LIB_OBJ_DIR)/%.o, $(SOURCE_LIBS))


# All necessary files and directories for project
WORKING_FILES = LICENSE README.md
WORKING_DIRS = bin lib $(LIB_OBJ_DIR) $(LIB_SRC_DIR) $(LIB_INC_DIR) src test

MAKEFILE_TEST_LINK = \
	https://raw.githubusercontent.com/harrynguyen97/CppSkeleton-/master/test_skeleton/Makefile

all: $(OBJ_LIBS) $(PROJ_NAME)

# Compile object libraries 
$(OBJ_LIBS): $(SOURCE_LIBS) $(HEADER_LIBS)
	@echo Building object libraries...
	@$(CC) $(CPP_FLAGS) $(LIB_FLAGS) $(SOURCE_LIBS)

	@# Move *.o to lib/build because g++ can not generate multiple .o file
	@# into a designated directory
	@mv *.o -v $(LIB_OBJ_DIR)

	@echo Finished.

# Compile executive file from src/main.cpp whose name $(PROJECT_NAME)
$(PROJ_NAME): $(SOURCE_LIBS) $(HEADER_LIBS) 
	@echo Building executive files...
	@$(CC) $(CPP_FLAGS) src/main.cpp $(OBJ_LIBS) $(OUTPUT_FLAGS) $@
	@echo Finished.

# Make necessary directories and file
configure:
	@echo Creating working files and directories...
	@mkdir -p $(WORKING_DIRS)
	@touch $(WORKING_FILES)
	@echo Finished.

	@# Download Makefile for Unit Testing from Github
	@$(RM) test/Makefile
	@echo Download necessary files...
	@wget -P test/ $(MAKEFILE_TEST_LINK)

	@# Make the Makefile in test for unit testing
	@# make -C <dir> <option> is for changing the directory for multiple make
	@make -C test configure 
	
	@echo Finished

# For debugging purpose.
debug: 
	@echo Create debuging file...

	@# Generate a.out
	@$(CC) $(DEBUG_FLAGS) src/main.cpp $(OBJ_LIBS) 
	
	@# Move a.out to bin/ because g++ does not provide any way to
	@# generate a.out file into a specific directory
	@mv a.out bin/

	@echo Finished.
	@echo Debugging mode.
	
	@# Debug
	@gdb bin/a.out 

.PHONY: clean
clean: 
	@echo Cleaning following files: [$(OBJ_LIBS) $(PROJ_NAME)]...
	@$(RM) -rf $(OBJ_LIBS) $(PROJ_NAME)
	@echo Finished.