# Compiler
CC = g++
# CPPFLAGS = -Wall -Werror -Wunused -O2 -g

# Project name
PROJECT = nmr_ana 

# Directories
OBJDIR = obj
SRCDIR = src
INCDIR = include 
# options 
CPPFLAGS = -Wall -I$(INCDIR) -O2 -g  \
       -Wmissing-declarations -Wreturn-type -Wunused \
       -Wcomment -Wformat

# Libraries
LIBS = -lm 

# Files and folders
SRCS    = $(shell find $(SRCDIR) -name '*.cpp')
SRCDIRS = $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
OBJS    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS    = $(patsubst $(SRCDIR)/%.cpp,$(INCDIR)/%.h,$(SRCS))

# Targets
$(PROJECT): buildrepo $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# $(OBJDIR)/main.o: $(DEPS) 

.PHONY: clean
clean:
	rm -Rf $(PROJECT) $(OBJDIR) $(SRCDIR)/*~  *~ 

buildrepo:
	@$(call make-repo)

# Create obj directory structure
define make-repo
	mkdir -p $(OBJDIR)
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef

