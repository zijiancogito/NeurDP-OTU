ifndef VERBOSE
	QUIET:=@
endif

LLVM_CONFIG?=llvm-config-10
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
LDFLAGS+=-ldl -ltinfo -lpthread -L. -lLLVM-10 -ljsoncpp -lpthread -lgflags
COMMON_FLAGS=-Wall -Wextra -fno-rtti
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

LLVMLIBS=$(shell $(LLVM_CONFIG) --libs --system-libs)

SOURCEDIR = ./
BUILDDIR = build
INCLUDEDIR = ./



SOURCE = parser

OBJECT = $(join $(addsuffix $(BUILDDIR)/, $(dir $(SOURCE))), $(notdir $(SOURCE:=.o)))

OBJDUMPSRC = llvm-objdump
OBJDUMPOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(OBJDUMPSRC))), $(notdir $(OBJDUMPSRC:=.o)))
OBJDUMPEXE = $(OBJDUMPSRC)

COFFSRC = COFFDump
COFFOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(COFFSRC))), $(notdir $(COFFSRC:=.o)))
COFFEXE = $(COFFSRC).so

ELFSRC =  ELFDump
ELFOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(ELFSRC))), $(notdir $(ELFSRC:=.o)))

MACHSRC = MachODump
MACHOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(MACHSRC))), $(notdir $(MACHSRC:=.o)))

WASMSRC = WasmDump
WASMOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(WASMSRC))), $(notdir $(WASMSRC:=.o)))

MAINSRC = main
MAINOBJ = $(join $(addsuffix $(BUILDDIR)/, $(dir $(MAINSRC))), $(notdir $(MAINSRC:=.o)))
MAINEXE = objdump

all: default

default: directory $(OBJECT) $(OBJDUMPOBJ) $(WASMOBJ) $(MACHOBJ) $(ELFOBJ) $(COFFOBJ) $(MAINOBJ)
	$(QUIET) $(CXX) -I$(INCLUDEDIR) -o $(MAINEXE) $(CXXFLAGS) $(OBJDUMPOBJ) $(OBJECT) $(WASMOBJ) $(MACHOBJ) $(ELFOBJ) $(COFFOBJ) $(MAINOBJ) $(LLVMLIBS) $(LDFLAGS)

	
directory:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	@echo Compiling $*.cpp
	$(QUIET) $(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $<



clean:
	$(QUIET)rm -rf $(OBJDUMPEXE) $(BUILDDIR)
