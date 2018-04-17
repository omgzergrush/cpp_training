#include "store_int.h"
#include "MemoryPool.h"

// Constructor and destructor

store_int::store_int()
{
    pvalue_ = new int;
    *pvalue_ = 0;
}

store_int::~store_int()
{
    delete pvalue_;
}


// Copy consturctor, move constuctor, assign and swap

store_int::store_int(const store_int& other): pvalue_{other.pvalue_}
{
    pvalue_ = new int;
    *pvalue_ = *(other.pvalue_);
}

store_int::store_int(store_int&& other) noexcept : pvalue_{other.pvalue_}
{
    other.pvalue_ = nullptr;
}

store_int& store_int::operator=(store_int other)
{
    store_int tmp(other);
    swap(tmp);
    return *this;
}

void store_int::swap(store_int& tmp) noexcept
{
    std::swap(pvalue_, tmp.pvalue_);
}


// New and delete

void* store_int::operator new(std::size_t size)
{
    auto& my_mempool = mem_pool_singleton::instance();
    return my_mempool.allocate(size);
}
void store_int::operator delete(void* pointer_to_memory)
{
    auto& my_mempool = mem_pool_singleton::instance();
    return my_mempool.deallocate(pointer_to_memory);
}



// Interface methods

int store_int::get() const
{
    return *pvalue_;
}

void store_int::store(const int value)
{
    *pvalue_ = value;
}
