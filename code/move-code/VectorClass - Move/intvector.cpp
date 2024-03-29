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

    // Part 4
    IntVector(std::initializer_list<value_type> init);


private:
    size_type _logicalSize;
    size_type _allocatedSize;
    value_type* _elems;
};


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
    std::move_backward(_elems + indx, _elems + _logicalSize, _logicalSize + 1); // Don't make copies!
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

#endif // IntVector_H
