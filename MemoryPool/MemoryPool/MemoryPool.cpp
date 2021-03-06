#include "MemoryPool.h"
#include <cassert>
#include <iostream>


mem_pool_singleton::mem_pool::mem_pool() : ptr_(mem_)
{
    std::cout << "mempool ctor called\n";
}

mem_pool_singleton::mem_pool::~mem_pool()
{
    std::cout << "mempool dtor called\n";
}

void * mem_pool_singleton::mem_pool::allocate(size_t size_requested)
{
    assert((ptr_ + size_requested) <= (mem_ + sizeof mem_) && "Pool exhausted!");
    void* mem = ptr_;
    ptr_ += size_requested;
    return mem;
}

void mem_pool_singleton::mem_pool::deallocate(void* chunk)
{

}

