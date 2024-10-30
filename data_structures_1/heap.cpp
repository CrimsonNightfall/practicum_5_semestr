#include <iostream>
#include <vector>

void SiftDown(std::vector<int>& arr, int heap_size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap_size && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < heap_size && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != index) {
        std::swap(arr[index], arr[largest]);
        SiftDown(arr, heap_size, largest);
    }
}

void HeapSort(std::vector<int>& arr) {
    int heap_size = arr.size();

    for (int i = heap_size / 2 - 1; i >= 0; --i) {
        SiftDown(arr, heap_size, i);
    }

    for (int i = heap_size - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        SiftDown(arr, i, 0);
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    HeapSort(arr);

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}