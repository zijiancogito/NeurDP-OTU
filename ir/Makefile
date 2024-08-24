ifndef VERBOSE
	QUIET:=@
endif

LLVM_CONFIG?=llvm-config-10
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
LDFLAGS+=-ldl -ltinfo -lpthread -L. -ljsoncpp -lgflags
COMMON_FLAGS=-Wall -Wextra -fno-rtti
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

LLVMLIBS=$(shell $(LLVM_CONFIG) --libs --system-libs)

SOURCEDIR = ./
BUILDDIR = build
INCLUDEDIR = ./

SOURCE = llformat
LLSIMSRC = llsimple

OBJECT = $(join $(addsuffix $(BUILDDIR)/, $(dir $(SOURCE))), $(notdir $(SOURCE:=.o)))

LLSIMOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(LLSIMSRC))), $(notdir $(LLSIMSRC:=.o)))

EXECUTABLE = $(SOURCE)
LLSIMEXE = $(LLSIMSRC).so

LLCOMSRC = llfull
LLCOMOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(LLCOMSRC))), $(notdir $(LLCOMSRC:=.o)))
LLCOMEXE = $(LLCOMSRC).so

LLJSONSRC = llsimple-json
LLJSONOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(LLJSONSRC))), $(notdir $(LLJSONSRC:=.o)))
LLJSONEXE = $(LLJSONSRC).so

all: default

default: directory $(OBJECT) $(LLSIMOBJ) $(LLCOMOBJ) $(LLJSONOBJ)
	@echo Linking Project
	$(QUIET) $(CXX) -I$(INCLUDEDIR) -shared -o $(LLSIMEXE) $(CXXFLAGS) $(LLSIMOBJ)  $(LLVMLIBS) $(LDFLAGS)
	$(QUIET) $(CXX) -I$(INCLUDEDIR) -shared -o $(LLCOMEXE) $(CXXFLAGS) $(LLCOMOBJ) $(LLVMLIBS) $(LDFLAGS)
	$(QUIET) $(CXX) -I$(INCLUDEDIR) -shared -o $(LLJSONEXE) $(CXXFLAGS) $(LLJSONOBJ) $(LLVMLIBS) $(LDFLAGS)
	$(QUIET) $(CXX) -I$(INCLUDEDIR) -o $(EXECUTABLE) $(CXXFLAGS) $(OBJECT) $(LLSIMOBJ) $(LLCOMOBJ) $(LLJSONOBJ) $(LLVMLIBS) $(LDFLAGS)
	

directory:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	@echo Compiling $*.cpp
	$(QUIET) $(CXX) -fPIC -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $<



clean:
	$(QUIET)rm -rf $(EXECUTABLE) $(BUILDDIR) $(LLSIMEXE) $(LLCOMEXE) $(LLJSONEXE)
