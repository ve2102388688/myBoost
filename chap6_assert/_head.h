#include <iostream>

constexpr size_t length(size_t size){
    return size > 16 ? 0 : 4 * size;
}

const int size = 10;
const int arr[length(size)] = {};