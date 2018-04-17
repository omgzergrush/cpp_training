#include "pch.h"
#include "RingBuffer2.h"
#include "store_int.h"

TEST(TestRingBuffer2, SimpleTest) {
    RingBuffer mybuffer;

    mybuffer.push(1);

    EXPECT_EQ(1, mybuffer.peek());
}

TEST(TestIntStore, SimpleTest) {
    store_int test_store;

    test_store.store(1);

    EXPECT_EQ(1, test_store.get());
}

TEST(TestIntStore, CopyTest) {
    store_int test_store;
    test_store.store(1);

    auto another_buffer = test_store;

    EXPECT_EQ(1, another_buffer.get());
    EXPECT_EQ(1, test_store.get());
}

TEST(TestIntStore, MoveTest) {
    store_int test_store;
    test_store.store(1);

    auto another_buffer = std::move(test_store);

    EXPECT_EQ(1, another_buffer.get());
}

TEST(TestIntStore, SwapTest) {
    store_int test_store;
    test_store.store(1);

    store_int another_store;
    another_store.store(2);

    using std::swap;
    swap(test_store, another_store);

    EXPECT_EQ(1, another_store.get());
    EXPECT_EQ(2, test_store.get());
}

TEST(TestIntStore, AssignTest) {
    store_int test_store;
    test_store.store(1);

    store_int another_buffer;
    another_buffer = test_store;

    EXPECT_EQ(1, another_buffer.get());
}

TEST(TestIntStore, NewTest) {
    store_int* pstore = new store_int();

    pstore->store(1);

    EXPECT_EQ(1, pstore->get());

    pstore->~store_int();
}


TEST(TestIntStore, MoreNewTests) {
    store_int* pstore = new store_int();
    store_int* pstore2 = new store_int();

    pstore->store(1);
    pstore2->store(99);


    EXPECT_EQ(1, pstore->get());
    EXPECT_EQ(99, pstore2->get());

    pstore->~store_int();
    pstore2->~store_int();
}