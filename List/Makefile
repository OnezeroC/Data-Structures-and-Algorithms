# Variables
CXX = g++
CXXFLAGS = -std=c++20 -Wall
TARGET = List
TEX = xelatex
TEX_TARGET = report

# Default target
all: $(TARGET)

# Compile and link the test executable
$(TARGET): List.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) List.cpp

# Run the test executable
run: $(TARGET)
	./$(TARGET)

# Build the report
report: $(TEX_TARGET).tex
	$(TEX) $(TEX_TARGET).tex

view: $(TEX_TARGET).pdf
	evince $(TEX_TARGET).pdf

# Clean up the auxiliary files and the test executable
clean:
	rm -f $(TARGET) $(TEX_TARGET).aux $(TEX_TARGET).log $(TEX_TARGET).pdf

# Clean everything, including the report
distclean: clean
	rm -f $(TEX_TARGET).pdf
