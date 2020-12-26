
CC = g++

# Compiler Flags
CFLAGS = -g -Wall -std=c++11 -D_GNU_SOURCE
# Linking flags
LDFLAGS = -lncurses 

# Setup flags from wildcards
SOURCES := $(filter-out src/main.cpp, $(filter-out src/test.cpp, $(wildcard src/*.cpp))) # get all cpp files excluding main and test
INCLUDES := $(wildcard src/*.h)
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)

# Compile Tests
test: obj/test.o $(OBJECTS)
	$(CC) $(CFLAGS) obj/test.o $(OBJECTS) -o $@ $(LDFLAGS)

# Compile main
main: obj/main.o $(OBJECTS)
	$(CC) $(CFLAGS) obj/main.o $(OBJECTS) -o main $(LDFLAGS)
 			
#build test
obj/test.o: src/test.cpp | obj
	$(CC) $(CFLAGS) -c $< -o $@
			
# build main
obj/main.o: src/main.cpp | obj
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS): obj/%.o : src/%.cpp | obj
	$(CC) $(CFLAGS) -c $< -o $@

format:
	cd src && clang-format -i *.cpp *.h

# Create object folder if it does not exist
obj:
	mkdir $@

clean:
	@-rm -f test
	@-rm -f main
	@-rm -rf obj


run:  main
	./main

