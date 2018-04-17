#include "pch.h"
#include "RingBuffer2.h"
#include "store_int.h"

TEST(TestRingBuffer2, SimpleTest) {
    RingBuffer mybuffer;

    mybuffer.push(1);

    EXPECT_EQ(1, mybuffer.peek());
}

TEST(TestIntStore, SimpleTest) {
    store_int mybuffer;

    mybuffer.store(1);

    EXPECT_EQ(1, mybuffer.get());
}

TEST(TestIntStore, CopyTest) {
    store_int mybuffer;
    mybuffer.store(1);

    auto another_buffer = mybuffer;

    EXPECT_EQ(1, another_buffer.get());
    EXPECT_EQ(1, mybuffer.get());
}

TEST(TestIntStore, MoveTest) {
    store_int mybuffer;
    mybuffer.store(1);

    auto another_buffer = std::move(mybuffer);

    EXPECT_EQ(1, another_buffer.get());
}

TEST(TestIntStore, SwapTest) {
    store_int mybuffer;
    mybuffer.store(1);

    store_int another_buffer;
    another_buffer.store(2);

    using std::swap;
    swap(mybuffer, another_buffer);

    EXPECT_EQ(1, another_buffer.get());
    EXPECT_EQ(2, mybuffer.get());
}

TEST(TestIntStore, AssignTest) {
    store_int mybuffer;
    mybuffer.store(1);

    store_int another_buffer;
    another_buffer = mybuffer;

    EXPECT_EQ(1, another_buffer.get());
}

TEST(TestIntStore, NewTest) {
    store_int* pstore = new store_int();

    pstore->store(1);

    EXPECT_EQ(1, pstore->get());

    pstore->~store_int();
}