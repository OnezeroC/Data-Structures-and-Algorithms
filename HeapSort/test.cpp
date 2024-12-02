#include <iostream>
#include <vector>
#include <algorithm>  // For std::make_heap, std::sort_heap
#include <chrono>     // For time measurement
#include <random>     // For generating random sequences
#include "HeapSort.h"

// 检查排序是否正确
template <typename T>
bool check(const std::vector<T>& data) {
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i - 1] > data[i]) {
            return false;  // 如果前一个元素大于后一个元素，返回 false
        }
    }
    return true;
}

// 用于生成随机序列的辅助函数
std::vector<int> generateRandomSequence(size_t size) {
    std::vector<int> seq(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);  // 随机数范围
    for (size_t i = 0; i < size; ++i) {
        seq[i] = dis(gen);
    }
    return seq;
}

// 用于生成有序序列的辅助函数
std::vector<int> generateSortedSequence(size_t size) {
    std::vector<int> seq(size);
    for (size_t i = 0; i < size; ++i) {
        seq[i] = i;
    }
    return seq;
}

// 用于生成逆序序列的辅助函数
std::vector<int> generateReverseSortedSequence(size_t size) {
    std::vector<int> seq(size);
    for (size_t i = 0; i < size; ++i) {
        seq[i] = size - i - 1;
    }
    return seq;
}

// 用于生成部分重复序列的辅助函数
std::vector<int> generatePartiallyDuplicateSequence(size_t size) {
    std::vector<int> seq(size);
    for (size_t i = 0; i < size; ++i) {
        seq[i] = i % 1000;  // 生成每1000个元素重复的序列
    }
    return seq;
}

int main() {
    size_t sequence_size = 1000000;  // 测试序列的大小

    // 测试随机序列
    std::vector<int> random_seq = generateRandomSequence(sequence_size);
    std::cout << "Testing random sequence..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    HeapSort<int> heapSortRandom(random_seq);
    heapSortRandom.sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "HeapSort time: " << duration.count() << " seconds" << std::endl;
    std::cout << "Check: " << (check(random_seq) ? "Passed" : "Failed") << std::endl;

    // 与 std::sort_heap 进行对比
    std::vector<int> random_seq_copy = random_seq;
    std::make_heap(random_seq_copy.begin(), random_seq_copy.end());  // 先构建堆
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(random_seq_copy.begin(), random_seq_copy.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "std::sort_heap time: " << duration.count() << " seconds" << std::endl << std::endl;

    // 测试有序序列
    std::vector<int> sorted_seq = generateSortedSequence(sequence_size);
    std::cout << "Testing sorted sequence..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    HeapSort<int> heapSortSorted(sorted_seq);
    heapSortSorted.sort();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "HeapSort time: " << duration.count() << " seconds" << std::endl;
    std::cout << "Check: " << (check(sorted_seq) ? "Passed" : "Failed") << std::endl;

    // 与 std::sort_heap 进行对比
    std::vector<int> sorted_seq_copy = sorted_seq;
    std::make_heap(sorted_seq_copy.begin(), sorted_seq_copy.end());  // 先构建堆
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(sorted_seq_copy.begin(), sorted_seq_copy.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "std::sort_heap time: " << duration.count() << " seconds" << std::endl << std::endl;

    // 测试逆序序列
    std::vector<int> reverse_sorted_seq = generateReverseSortedSequence(sequence_size);
    std::cout << "Testing reverse sorted sequence..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    HeapSort<int> heapSortReverse(reverse_sorted_seq);
    heapSortReverse.sort();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "HeapSort time: " << duration.count() << " seconds" << std::endl;
    std::cout << "Check: " << (check(reverse_sorted_seq) ? "Passed" : "Failed") << std::endl;

    // 与 std::sort_heap 进行对比
    std::vector<int> reverse_sorted_seq_copy = reverse_sorted_seq;
    std::make_heap(reverse_sorted_seq_copy.begin(), reverse_sorted_seq_copy.end());  // 先构建堆
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(reverse_sorted_seq_copy.begin(), reverse_sorted_seq_copy.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "std::sort_heap time: " << duration.count() << " seconds" << std::endl << std::endl;

    // 测试部分重复序列
    std::vector<int> partially_duplicate_seq = generatePartiallyDuplicateSequence(sequence_size);
    std::cout << "Testing partially duplicate sequence..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    HeapSort<int> heapSortDuplicate(partially_duplicate_seq);
    heapSortDuplicate.sort();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "HeapSort time: " << duration.count() << " seconds" << std::endl;
    std::cout << "Check: " << (check(partially_duplicate_seq) ? "Passed" : "Failed") << std::endl;

    // 与 std::sort_heap 进行对比
    std::vector<int> partially_duplicate_seq_copy = partially_duplicate_seq;
    std::make_heap(partially_duplicate_seq_copy.begin(), partially_duplicate_seq_copy.end());  // 先构建堆
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(partially_duplicate_seq_copy.begin(), partially_duplicate_seq_copy.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "std::sort_heap time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
