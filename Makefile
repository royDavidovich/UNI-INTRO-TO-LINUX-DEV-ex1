# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Directories
SRCDIR := .
OBJDIR := obj
BINDIR := bin

# Source and object files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
EXES := $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%,$(SRCS))

# Default target
all: $(BINDIR) $(OBJDIR) $(EXES)

# Compile each source file to an executable
$(BINDIR)/%: $(OBJDIR)/%.o
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile source file to object file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they don’t exist
$(BINDIR) $(OBJDIR):
	mkdir -p $@

# Clean up
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
