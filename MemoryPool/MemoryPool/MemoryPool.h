#ifndef MEMPOOL_H
#define MEMPOOL_H


class mem_pool_singleton
{
protected:
    ~mem_pool_singleton() = default;
public:

    static mem_pool_singleton& instance();

    virtual void* allocate(size_t size) = 0;
    virtual void deallocate(void* chunk) = 0;
private:

    class mem_pool;
};


class mem_pool_singleton::mem_pool : public mem_pool_singleton
{
public:
    mem_pool();
    virtual ~mem_pool();
    void* allocate(size_t size) override;
    void deallocate(void* chunk) override;
private:
    char mem_[4096];
    char* ptr_;
};


inline mem_pool_singleton & mem_pool_singleton::instance()
{
    static mem_pool_singleton::mem_pool instance;
    return instance;
}



#endif