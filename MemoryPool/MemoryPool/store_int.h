#pragma once
#include <utility>

class store_int
{
public:
    store_int();
    ~store_int();

    store_int(const store_int& other);      // copy
    store_int(store_int&& other) noexcept;  // move
    store_int& operator=(store_int other);  // assign
    // todo: move assign
    void swap(store_int& tmp) noexcept;

    void* operator new(std::size_t sz);
    void operator delete(void* pointer_to_memory);
    //void* operator new[](std::size_t sz);
    //void operator delete[](void* pointer_to_memory);

    int get() const;
    void store(int);
private:
    int* pvalue_;
};

