#pragma once

#include <algorithm>
#include <cstdlib>

using namespace std;
// Реализуйте шаблон SimpleVector
template<typename T>
class SimpleVector {
public:
    SimpleVector() :
            data(nullptr),
            capacity_(0),
            size_(0) {}

    explicit SimpleVector(size_t size) {
        data = new T[size];
        size_ = size;
        capacity_ = size;
    }

    SimpleVector(const SimpleVector &other)
        : data(new T[other.capacity_]),
          size_(other.size_),
          capacity_(other.capacity_) {
        copy(other.begin(), other.end(), begin());
    }

    ~SimpleVector() {
        delete[] data;
        size_ = 0;
        capacity_ = 0;
    }

    T &operator[](size_t index) {
        return data[index];
    }

    void operator=(const SimpleVector &other) {
        if (capacity_ >= other.size_) {
            copy(other.begin(), other.end(), begin());
            size_ = other.size_;
        } else {
            SimpleVector tmp(other);
            swap(tmp.data, data);
            swap(tmp.size_, size_);
            swap(tmp.capacity_, capacity_);
        }
    }

    T *begin() {
        return data;
    }

    T *end() {
        return data + size_;
    }

    T *begin() const {
        return data;
    }

    T *end() const {
        return data + size_;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T &value) {
        if (size_ == 0) {
            capacity_ = 1;
            data = new T[capacity_];
        }
        if (size_ == capacity_) {
            T *new_data = new T[2 * capacity_];
            for (int i = 0; i < size_; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity_ *= 2;
        }
        data[size_++] = value;
    }

private:
    T *data;
    size_t capacity_;
    size_t size_;
};

