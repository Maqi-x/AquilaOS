/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once
#include <memory.hpp>
#include <types.hpp>

template <typename T> class Slice {
  public:
    size_t cap, len;
    Slice() : cap(0), len(0), data(nullptr) {}
    ~Slice() { delete[] data; }

    Slice(const Slice& other) : cap(other.cap), len(other.len) {
        data = new T[cap];
        for (size_t i = 0; i < len; i++) {
            data[i] = other.data[i];
        }
    }

    template <int N> Slice(const T (&arr)[N]) {
        delete[] data;
        cap = N;
        len = N;
        data = new T[cap];
        for (size_t i = 0; i < len; i++) {
            data[i] = arr[i];
        }
    }

    Slice(Slice&& other) noexcept : data(other.data), cap(other.cap), len(other.len) {
        other.data = nullptr;
        other.cap = 0;
        other.len = 0;
    }

    Slice& operator=(const Slice& other) {
        if (this == &other) return *this;
        delete[] data;
        cap = other.cap;
        len = other.len;
        data = new T[cap];
        for (size_t i = 0; i < len; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    Slice& operator=(Slice&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        cap = other.cap;
        len = other.len;
        other.data = nullptr;
        other.cap = 0;
        other.len = 0;
        return *this;
    }

    template <int N> void operator=(const T (&arr)[N]) {
        delete[] data;
        cap = N;
        len = N;
        data = new T[cap];
        for (size_t i = 0; i < len; i++) {
            data[i] = arr[i];
        }
    }

    void Append(T element) {
        if (len >= cap) Resize(cap == 0 ? 1 : cap * 2);
        data[len++] = element;
    }

    void Extend(Slice<T>& elements) {
        for (size_t i = 0; i < elements.len; i++) {
            Append(elements.data[i]);
        }
    }

    void Extend(T* elements, size_t count) {
        for (size_t i = 0; i < count; i++) {
            Append(elements[i]);
        }
    }

    T Pop() {
        if (len == 0) {
            return T();
        }
        T value = move(data[--len]);
        return value;
    }

    size_t Len() const { return len; }

    T& operator[](size_t index) {
        if (index >= len) {
            static T defaultV{};
            return defaultV;
        }
        return data[index];
    }

    bool operator==(const Slice<T>& other) const {
        if (len != other.len) return false;
        for (size_t i = 0; i < len; i++) {
            if (!(data[i] == other.data[i])) return false;
        }
        return true;
    }

    bool operator!=(const Slice<T>& other) const { return !(*this == other); }

  protected:
    T* data;

    void Resize(size_t newCap) {
        if (newCap <= cap) return;

        T* newData = new T[newCap];
        for (size_t i = 0; i < len; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        cap = newCap;
    }
};

template <typename T> struct removeReference {
    using type = T;
};

template <typename T> struct removeReference<T&> {
    using type = T;
};

template <typename T> struct removeReference<T&&> {
    using type = T;
};

template <typename T> constexpr typename removeReference<T>::type&& move(T&& t) noexcept { return static_cast<typename removeReference<T>::type&&>(t); }
