#include <iterator>
#include <algorithm>
#define HIGHBIT(_x) (_x ? (1 << (32-__builtin_clz(_x))) : 1)

template <typename T>
class Vector {
    size_t size_, cap_;
    T *arr_;
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
        T *ptr_;
    public:
        typedef T value_type;
        Iterator(T *ptr) : ptr_(ptr) {}
        Iterator &operator++() {
            ptr_++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp(ptr_);
            operator++();
            return tmp;
        }
        Iterator &operator--() {
            ptr_--;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp(ptr_);
            operator--();
            return tmp;
        }
        Iterator operator+(const size_t n) {
            return Iterator(ptr_+n);
        }
        Iterator operator-(const size_t n) {
            return Iterator(ptr_-n);
        }
        size_t operator-(const Iterator &rhs) {
            return ptr_-rhs.ptr_;
        }
        constexpr bool operator==(const Iterator &rhs) const {
            return ptr_ == rhs.ptr_;
        }
        constexpr bool operator!=(const Iterator &rhs) const {
            return ptr_ != rhs.ptr_;
        }
        constexpr T &operator*() const {
            return *ptr_;
        }
    };
    Vector() : size_(0), cap_(1), arr_(new T[cap_]) {}
    Vector(size_t size) : size_(size), cap_(HIGHBIT(size_)), arr_(new T[cap_]()) {}
    Vector(const Vector &other) : size_(other.size_), cap_(other.cap_), arr_(new T[cap_]) {
        std::copy(other.begin(), other.end(), this->begin());
    }
    ~Vector() {
        delete[] arr_;
    }
    constexpr bool empty() const {
        return size_ == 0;
    }
    constexpr Iterator begin() {
        return Iterator(arr_);
    }
    constexpr const Iterator begin() const {
        return Iterator(arr_);
    }
    constexpr Iterator end() {
        return Iterator(arr_+size_);
    }
    constexpr const Iterator end() const {
        return Iterator(arr_+size_);
    }
    constexpr size_t size() const {
        return size_;
    }
    constexpr size_t cap() const {
        return cap_;
    }
    constexpr T &operator[](int idx) {
        return arr_[idx];
    }
    constexpr const T &operator[](int idx) const {
        return arr_[idx];
    }
    void fill(Iterator first, Iterator last) {
        while(first != last) *(first++) = T();
    }
    void resize(size_t size) {
        if(size > cap_) {
            cap_ = HIGHBIT(size);
            auto tmp = new T[cap_]();
            std::copy(begin(), end(), tmp);
            delete[] arr_;
            arr_ = tmp;
        }
        else size_ = size;
    }
    void pushBack(const T &value) {
        if(size_ == cap_) resize(cap_<<1);
        arr_[size_++] = value;
    }
    Vector<T> &operator=(const Vector<T> &rhs) {
        if(this == &rhs) return *this;
        resize(rhs.size_);
        std::copy(rhs.begin(), rhs.end(), begin());
        return *this;
    }
};