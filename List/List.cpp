#include <iostream>
#include "List.h"

int main() {
    // 测试构造函数
    List<int> myList{10, 20, 30, 40, 50};
    std::cout << "Initial list: ";
    for (const auto &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // 测试 push_back, push_front
    myList.push_back(60);
    myList.push_front(5);
    std::cout << "List after push_back(60) and push_front(5): ";
    for (const auto &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // 测试 pop_back, pop_front
    myList.pop_back();
    myList.pop_front();
    std::cout << "List after pop_back() and pop_front(): ";
    for (const auto &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // 测试 front 和 back
    std::cout << "Front element: " << myList.front() << std::endl;
    std::cout << "Back element: " << myList.back() << std::endl;

    // 测试 insert
    auto it = myList.begin();
    ++it; // 指向第二个元素
    myList.insert(it, 25);
    std::cout << "List after insert(25): ";
    for (const auto &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // 测试 erase
    it = myList.begin();
    ++it; // 指向第二个元素
    myList.erase(it);
    std::cout << "List after erase second element: ";
    for (const auto &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // 测试 size 和 empty
    std::cout << "List size: " << myList.size() << std::endl;
    std::cout << "Is list empty? " << (myList.empty() ? "Yes" : "No") << std::endl;

    // 测试移动构造函数和赋值运算符
    List<int> movedList = std::move(myList);
    std::cout << "Moved list: ";
    for (const auto &x : movedList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    std::cout << "Original list size after move: " << myList.size() << std::endl;

    // 测试 clear
    movedList.clear();
    std::cout << "Moved list size after clear: " << movedList.size() << std::endl;

    return 0;
}
