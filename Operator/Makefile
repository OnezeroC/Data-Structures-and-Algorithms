CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

# Source files
SRCS = main.cpp expression_evaluator.cpp
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = main

# Default rule
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

report:
	xelatex report.tex report.pdf

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET) report.pdf *.aux *.log

# Phony targets
.PHONY: all clean run report