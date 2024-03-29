#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <string>
#include <algorithm>
#include <ostream>
#include <numeric>
#include <iterator>

template <typename T> // We added this to our IntVector class
class MyVector {
public:
    using value_type = T; // we changed this from int to arbitrary T.
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    const size_type kDefaultSize = 10;

    // intro to gap buffers
    MyVector<T>();
    MyVector<T>(size_type n, const_reference val);
    size_type size() const;
    bool empty() const;
    void reserve(size_type new_cap);

    void insert(size_type indx, const_reference value);
    void push_back(const_reference value);

    // const-correctness
    reference at(size_type n);
    const_reference at(size_type n) const;

    // operators
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    MyVector& operator+=(const_reference element);

    // iterators (NEW!)
    friend class iterator;

    class iterator :
            public std::iterator<std::random_access_iterator_tag, value_type> {
    public:
        friend class MyVector;

        reference operator*();
        iterator& operator+=(size_type diff);


        iterator operator+(size_type diff);
        friend iterator operator+(size_type diff, const iterator& rhs);

        // prefix
        iterator& operator++();
        // postfix
        iterator operator++(int);

    private:
        // why is it private? So you only friends
        // i.e. MyVector can create iterators
        iterator(MyVector<T>* pointee, size_type index) {
            _pointee = pointee;
            _index = index;
        }

        MyVector<T>* _pointee;
        size_type _index;

    };

    // iterator creators
    iterator begin();
    iterator end();


    // initializer list - probably next time
    MyVector<T>(std::initializer_list<value_type> init);

    // constructors -  next time


private:
    size_type _logicalSize;
    size_type _allocatedSize;
    value_type* _elems;
};

template <typename T>
MyVector<T>::MyVector() {
    _logicalSize = 0;
    _allocatedSize = 10;
    _elems = new T[_allocatedSize];
}

template <typename T>
MyVector<T>::MyVector(size_type n, const_reference val) {
    _logicalSize = n;
    _allocatedSize = 10 ? n < 5 : 2*n;
    _elems = new T[_allocatedSize];
    std::fill(_elems, _elems + _allocatedSize, val);
}

// We added the template declarations in front of all members.
// Don't forget to put typename in front of all qualified types
// i.e. - types which require mentioning MyVector<T> before
// the actual name of the funciton
template <typename T>
typename MyVector<T>::size_type MyVector<T>::size() const {
    return _logicalSize;
}

template <typename T>
bool MyVector<T>::empty() const {
    return size() == 0;
}

template <typename T>
void MyVector<T>::reserve(size_type new_cap) {
    if (new_cap > _allocatedSize) {
        value_type* new_array = new value_type[new_cap];
        std::move(_elems, _elems + _allocatedSize, new_array);
        delete[] _elems;
        _elems = new_array;
        _allocatedSize = new_cap;
    }
}


template <typename T>
void MyVector<T>::insert(size_type indx, const_reference value) {
    if(size() == _allocatedSize) {
        reserve(2*_allocatedSize);
    }
    std::move_backward(_elems + indx, _elems + _logicalSize, _logicalSize + 1); // Don't make copies!
    _elems[indx] = value;
    ++_logicalSize;
}

template <typename T>
void MyVector<T>::push_back(const_reference value) {
    insert(_logicalSize, value);
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::at(size_type n) {
    return const_cast<value_type&>(static_cast<const MyVector<T>*>(this)->at(n));
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::at(size_type n) const {
    if (n >= _allocatedSize) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return _elems[n];
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::operator[](size_type n) {
    return const_cast<value_type&>(
                static_cast<const MyVector<T>*>(this)->operator[](n));
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::operator[](size_type n) const {
    return _elems[n];
}

template <typename T>
MyVector<T>& MyVector<T>::operator+=(const_reference element) {
    push_back(element);
    return *this;
}

template <typename T>
MyVector<T> operator+(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    auto copy = lhs;
    for (size_t i = 0; i < rhs.size(); ++i) {
        copy.push_back(rhs[i]);
    }
    return copy;
}

template <typename T>
std::ostream& operator<<(std::ostream& oss, const MyVector<T>& rhs) {
    oss << "{";
    for (size_t i = 0; i < rhs.size(); ++i) {
        oss << rhs[i];
        if (i != rhs.size()-1) oss << ", ";
    }
    oss << "}";
    return oss;
}


// Member iterator functions
template <typename T>
typename MyVector<T>::reference MyVector<T>::iterator::operator*() {
    return _pointee->_elems[_index];
}

template <typename T>
typename MyVector<T>::iterator& MyVector<T>::iterator::operator+=(size_type diff) {
    _index += diff;
    return *this;
}


template <typename T>
typename MyVector<T>::iterator& MyVector<T>::iterator::operator++() {
    ++_index;
    return *this;
}

// Non-member iterator functions
template <typename T>
typename MyVector<T>::iterator
MyVector<T>::iterator::operator++(int) {
    auto copy = *this;
    ++_index;
    return copy;
}

template <typename T>
typename MyVector<T>::iterator operator+(
        typename MyVector<T>::size_type diff,
        const typename MyVector<T>::iterator& rhs) {
    auto copy = rhs;
    copy._index += diff;
    return copy;
}

// Iterator creators
template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
    return iterator(this, 0);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
    return iterator(this, size());
}


#endif // MYVECTOR_H
