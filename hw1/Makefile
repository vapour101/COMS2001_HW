#################
#   variables   #
#################

# files
EXECUTABLE  = shell
OBJECTS  = main.o shell.o process.o io.o parse.o 

# flags
WARN	= -Wall -Wextra -pedantic
CFLAGS  = -ggdb3 $(WARN)

#################
#     targets   #
#################

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)

# remove object files and executable
clean:
	rm -f *.o $(EXECUTABLE)

# phony targets
.PHONY: clean
