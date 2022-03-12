# The variable CC specifies which compiler will be used.
# (because different unix systems may use different compilers)
CC=gcc

# The variable CFLAGS specifies compiler options
#   -c :    Only compile (don't link)
#   -Wall:  Enable all warnings about lazy / dangerous C programming 
#   -std=gnu99: Using newer C99 version of C programming language
#               + GNU extensions (for random / srandom()
CFLAGS=-c -Wall -std=gnu99 -O2

# All of the .h header files to use as dependencies
HEADERS=matrix_math.h

# All of the object files to produce as intermediary work
OBJECTS=matrix_math.o

# The final program to build
EXECUTABLE=matrix_math

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
