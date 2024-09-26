#include <iostream>
#include <cstring>

class Chicken
{
private:
    int age = 0;
    char *name = nullptr;

public:
    // 默认构造函数
    Chicken() = default;

    // 带年龄参数的构造函数
    Chicken(int _age) : age(_age) {}

    // 带年龄和名称参数的构造函数
    Chicken(int _age, const char *_name) : age(_age)
    {
        setName(_name);
    }

    // 复制构造函数
    Chicken(const Chicken &other) : age(other.age)
    {
        if (other.name)
        {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
    }

    // 赋值操作符
    Chicken &operator=(const Chicken &other)
    {
        if (this != &other)
        {
            age = other.age;
            delete[] name; // 先释放已有的内存
            if (other.name)
            {
                name = new char[strlen(other.name) + 1];
                strcpy(name, other.name);
            }
            else
            {
                name = nullptr; // 确保 name 为空指针
            }
        }
        return *this;
    }

    // 析构函数
    ~Chicken()
    {
        delete[] name; // 防止内存泄漏
    }

    // 设置年龄
    void setAge(int _age)
    {
        age = _age;
    }

    // 设置名称
    void setName(const char *_name)
    {
        delete[] name; // 先释放已有的内存
        if (_name)
        {
            name = new char[strlen(_name) + 1];
            strcpy(name, _name);
        }
        else
        {
            name = nullptr; // 确保 name 为空指针
        }
    }

    // 获取名称
    const char *getName() const
    {
        return name ? name : "Unnamed"; // 避免空指针解引用
    }

    // 获取年龄
    const int &getAge() const
    {
        return age;
    }
};

int main()
{
    Chicken c(24, "Kunkun");
    std::cout << "Hi, everyone! My name is " << c.getName() << ", I am " << c.getAge() << " years old." << std::endl;

    Chicken c2 = c; // 测试复制构造函数
    std::cout << "Hi, everyone! My name is " << c2.getName() << ", I am " << c2.getAge() << " years old." << std::endl;

    Chicken c3, c4;
    c4 = c3 = c; // 测试赋值操作符
    std::cout << "Hi, everyone! My name is " << c4.getName() << ", I am " << c4.getAge() << " years old." << std::endl;

    return 0;
}
