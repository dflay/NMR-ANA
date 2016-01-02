# Compiler
CC = g++
# CPPFLAGS = -Wall -Werror -Wunused -O2 -g

# Project name
PROJECT = nmr_ana 

# Directories
OBJDIR = obj
SODIR  = lib  
SRCDIR = src
INCDIR = include 
# options 
CPPFLAGS = -Wall -I$(INCDIR) -O2 -g  \
       -Wmissing-declarations -Wreturn-type -Wunused \
       -Wcomment -Wformat
# shared object 
SOFLAGS = -shared  

# Libraries
LIBS        = -lm
LDLIBS      = 
LIBNAME    := NMR  
SOLIBNAMES := NMRANA
LIBRARY     = lib$(LIBNAME).so  
SOLIBS     := $(SOLIBNAMES:%=lib/lib%.so) 

# Files and folders
SRCS    = $(shell find $(SRCDIR) -name '*.cpp')
SRCDIRS = $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
OBJS    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS    = $(patsubst $(SRCDIR)/%.cpp,$(INCDIR)/%.h,$(SRCS))

# Targets
$(PROJECT): buildrepo $(OBJS)  
	$(CC) $(OBJS) $(LIBS) -o $@
# make objects
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
# make shared libraries (shared objects): doesn't work, and probably not what we want.  
# we want all objects created put into a single library called NMRANA.   
$(SODIR)/%.so: $(OBJDIR)/*.o
	$(CC) $(SOFLAGS) $^ -o $@

# $(OBJDIR)/main.o: $(DEPS) 

.PHONY: clean
clean:
	rm -Rf $(PROJECT) $(OBJDIR) $(SODIR) $(SRCDIR)/*~  *~ 

buildrepo:
	@$(call make-repo)

shared_libs: $(SOLIBNAMES) 
	@echo "===== Creating NMR Shared Library ===== " 
	g++ $(CPPFLAGS) $(SOFLAGS) -Wl,-soname,$(LIBRARY) -o so/$(LIBRARY) $(SOLIBS) $(LDLIBS)  

# Create obj directory structure
define make-repo
	for dir in $(SRCDIRS); \
	do \
	mkdir -p $(OBJDIR)/$$dir; \
	mkdir -p $(SODIR)/$$dir; \
	done
endef

