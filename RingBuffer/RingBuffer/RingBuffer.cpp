#include "stdafx.h"
#include "RingBuffer.h"



ring_buffer::ring_buffer(const size_t capacity) : buffer_(std::make_unique<std::string[]>(capacity)), capacity_(capacity), read_index_(0), write_index_(0), empty_(true)
{
    // the old fashioned way, you don't need to use explicit new/delete in C++14
    //buffer_ = new std::string[capacity];  
}

ring_buffer::ring_buffer(const ring_buffer& other)
    : buffer_(std::make_unique<std::string[]>(other.capacity_)),
    capacity_(other.capacity_),
    read_index_(other.read_index_),
    write_index_(other.write_index_),
    empty_(other.empty_)
{
    for (auto i = 0; i < capacity_; i++)
    {
        buffer_[i] = other.buffer_[i];
    }
}

ring_buffer::ring_buffer(ring_buffer&& other) noexcept
    : buffer_(std::move(other.buffer_)),
    capacity_(other.capacity_),
    read_index_(other.read_index_),
    write_index_(other.write_index_),
    empty_(other.empty_)
{
}

ring_buffer& ring_buffer::operator=(const ring_buffer& other)
{
    if (this == &other)
    {
        return *this;
    }
    ring_buffer tmp(other);
    swap(tmp);
    return *this;
}

ring_buffer& ring_buffer::operator=(ring_buffer&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    buffer_ = std::move(other.buffer_);
    capacity_ = other.capacity_;
    read_index_ = other.read_index_;
    write_index_ = other.write_index_;
    empty_ = other.empty_;
    return *this;
}

ring_buffer::~ring_buffer()
{
    //delete[] buffer_;
}

void ring_buffer::swap(ring_buffer & tmp) noexcept
{
    std::swap(buffer_, tmp.buffer_);
    std::swap(capacity_, tmp.capacity_);
    std::swap(read_index_, tmp.read_index_);
    std::swap(write_index_, tmp.write_index_);
    std::swap(empty_, tmp.empty_);
}

void ring_buffer::push(const std::string s)
{
    if (((read_index_ < write_index_ && write_index_ < capacity_) || (0 <= write_index_ && write_index_ < read_index_)) || empty_)
    {
        // placement new (note: just use "buffer_[write_index_] = s;")
        const auto sptr = new(&buffer_[write_index_]) std::string;
        *sptr = s;
        
        write_index_++;
        empty_ = false;
    }
    if (write_index_ == capacity_)
    {
        write_index_ = 0;
    }
}

std::string ring_buffer::pop() 
{
    std::string data;
    if (read_index_ < capacity_ && !empty_)
    {
        data = buffer_[read_index_++];
        if (read_index_ == capacity_)
        {
            read_index_ = 0;
        }
        if (read_index_ == write_index_)
        {
            empty_ = true;
        }
    }
    else
    {
        data = "";
    }

    return data;
}
