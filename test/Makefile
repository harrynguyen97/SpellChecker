CC = g++

# Flag for building .o file 
# used for speeding up compiling time of Catch unit test framework
OBJ_FLAGS = -c

# Name of test
# Pass by make TEST_NAME=<name_of_your_test>
# used for build multiple executive test files which named name_of_your_test 
TEST_NAME = example

# Include header files for testing 
# Iinc includes catch.hpp
INC = -I../lib/inc -Iinc

# General flags for compiling executive file
CPP_FLAGS = -O2 -Wall $(INC)

# This object file used for speeding up Catch unit test
# speed_up_test.o is packed 
OBJ_SPEED_UP_TEST = speed_up_test.o

# Speed up unit test source file
SRC_SPEED_UP_TEST = src/speed-up-test/speed_up_test.cpp

# Name of test with the format test_<name_of_your_test>
# pass by make TEST_NAME=<name_of_your_test>
TEST_SRC_FILE = src/test_$(TEST_NAME).cpp

# Name of object file name_of_your_test.o used 
# for compiling test_<name_of_your_test>
OBJ_FILE = ../lib/build/*.o

# Github link github to speed_up_test.cpp
SPEED_UP_CPP = \
	https://raw.githubusercontent.com/harrynguyen97/CppSkeleton-/master/test_skeleton/speed_up_test.cpp

# Github link to catch.hpp
CATCH_HPP = \
	https://raw.githubusercontent.com/harrynguyen97/CppSkeleton-/master/test_skeleton/catch.hpp

all: test_$(TEST_NAME)

configure: skeleton speed

# Build speed_up_test.o
speed: $(SRC_SPEED_UP_TEST)
	@echo Speeding up testing...
	@$(CC) $(OBJ_FLAGS) $(INC) $(SRC_SPEED_UP_TEST)

	@# Move speed_up_test.o to build cus g++ does not support 
	@# compile .o file to a designated directory.
	@mv $(OBJ_SPEED_UP_TEST) build
	@echo Finished.

# Build test_<name_of_your_test> executive file
# Passed by make TEST_NAME=<name_of_your_test>
test_$(TEST_NAME): $(TEST_SRC_FILE)
	@echo Building executive test file 
	$(CC) $(CPP_FLAGS) $(TEST_SRC_FILE) $(OBJ_FILE) build/$(OBJ_SPEED_UP_TEST) -o $@
	@echo Finished.

# Make necessary directories for unit testing
# and download files from harrynguyen97 github (it's mine)
skeleton: 
	@echo Creating working files and directories...
	@mkdir -p build inc src src/speed-up-test 
	@echo Finished.

	@$(RM) src/speed-up-test/speed_up_test.cpp inc/catch.hpp
	@echo Download necessary files...
	@wget -P src/speed-up-test $(SPEED_UP_CPP)
	@wget -P inc $(CATCH_HPP)
	@echo Finished

.PHONY: clean
clean:
	@echo Cleaning executive test files...
	@$(RM) -rf test_$(TEST_NAME)
	@echo Finished.
