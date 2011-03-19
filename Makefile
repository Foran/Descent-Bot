Q = @
OBJS=	main.o hog.o rdl.o file.o log.o log_driver_raw.o config.o \
	hogmanager.o fstreamptr.o math.o log_driver.o log_driver_file.o
SOURCES=$(OBJS:.o=.cpp)
DEPENDS=$(SOURCES:.cpp=.d)
DEFINES=-DDEBUG -DVERSION=\"0.01a\"
LIBS=-lxml2 -llua5.1
CC=g++
BIN=descent-bot
CFLAGS=-Wall -pedantic -g -I/usr/include/libxml2
#-fpack-struct -fno-exceptions

.PHONY: all test

all: $(BIN)

$(BIN):$(OBJS)
	@echo "Linking $@..."
	$(Q)$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN)
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
	$(Q)make -C test clean

mrproper: clean
	@echo "Removing dependancies..."
	$(Q)-rm -rf $(DEPENDS)
	$(Q)make -C test mrproper

test: $(BIN)
	$(Q)make -C test test

createConfig:
	@echo "Creating config/Main.xml from example..."
	$(Q)cp config/Main.xml.example config/Main.xml
