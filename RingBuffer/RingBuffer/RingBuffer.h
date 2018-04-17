#pragma once
#include <string>
#include <memory>

// TODO: Use template
class ring_buffer
{
public:
    explicit ring_buffer(size_t capacity);
    ring_buffer(const ring_buffer& other);
    ring_buffer(ring_buffer&& other) noexcept;
    ring_buffer& operator=(const ring_buffer& other);
    ring_buffer& operator=(ring_buffer&& other) noexcept;
    ~ring_buffer();
    void swap(ring_buffer& tmp) noexcept;
    void push(std::string);
    std::string pop() ;
private:
    std::unique_ptr<std::string[]> buffer_;
    size_t capacity_;
    size_t read_index_;
    size_t write_index_;
    bool empty_;
};

