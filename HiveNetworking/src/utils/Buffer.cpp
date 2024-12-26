//
// Created by guill on 2024-12-23.
//
#include "Buffer.h"

#include <memory>
#include <cstring>

namespace hive
{
    Buffer::Buffer()
        : m_data(nullptr), m_size(0)
    {

    }

    Buffer::Buffer(const void *data, size_t size)
        : m_data(nullptr), m_size(0)
    {
        /// I want to create a new buffer
        /// So if a play with it, it won't affect the data
        allocate(size);

        memcpy(m_data, data, size);
    }

    Buffer::Buffer(const Buffer &buffer)
        : m_data(nullptr), m_size(0)
    {
        /// Same issue but with a Buffer object
        allocate(buffer.m_size);

        memcpy(m_data, buffer.m_data, buffer.m_size);
    }

    Buffer::~Buffer()
    {
        release();
    }

    Buffer Buffer::copy(const void *data, size_t size)
    {
        return Buffer(data, size);
    }

    Buffer Buffer::copy(const Buffer &buffer)
    {
        return Buffer(buffer);
    }

    void Buffer::allocate(size_t size)
    {
        release();

        if(size == 0) return;

        m_data = new uint8_t[size];
        m_size = size;
    }

    void Buffer::release()
    {
        delete[](uint8_t*)m_data;

        m_data = nullptr;
        m_size = 0;
    }

    void Buffer::zeroInitialize()
    {
        if (m_data) memset(m_data, 0, m_size);
    }

    uint8_t *Buffer::readBytes(size_t size, size_t offset) const
    {
        auto* buffer = new uint8_t[size];
        memcpy(buffer, (uint8_t*)m_data + offset, size);
        return buffer;
    }

    void Buffer::write(const void *data, size_t size, size_t offset)
    {
        memcpy((uint8_t*)m_data + offset, data, size);
    }

    Buffer::operator bool() const
    {
        return m_data;
    }

    uint8_t &Buffer::operator[](int index)
    {
        return ((uint8_t*)m_data)[index];
    }

    uint8_t Buffer::operator[](int index) const
    {
        return ((uint8_t*)m_data)[index];
    }

    size_t Buffer::size() const
    {
        return m_size;
    }
}
