Q = @
OBJS=	main.o test.o testManager.o testbase.o test_hog.o
PROJ_OBJS= ../hog.o ../file.o ../rdl.o ../fstreamptr.o ../log.o ../hogmanager.o
SOURCES=$(OBJS:.o=.cpp)
DEPENDS=$(SOURCES:.cpp=.d)
DEFINES=-DDEBUG
LIBS=-lxml2 -llua5.1
CC=g++
BIN=testDescent-Bot
CFLAGS=-Wall -pedantic -g -I/usr/include/libxml2 -I../
#-fpack-struct -fno-exceptions

.PHONY: all test

all: $(BIN)

$(BIN):$(OBJS)
	@make -C ../
	@echo "Linking $@..."
	$(Q)$(CC) $(CFLAGS) $(PROJ_OBJS) $(OBJS) $(LIBS) -o $(BIN)

%.h:
	@echo FORCING DEPENDENCY CHECK - HEADERFILE $@ MISSING
	$(Q)rm -f *.d

%.o: %.cpp %.d
	@echo "Compiling $<..."
	$(Q)$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@

%.d: %.cpp
	@echo "Generating $@..."
	$(Q)set -e; $(CC) -M $(CFLAGS) $< | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@
	$(Q)test -s $@ || rm -f $@

-include $(SOURCES:.cpp=.d)

clean:
	@echo "Cleaning Files..."
	$(Q)-rm -rf *~ $(OBJS) $(BIN)

mrproper: clean
	@echo "Removing dependancies..."
	$(Q)-rm -rf $(DEPENDS)

test: $(BIN)
	@echo "Starting Testing Sequence..."
	$(Q)./$(BIN)
