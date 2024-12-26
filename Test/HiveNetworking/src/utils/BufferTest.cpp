//
// Created by guill on 2024-12-24.
//
#include <gtest/gtest.h>

#include "utils/Buffer.h"

const char* BUFFER_COMPARATOR = "Buffer";

TEST(BufferTest, Initialization_Without_Args)
{
    // Initialization without args
    hive::Buffer buffer;

    // must be nullptr
    EXPECT_NE(bool(buffer), true);

    // size must be 0
    EXPECT_EQ(buffer.size(), 0);
}

TEST(BufferTest, Initialization_With_Args)
{
    const char* b   = "Buffer";
    const size_t s  = strlen(b) + 1;

    hive::Buffer buffer(b, s);

    // must be "Buffer"
    EXPECT_NE(bool(buffer), false);

    // size must be s
    EXPECT_EQ(buffer.size(), s);
}

TEST(BufferTest, Initialization_With_Buffer)
{
    const char* b   = "Buffer";
    const size_t s  = strlen(b) + 1;

    const hive::Buffer BUFFER(b, s);

    hive::Buffer buffer(BUFFER);

    // must be "Buffer"
    EXPECT_NE(bool(buffer), false);

    // size must be s
    EXPECT_EQ(buffer.size(), s);
}

TEST(BufferTest, Copy_With_Args)
{
    const char* b   = "Buffer";
    const size_t s  = strlen(b) + 1;

    hive::Buffer buffer = hive::Buffer::copy(b, s);

    // must be "Buffer"
    EXPECT_NE(bool(buffer), false);

    // size must be s
    EXPECT_EQ(buffer.size(), s);
}

TEST(BufferTest, Copy_With_Buffer)
{
    const char* b   = "Buffer";
    const size_t s  = strlen(b) + 1;

    const hive::Buffer BUFFER(b, s);

    hive::Buffer buffer = hive::Buffer::copy(BUFFER);

    // must be "Buffer"
    EXPECT_NE(bool(buffer), false);

    // size must be s
    EXPECT_EQ(buffer.size(), s);
}

TEST(BufferTest, Allocate_Zero)
{
    const char* b   = "Buffer";
    const size_t s  = strlen(b) + 1;

    hive::Buffer buffer(b, s);

    // allocate 0
    buffer.allocate(0);

    // must be false
    EXPECT_NE(bool(buffer), true);

    // size must be 0
    EXPECT_EQ(buffer.size(), 0);

    // must be able to read b (not deleted)
    ASSERT_STREQ(b, BUFFER_COMPARATOR);
}

TEST(BufferTest, Allocate_New_Size)
{
    const char* b   = "Buffer";
    const size_t s  = strlen(b) + 1;

    hive::Buffer buffer(b, s);

    // allocate 10
    buffer.allocate(10);

    // must be not equal to nullptr
    EXPECT_NE(bool(buffer), false);

    // size must be 10
    EXPECT_EQ(buffer.size(), 10);

    // must be able to read b (did not touch b when released buffer
    ASSERT_STREQ(b, BUFFER_COMPARATOR);
}

TEST(BufferTest, Zero_Initialize_Without_Data)
{
    hive::Buffer buffer;

    // allocate 10
    buffer.allocate(10);

    // Zero Initialize
    buffer.zeroInitialize();

    // must be 0000000000
    EXPECT_NE(bool(buffer), false);

    // size must be 10
    EXPECT_EQ(buffer.size(), 10);

    // Evaluate buffer's value (uint8_t*)
    auto value = buffer.as<uint8_t>();

    EXPECT_EQ(*value, 0);
}

TEST(BufferTest, Zero_Initialize_When_Data)
{
    const char* b   = "Buffer";
    const size_t s  = strlen(b) + 1;

    hive::Buffer buffer(b, s);

    // Zero initialize instead of b
    buffer.zeroInitialize();

    // must be 000000
    EXPECT_NE(bool(buffer), false);

    // size must be s
    EXPECT_EQ(buffer.size(), s);

    // must be able to read b (did not touch b when released buffer
    ASSERT_STREQ(b, BUFFER_COMPARATOR);

    // Evaluate buffer's value (uint8_t*)
    auto value = buffer.as<uint8_t>();

    EXPECT_EQ(*value, 0);
}

TEST(BufferTest, ReadByte_Buffer_Reference)
{
    const char* b   = "Buffer";
    const size_t s  = strlen(b) + 1;

    const char* a   = "a";

    hive::Buffer buffer(b, s);

    char r;

    for(size_t i = 0; i < s; i++)
    {
        r = buffer.readByte<char>(i);

        EXPECT_EQ(r, b[i]);
    }
}

struct T
{
    uint32_t a;
    uint64_t b;
};

TEST(BufferTest, Read_Buffer_Reference)
{
    T* t = new T;
    t->a = 10; t->b = 20;
    const size_t s = sizeof(T);

    hive::Buffer buffer(t, s);

    T t_ = buffer.read<T>();

    EXPECT_EQ(t_.a, t->a);

    EXPECT_EQ(t_.b, t->b);
}
