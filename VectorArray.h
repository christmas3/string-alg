#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>
#include <memory>
#include <utility>

template<typename T>
class VectorArray
{
public:
    using SizeType = size_t;

    explicit VectorArray(SizeType size = 10)
        : arr_(new T[size * sizeof(T)])
        , size_(0)
        , capacity_(size)
        , step_(size)
    {
    }

    VectorArray(const VectorArray& other)
        : arr_(new T[other.size_ * sizeof(T)])
        , size_(other.size_)
        , capacity_(other.capacity_)
        , step_(other.step_)
    {
        memcpy(arr_, other.arr_, sizeof(T) * size_);
    }

    VectorArray(VectorArray&& other) noexcept
        : arr_(other.arr_)
        , size_(other.size_)
        , capacity_(other.capacity_)
        , step_(other.step_)
    {
        other.arr_ = nullptr;
        other.step_ = other.size_ = other.capacity_ = 0;
    }

    ~VectorArray() { delete[] arr_; }

    friend void swap(VectorArray& a, VectorArray& b) noexcept
    {
        using std::swap;

        swap(a.arr_, b.arr_);
        swap(a.size_, b.size_);
        swap(a.capacity_, b.capacity_);
        swap(a.step_, b.step_);
    }

    VectorArray& operator=(const VectorArray& other)
    {
        if (this == &other) {
            return *this;
        }
        VectorArray tmp(other);
        swap(tmp, *this);

        return *this;
    }

    VectorArray& operator=(VectorArray&& other) noexcept
    {
        VectorArray tmp(std::move(other));
        swap(tmp, *this);

        return *this;
    }

    SizeType size() const { return size_; }
    bool empty() const { return size_ == 0; }
    SizeType capacity() const { return capacity_; }
    T get(SizeType index) const { return arr_[index]; }
    T& operator[](SizeType index) { return arr_[index]; }
    void putBack(const T& item) { putImpl(item, size_); }
    void putBack(T&& item) { putImpl(std::move(item), size_); }
    void put(const T& item, SizeType index) { putImpl(item, index); }
    void put(T&& item, SizeType index) { putImpl(std::move(item), index); }
    T& back() { return arr_[size_ - 1]; }
    const T* data() const { return arr_; }

    T remove(SizeType index)
    {
        assert(size_ > index);

        if (isNeedToShrink()) {
            shrink();
        }

        --size_;
        T removed = arr_[index];
        if (index < size_) {
            memmove(arr_ + index, arr_ + index + 1, (size_ - index) * sizeof(T));
        }

        return removed;
    }
    void clear()
    {
        delete[] arr_;
        arr_ = new T[step_ * sizeof(T)];
        size_ = 0;
        capacity_ = step_;
    }
    VectorArray<T> getCopy() const
    {
        auto copy = std::make_shared<VectorArray<T>>();
        if (VectorArray<T>::empty()) {
            return copy;
        }
        copy->arr_ = new T[capacity_];
        memcpy(copy->arr_, arr_, size_ * sizeof(T));
        copy->size_ = size_;
        copy->step_ = step_;
        copy->capacity_ = capacity_;

        return copy;
    }

protected:
    virtual SizeType increaseCapacity() const { return capacity_ + step_; }
    //    [[nodiscard]] virtual bool isNeedToShrink() const { return capacity_ - size_ >= step_ * 2 - 1; }
    [[nodiscard]] virtual bool isNeedToShrink() const { return size_ < step_; }
    virtual SizeType shrinkCapacity() const { return capacity_ - step_; }

private:
    template<typename U>
    void putImpl(U&& item, SizeType index)
    {
        if (size_ == capacity_) {
            resize(index);
        }
        else if (index != size_) {
            memmove(arr_ + index + 1, arr_ + index, (size_ - index) * sizeof(T));
        }
        arr_[index] = std::forward<U>(item);
        ++size_;
    }

    void resize(SizeType index)
    {
        capacity_ = increaseCapacity();
        auto* newArr = new T[capacity_];
        if (index) {
            memcpy(newArr, arr_, index * sizeof(T));
        }
        if (index < size_) {
            memcpy(newArr + index + 1, arr_ + index, (size_ - index) * sizeof(T));
        }
        delete[] arr_;
        arr_ = newArr;
    }

    void shrink()
    {
        capacity_ = step_;
        auto* newArr = new T[capacity_];
        memcpy(newArr, arr_, size_ * sizeof(T));
        delete[] arr_;
        arr_ = newArr;
    }

    T* arr_;
    SizeType size_;
    SizeType capacity_;
    std::uint32_t step_;
};
