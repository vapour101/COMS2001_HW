#################
#   variables   #
#################

# files
EXEC	= shell
OBJS	= main.o shell.o process.o io.o parse.o 

# flags
WARN	= -Wall -Wextra -pedantic
CFLAGS	= -ggdb3 $(WARN)

# rules
.DEFAULT_GOAL	= all
include $(OBJS:.o=.d)

#################
#     targets   #
#################

all: $(EXEC)

$(EXEC): $(OBJS)

# depency files
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# remove object files and executable
clean:
	rm -f $(OBJS) $(EXEC)

cleanall: clean
	rm -f $(OBJS:.o=.d)

# phony targets
.PHONY: clean all
