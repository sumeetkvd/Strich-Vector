
#include <iostream>
#include <functional>

template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size;
    std::function<size_t(size_t)> size_func; // callback function

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), capacity(0), size(0), size_func(nullptr) { }

    Vector(std::function<size_t(size_t)> func) : data(nullptr), capacity(0), size(0), size_func(func) { }

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& element) {
        if (size == capacity) {
            size_t newCapacity;
            if (size_func) {
                newCapacity = size_func(capacity);
            }
            else {
                newCapacity = (capacity == 0) ? 1 : capacity * 2;
            }
            resize(newCapacity);
        }
        data[size++] = element;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void pop_back() {
        if (size == 0) {
            throw std::length_error("Cannot pop from empty vector");
        }
        size--;
    }

    size_t getSize() {
        return size;
    }

    size_t getCapacity() {
        return capacity;
    }
};

int main() {
    Vector<int> vec;

    vec.push_back(54);
    vec.push_back(80);
    vec.push_back(49);

    std::cout << "Vector size is: " << vec.getSize() << std::endl;
    std::cout << "Vector capacity is: " << vec.getCapacity() << std::endl;

    vec.pop_back();
    std::cout << "The poped value is: " << vec[1] << std::endl;

    // using user callback function
    Vector<int> vec2([](size_t current_size) { return current_size + 1; });
    vec2.push_back(22);
    vec2.push_back(10);
    vec2.push_back(04);

    std::cout << "Vector-2 (using user callback function) size is: " << vec2.getSize() << std::endl;
    std::cout << "Vector-2 (using user callback function) capacity is: " << vec2.getCapacity() << std::endl;
}
