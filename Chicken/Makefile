# 编译器
CXX = g++

# 编译选项
CXXFLAGS = -Wall -std=c++11

# 可执行文件名称
TARGET = Chicken

# 源文件
SRCS = Chicken.cpp

# 目标文件
OBJS = $(SRCS:.cpp=.o)

# 编译目标
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 编译源文件生成目标文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 运行程序
run: 
	./$(TARGET)
