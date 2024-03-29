#ifndef INTVECTOR_H
#define INTVECTOR_H
#include <string>
#include <algorithm>
#include <ostream>
#include <numeric>
#include <iterator>

class IntVector {
public:
    using value_type = int;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    const size_type kDefaultSize = 10;

    IntVector();
    IntVector(size_type n, const_reference val);
    size_type size() const;
    bool empty() const;
    void reserve(size_type new_cap);

    void insert(size_type indx, const_reference value);
    void push_back(const_reference value);

    reference at(size_type n);
    const_reference at(size_type n) const;

    reference operator[](size_type n);
    const_reference operator[](size_type n) const;

    IntVector& operator+=(const_reference value);

    // Part 4
    IntVector(std::initializer_list<value_type> init);

    // Also, turn everything into a template!


private:
    size_type _logicalSize;
    size_type _allocatedSize;
    value_type* _elems;
};

IntVector::IntVector() {
    _logicalSize = 0;
    _allocatedSize = 10;
    _elems = new int[_allocatedSize];
}

IntVector::IntVector(size_type n, const_reference val) {
    _logicalSize = n;
    _allocatedSize = 10 ? n < 5 : 2*n;
    _elems = new int[_allocatedSize];
    std::fill(_elems, _elems + _allocatedSize, val);
}

IntVector::size_type IntVector::size() const {
    return _logicalSize;
}

bool IntVector::empty() const {
    return size() == 0;
}

void IntVector::reserve(size_type new_cap) {
    if (new_cap > _allocatedSize) {
        value_type* new_array = new value_type[new_cap];
        std::move(_elems, _elems + _allocatedSize, new_array);
        delete[] _elems;
        _elems = new_array;
        _allocatedSize = new_cap;
    }
}



void IntVector::insert(size_type indx, const_reference value) {
    if(size() == _allocatedSize) {
        reserve(2*_allocatedSize);
    }
    std::move_backward(_elems + indx, _elems + _logicalSize, _elems + _logicalSize + 1); // Don't make copies!
    _elems[indx] = value;
    ++_logicalSize;
}


void IntVector::push_back(const_reference value) {
    insert(_logicalSize, value);
}


IntVector::reference IntVector::at(size_type n) {
    return const_cast<value_type&>(static_cast<const IntVector*>(this)->at(n));
}

IntVector::const_reference IntVector::at(size_type n) const {
    if (n >= _allocatedSize) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return _elems[n];
}

IntVector::reference IntVector::operator[](size_type n) {
    return const_cast<value_type&>(static_cast<const IntVector*>(this)->operator[](n));
}

IntVector::const_reference IntVector::operator[](size_type n) const {
    return _elems[n];
}

IntVector& IntVector::operator+=(const_reference element) {
    push_back(element);
    return *this;
}

IntVector operator+(const IntVector& lhs, const IntVector& rhs) {
    auto copy = lhs;
    for (size_t i = 0; i < rhs.size(); ++i) {
        copy.push_back(rhs[i]);
    }
    return copy;
}

std::ostream& operator<<(std::ostream& oss, const IntVector& rhs) {
    oss << "{";
    for (size_t i = 0; i < rhs.size(); ++i) {
        oss << rhs[i];
        if (i != rhs.size()-1) oss << ", ";
    }
    oss << "}";
    return oss;
}


#endif // IntVector_H
