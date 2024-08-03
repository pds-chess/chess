CC          := g++
TARGET      := chessGame

SRCDIR      := chess
INCDIR      := include
BUILDDIR    := obj
TARGETDIR   := bin
SRCEXT      := cpp
OBJEXT      := o

CFLAGS      := -fopenmp -Wall -O3 -g
INC         := -I$(INCDIR)

SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(TARGET)

remake: cleaner all

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