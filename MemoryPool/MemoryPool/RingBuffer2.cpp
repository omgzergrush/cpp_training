#include <utility>

#include "RingBuffer2.h"


RingBuffer::RingBuffer()
    : data(nullptr), head(0), tail(0)
{
    data = new int[capacity];
}

RingBuffer::~RingBuffer()
{
    delete[] data;
}

RingBuffer::RingBuffer(RingBuffer const& rhs)
    : data(nullptr), head(rhs.head), tail(rhs.tail)
{
    data = new int[capacity];
    for (std::size_t i = head; i != tail; i = (i + 1) % capacity)
    {
        data[i] = rhs.data[i];
    }
}

RingBuffer& RingBuffer::operator =(RingBuffer const& rhs)
{
    if (&rhs != this)
    {
        delete[] data;
        data = new int[capacity];

        head = rhs.head;
        tail = rhs.tail;
        for (std::size_t i = head; i != tail; i = (i + 1) % capacity)
        {
            data[i] = rhs.data[i];
        }
    }
    return *this;
}

RingBuffer::RingBuffer(RingBuffer&& rhs)
    : head(rhs.head), tail(rhs.tail)
{
    data = rhs.data;
    rhs.data = nullptr;
}

RingBuffer& RingBuffer::operator =(RingBuffer&& rhs)
{
    if (&rhs != this)
    {
        head = rhs.head;
        tail = rhs.tail;
        data = rhs.data;
        rhs.data = nullptr;
    }
    return *this;
}

bool RingBuffer::empty() const
{
    return head == tail;
}

int RingBuffer::peek() const
{
    return data[head];
}

void RingBuffer::push(int const& element)
{
    data[tail] = element;
    tail = (tail + 1) % capacity;
}

void RingBuffer::push(int&& element)
{
    data[tail] = std::move(element);
    tail = (tail + 1) % capacity;
}

void RingBuffer::pop()
{
    head = (head + 1) % capacity;
}
