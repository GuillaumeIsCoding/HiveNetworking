//
// Created by guill on 2024-12-23.
//
#pragma once

#include <cstdint>
#include <cstring>

namespace hive
{
    class Buffer
    {
    public:
        Buffer();
        Buffer(const void* data, size_t size);
        Buffer(const Buffer& buffer);

        ~Buffer();

        static Buffer copy(const void* data, size_t size);
        static Buffer copy(const Buffer& buffer);

        void allocate(size_t size);
        void release();
        void zeroInitialize();

        template<typename T>
        T& read(size_t offset = 0)
        {
            return *(T*)((uint32_t*)m_data + offset);
        }

        template<typename T>
        [[nodiscard]]
        const T& read(size_t offset = 0) const
        {
            return *(T*)((uint32_t*)m_data + offset);
        }

        template<typename T>
        [[nodiscard]]
        T& readByte(size_t offset = 0) const
        {
            return *(T*)((uint8_t*)m_data + offset);
        }

        [[nodiscard]]
        uint8_t* readBytes(size_t size, size_t offset = 0) const;

        void write(const void* data, size_t size, size_t offset = 0);

        [[nodiscard]]
        explicit operator bool() const;

        uint8_t& operator[](int index);
        [[nodiscard]]
        uint8_t  operator[](int index) const;

        template<typename T>
        [[nodiscard]]
        T* as() const
        {
            return (T*)m_data;
        }

        [[nodiscard]]
        size_t size() const;

    private:
        void*  m_data;
        size_t m_size;
    };
}
