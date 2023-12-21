#pragma once

#include <iostream>
#include <algorithm> // 如果需要使用 std::swap
// Vector.h
#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class Vector {
private:
    T* arr;
    size_t size;
    size_t cap;

    void resize() {
        size_t newCap = cap == 0 ? 2 : cap * 2;
        T* newArr = new T[newCap];
        for (size_t i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        cap = newCap;
    }
    void erase(size_t index) {
        if (index < size) {
            for (size_t i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
        }
    }
    void insert(size_t index, T newdata) {
        if (size == cap) resize();
        T* newArr = new T[cap];
        newArr[0] = newdata;
        for (size_t i = index; i < size; ++i) {
            newArr[i + 1] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        size++;
    }

public:
    Vector(size_t newcap) : size(0), cap(newcap) {
        arr = new T[cap];
    }

    ~Vector() {
        delete[] arr;
    }

    void push_front(T newdata) {
        insert(0);
    }

    void push_back(T newdata) {
        insert(getsize() - 1);
    }

    void pop_front() {
        erase(0);
    }

    void pop_back() {
        erase(getsize() - 1);
    }

    size_t getsize() const {
        return size;
    }

    size_t getcap() const {
        return cap;
    }

    T& operator[](size_t index) {
        return arr[index];
    }
};

#endif // VECTOR_H