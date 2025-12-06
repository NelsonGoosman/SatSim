# Purpose: This file contains C compiling options.

# Define macros
APPNAME     = TleReepoch
SUFFIX      = 
SOURCE      = ./src
RELEASEDIR  = ./bin
OBJDIR      = ./obj
SERVICES    = ../services
WRAPPERS    = ../wrappers

# Create the obj and bin directories if they don't exist
ifeq ($(OS), WindowsNT)
    MKDIR = mkdir
else
    MKDIR = mkdir -p

    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SUFFIX = _mac
    endif
endif

$(shell ${MKDIR} ${OBJDIR})
$(shell ${MKDIR} ${RELEASEDIR})

# DHN 31Oct2019 - add new VPATH variable which is to specify the search path (separated by colons or blanks).
# Order in which directories are listed is the order followed by make in its search
VPATH = $(SOURCE):$(SERVICES):$(WRAPPERS)


# compiling options
# -lm : linking with math library libm.so
# -lc : linking with standard C library libc.so
# -ldl: linking with library contains dlopen, dlclose, dlsym...
# -c  : compile only

CC     = gcc
CFLAGS = -c 
CLIB   = -ldl -lc -lm


### TleReepoch Objects ###
OBJS= \
	$(OBJDIR)/TimeFuncDll_Service.o \
	$(OBJDIR)/DllUtils.o \
	$(OBJDIR)/DllMainDll_Service.o \
	$(OBJDIR)/TleDll.o \
	$(OBJDIR)/TimeFuncDll.o \
	$(OBJDIR)/Sgp4PropDll.o \
	$(OBJDIR)/EnvConstDll.o \
	$(OBJDIR)/DllMainDll.o \
	$(OBJDIR)/AstroFuncDll.o \
	$(OBJDIR)/AstroFuncDll_Service.o


### Build Application ###
$(APPNAME): $(OBJS)
	$(CC) -m64 $(SOURCE)/$(APPNAME).c -o $(RELEASEDIR)/$(APPNAME)$(SUFFIX) $(OBJS) $(CLIB)

### Compile source files into object file (.o's) ###
### using implicit rules (Inference Rules) ###
$(OBJDIR)/%.o: %.c
	$(CC) -m64 $(CFLAGS) $< -o $@


clean:
	rm -f $(OBJDIR)/*.o
	rm -f *.mod


all : clean $(APPNAME)
