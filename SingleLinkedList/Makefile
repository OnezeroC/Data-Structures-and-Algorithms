# 编译器
CXX = g++

# 编译选项
CXXFLAGS = -std=c++11 -Wall -g

# 可执行文件的名称
TARGET = main

# 源文件
SRCS = main.cpp

# 生成的对象文件
OBJS = $(SRCS:.cpp=.o)

# 默认规则：编译并生成可执行文件
all: $(TARGET)

# 链接对象文件生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 编译每个cpp文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 运行可执行文件
run: all
	./$(TARGET)

# 清理生成的对象文件和可执行文件
clean:
	rm -f $(OBJS) $(TARGET)

# 伪目标，确保all和clean不会和同名文件冲突
.PHONY: all clean run
