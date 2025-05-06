#include <iostream>
#include "../include/uniqueptr.hpp"

int main() {
    my_smart_ptr::UniquePtr<int> p(new int(42));
    if (p) {
        std::cout << "Value: " << *p << std::endl;
    }

    my_smart_ptr::UniquePtr<int[]> arr(new int[3]{1, 2, 3});
    for (size_t i = 0; i < 3; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    int* raw = p.release();
    if (!p) std::cout << "Pointer released, raw value = " << *raw << std::endl;
    delete raw;

    arr.reset();

    return 0;
}