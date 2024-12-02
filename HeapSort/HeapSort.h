#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <algorithm>  // For std::swap

// HeapSort 类实现堆排序算法
template <typename T>
class HeapSort {
public:
    // 构造函数，传入待排序的 vector
    HeapSort(std::vector<T>& data) : data_(data) {}

    // 排序函数，执行堆排序
    void sort() {
        buildMaxHeap();  // 第一步：构建最大堆
        for (int i = data_.size() - 1; i > 0; --i) {
            // 将堆顶元素（最大元素）交换到数组末尾
            std::swap(data_[0], data_[i]);
            // 调整堆，保持堆的性质
            maxHeapify(0, i);
        }
    }

private:
    std::vector<T>& data_;  // 引用待排序的 vector

    // 构建最大堆
    void buildMaxHeap() {
        // 从最后一个非叶子节点开始构建堆
        for (int i = data_.size() / 2 - 1; i >= 0; --i) {
            maxHeapify(i, data_.size());
        }
    }

    // 调整堆的性质，确保以 i 为根的子树是一个最大堆
    void maxHeapify(int i, int heapSize) {
        int left = 2 * i + 1;  // 左子节点索引
        int right = 2 * i + 2; // 右子节点索引
        int largest = i;       // 假设当前节点 i 是最大值

        // 如果左子节点存在且比当前最大值大，更新最大值的索引
        if (left < heapSize && data_[left] > data_[largest]) {
            largest = left;
        }

        // 如果右子节点存在且比当前最大值大，更新最大值的索引
        if (right < heapSize && data_[right] > data_[largest]) {
            largest = right;
        }

        // 如果最大值的索引不是当前节点 i，交换并递归调整子树
        if (largest != i) {
            std::swap(data_[i], data_[largest]);
            maxHeapify(largest, heapSize);  // 递归调整子树
        }
    }
};

#endif // HEAPSORT_H
