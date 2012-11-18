Q = @
OBJS=	main.o hog.o rdl.o file.o log.o log_driver_raw.o config.o \
	hogmanager.o fstreamptr.o math.o log_driver.o log_driver_file.o \
	connection.o packets.o connectionmanager.o mission.o missionmanager.o \
	xml.o network.o
SOURCES=$(OBJS:.o=.cpp)
DEPENDS=$(SOURCES:.cpp=.d)
TESTOBJS=	test_main.o testbase.o test_hog.o test.o testManager.o
TESTSOURCES=$(TESTOBJS:.o=.cpp)
TESTDEPENDS=$(TESTSOURCES:.cpp=.d)
DEFINES=-DDEBUG -DVERSION=\"0.01a\"
LIBS=-lxml2 -llua5.1
CC=g++
BIN=descent-bot
TESTBIN=testdescent-bot
CFLAGS=-Wall -pedantic -g -I/usr/include/libxml2 -std=c++0x
#-fpack-struct -fno-exceptions

.PHONY: all test

all: $(BIN)

documentation:$(BIN)
	@echo "Generating documentation..."
	$(Q)doxygen

$(BIN):$(OBJS)
	@echo "Linking $@..."
	$(Q)$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN)

$(TESTBIN):$(TESTOBJS)
	@echo "Linking $@..."
	$(Q)$(CC) $(CFLAGS) $(TESTOBJS) $(LIBS) -o $(TESTBIN)

%.h:
	@echo FORCING DEPENDENCY CHECK - HEADERFILE $@ MISSING
	$(Q)rm -f *.d

%.o: %.cpp %.d
	@echo "Compiling $<..."
	$(Q)$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@
	#temporarly disable the static analysis
	#@cppcheck $<

%.d: %.cpp
	@echo "Generating $@..."
	$(Q)set -e; $(CC) -M $(CFLAGS) $< | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@
	$(Q)test -s $@ || rm -f $@

-include $(SOURCES:.cpp=.d)

-include $(TESTSOURCES:.cpp=.d)

clean:
	@echo "Cleaning Files..."
	$(Q)-rm -rf *~ $(OBJS) $(BIN) $(TESTOBJS) $(TESTBIN)

mrproper: clean
	@echo "Removing dependancies..."
	$(Q)-rm -rf $(DEPENDS) $(TESTDEPENDS)
	@echo "Removing documentation..."
	$(Q)-rm -rf documentation/*

test: $(BIN) $(TESTBIN)
	$(Q)./testdescent-bot

createConfig:
	@echo "Creating config/Main.xml from example..."
	$(Q)cp config/Main.xml.example config/Main.xml
