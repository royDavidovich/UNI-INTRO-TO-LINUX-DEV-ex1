# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -fPIC

# Directories
SRCDIR := src
OBJDIR := obj
BINDIR := bin

# Library
LIBNAME := libblockchain_utils.so
LIB     := $(OBJDIR)/$(LIBNAME)

# Executables
EXES    := printDatabase blockFinder refreshDatabase bitcoinShell

# Default: build library + all bins
all: $(BINDIR) $(OBJDIR) $(LIB) $(patsubst %,$(BINDIR)/%,$(EXES))
	@echo
	@echo "Build ended successfully!"

# 1) Build any .cpp → .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@

# 2) Link utils .o → shared library
$(LIB): $(OBJDIR)/blockchain_utils.o
	$(CXX) -shared -o $@ $^

# 3) Build executables:

# ─── Shared‐lib users with RPATH ───
$(BINDIR)/printDatabase: $(OBJDIR)/printDatabase.o $(LIB)
	$(CXX) $(CXXFLAGS) \
	      $< -L$(OBJDIR) -lblockchain_utils \
	      -Wl,-rpath,'$$ORIGIN/../obj' \
	      -o $@

$(BINDIR)/blockFinder:   $(OBJDIR)/blockFinder.o   $(LIB)
	$(CXX) $(CXXFLAGS) \
	      $< -L$(OBJDIR) -lblockchain_utils \
	      -Wl,-rpath,'$$ORIGIN/../obj' \
	      -o $@

# ─── Standalone tools ───
$(BINDIR)/refreshDatabase: $(OBJDIR)/refreshDatabase.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(BINDIR)/bitcoinShell:    $(OBJDIR)/bitcoinShell.o
	$(CXX) $(CXXFLAGS) $< -o $@

# Ensure output directories exist
$(BINDIR) $(OBJDIR):
	mkdir -p $@

# Clean up build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
