#include "MemoryPool.h"
#include <cassert>


mem_pool_singleton::mem_pool::mem_pool() : ptr_(mem_)
{
}

mem_pool_singleton::mem_pool::~mem_pool()
{
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

