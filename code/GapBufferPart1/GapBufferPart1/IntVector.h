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
    void pop_back();

    reference at(size_type n);
    const_reference at(size_type n) const;

private:
    size_type _logicalSize;
    size_type _allocatedSize;
    value_type* _elems;
};

#endif // IntVector_H

IntVector::IntVector() {

}

IntVector::IntVector(size_type n, const_reference val) {
    (void) n, (void) val; // only here so it will compile
}

IntVector::size_type IntVector::size() const {
    return 0; // only here so it will compile
}

bool IntVector::empty() const {
    return false; // only here so it will compile
}

void IntVector::reserve(size_type new_cap) {
    (void) new_cap;
    if (new_cap > _allocatedSize) {
        value_type* new_array = new value_type[new_cap];
        std::move(_elems, _elems + _allocatedSize, new_array);
        delete[] _elems;
        _elems = new_array;
        _allocatedSize = new_cap;
    }
}


void IntVector::insert(size_type indx, const_reference value) {
    (void) indx, (void) value;
}


void IntVector::push_back(const_reference value) {
    (void) value;
}


IntVector::reference IntVector::at(size_type n) {
    (void) n;
    return _elems[0]; // only here so it will compile
}

// Only difference between operator[] and at is bounds checking.
IntVector::const_reference IntVector::at(size_type n) const {
    (void) n;
    return _elems[0]; // only here so it will compile
}
