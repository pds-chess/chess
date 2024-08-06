CC          := g++
TARGET      := chessGame

SRCDIR      := chess
INCDIR      := include
BUILDDIR    := obj
TARGETDIR   := bin
SRCEXT      := cpp
OBJEXT      := o

CFLAGS      := -fopenmp -Wall -O3 -g
INC         := -I $(INCDIR)

SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
TESTSOURCES := $(filter-out chess/chess.cpp, $(SOURCES))
TESTOBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(TARGET)

remake: cleaner all

run: all
	./$(TARGETDIR)/$(TARGET)

directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

clean:
	@$(RM) -rf $(BUILDDIR) $(TARGETDIR)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

tests: directories test

test: $(TESTOBJECTS) obj/tests.o
	$(CC) $(INC) -o test/test $^
	./test/test

obj/tests.o: test/tests.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<