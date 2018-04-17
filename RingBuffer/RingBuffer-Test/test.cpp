#include "pch.h"
#include "../RingBuffer/RingBuffer.h"
#include <string>

TEST(RingBufferTest, BasicPushPop) {
    ring_buffer rbuf(128);

    std::string test_input = "hello";
    rbuf.push(test_input);

    EXPECT_EQ(test_input, rbuf.pop());
}


TEST(RingBufferTest, InsertionOverCapacity) {
    ring_buffer rbuf(128);

    std::string test_input = "hello";

    for (size_t i = 0; i < 200; i++)
    {
        rbuf.push(test_input + std::to_string(i));
    }

    for (size_t i = 0; i < 128; i++)
    {
        EXPECT_EQ(test_input + std::to_string(i), rbuf.pop());
    }
}

TEST(RingBufferTest, PopEmpty) {
    ring_buffer rbuf(128);
    EXPECT_EQ("", rbuf.pop());
    std::string test_input = "hello";
    rbuf.push(test_input);
    EXPECT_EQ(test_input, rbuf.pop());
}

TEST(RingBufferTest, ContinuousPushPop) {
    ring_buffer rbuf(128);

    std::string test_input = "hello";

    for (size_t i = 0; i < 1024; i++)
    {
        rbuf.push(test_input + std::to_string(i));
        EXPECT_EQ(test_input + std::to_string(i), rbuf.pop());
    }
}

TEST(RingBufferTest, AroundTheBufferInChunks) {
    ring_buffer rbuf(128);

    std::string test_input = "hello";

    // Write full
    for (size_t i = 0; i < 128; ++i)
    {
        rbuf.push(test_input + std::to_string(i));
    }

    // Read half
    for (size_t i = 0; i < 64; ++i)
    {
        EXPECT_EQ(test_input + std::to_string(i), rbuf.pop());
    }

    // Try to write full
    for (size_t i = 128; i < 256; ++i)
    {
        rbuf.push(test_input + std::to_string(i));
    }

    // Read full
    for (size_t i = 64; i < 128; ++i)
    {
        EXPECT_EQ(test_input + std::to_string(i), rbuf.pop());
    }
}


TEST(RingBufferTest, EmptyOrFull) {
    ring_buffer rbuf(128);

    std::string test_input = "hello";

    for (size_t i = 0; i < 1; ++i)
    {
        rbuf.push(test_input + std::to_string(i));
    }
    for (size_t i = 0; i < 1; ++i)
    {
        EXPECT_EQ(test_input + std::to_string(i), rbuf.pop());
    }
    for (size_t i = 1; i < 129; ++i)
    {
        rbuf.push(test_input + std::to_string(i));
    }
    // Buffer is full, which looks like same as empty_ on ring buffers (since read pointer = write pointer)
    for (size_t i = 1; i < 129; ++i)
    {
        EXPECT_EQ(test_input + std::to_string(i), rbuf.pop());
    }
}

TEST(RingBufferTest, CopyBuffer) {
    ring_buffer rbuf1(128);

    std::string test_input = "hello";
    rbuf1.push(test_input);

    auto rbuf2 = rbuf1;

    EXPECT_EQ(test_input, rbuf2.pop());
    EXPECT_EQ(test_input, rbuf1.pop());
}

TEST(RingBufferTest, AssignBuffer) {
    ring_buffer rbuf1(128);

    std::string test_input = "hello";
    rbuf1.push(test_input);

    ring_buffer rbuf2(128);

    rbuf2 = rbuf1;

    EXPECT_EQ(test_input, rbuf2.pop());
    EXPECT_EQ(test_input, rbuf1.pop());
}

TEST(RingBufferTest, MoveBuffer1) {
    ring_buffer rbuf1(128);

    std::string test_input = "hello";
    rbuf1.push(test_input);

    auto rbuf2 = std::move(rbuf1);

    EXPECT_EQ(test_input, rbuf2.pop());
}

TEST(RingBufferTest, MoveBuffer2) {
    auto rbuf1 = ring_buffer{128};

    std::string test_input = "hello";
    rbuf1.push(test_input);

    EXPECT_EQ(test_input, rbuf1.pop());
}

