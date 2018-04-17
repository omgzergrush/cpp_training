#ifndef RING_BUFFER_2_H
#define RING_BUFFER_2_H

#include <cstddef>


class RingBuffer
{
public:
    RingBuffer();
    ~RingBuffer();

    // Copy
    RingBuffer(RingBuffer const& rhs);
    RingBuffer& operator =(RingBuffer const& rhs);

    // Move
    RingBuffer(RingBuffer && rhs);
    RingBuffer& operator =(RingBuffer&& rhs);

    bool empty() const;
    int peek() const;

    void push(int const& element);
    void push(int&& element);
    void pop();

private:
    static constexpr std::size_t capacity = 128;
    int* data;
    std::size_t head;
    std::size_t tail;
};


#endif // RING_BUFFER_2_H