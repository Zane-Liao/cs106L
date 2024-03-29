#ifndef GAPBUFFER_H
#define GAPBUFFER_H
#include <iostream> // cout for debug
#include <algorithm> // std::copy, std::move
#include <sstream> // stringstreams
#include <memory> // for unique_ptr

const int kDefaultSize = 10;

class GapBuffer {
public:
    using value_type = char;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = char*;
    using const_pointer = const char*;

    // Part 1
    GapBuffer();
    GapBuffer(size_type count, const value_type& val = value_type());
    void insert_at_cursor(const_reference element);
    void delete_at_cursor();
    reference get_at_cursor();
    reference at(size_type pos);

    // Part 2 - you need to declare these yourself
    const_reference at(size_type pos) const;
    const_reference get_at_cursor() const;
    size_type size() const;
    size_type cursor_index() const;
    bool empty() const;

    // Part 3 - you need to declare these yourself
    // member operators
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    // non-member, non-friend operators
    // we don't write these in our class declaration since they are non-members, non-friends
    // nevertheless, just so you see a clear outline of what you have to do, we put it here.

    // ostream& operator<<(ostream& os, const GapBuffer& buf);
    // bool operator==(const GapBuffer& left, const GapBuffer& right);
    // bool operator!=(const GapBuffer& left, const GapBuffer& right);
    // bool operator<(const GapBuffer& left, const GapBuffer& right);
    // bool operator>(const GapBuffer& left, const GapBuffer& right);
    // bool operator<=(const GapBuffer& left, const GapBuffer& right);
    // bool operator>=(const GapBuffer& left, const GapBuffer& right);

    /* Implemented for you */
    void move_cursor(int num);
    void reserve(size_type new_size);
    void debug() const;

private:
    pointer _elems; // uses array_index
    size_type _logical_size; // uses external_index
    size_type _buffer_size; // uses array_index
    size_type _cursor_index; // uses array_index
    size_type _gap_size;
    size_type to_external_index(size_type array_index);
    size_type to_array_index(size_type external_index);
    void move_to_left_of_buffer(size_type num);
};

GapBuffer::GapBuffer() {
    // TODO: Part 1
}

void GapBuffer::insert_at_cursor(const_reference element) {
    (void) element; // only here so it will compile

    // TODO: Part 1
}

void GapBuffer::delete_at_cursor() {
    // TODO: Part 1
}

typename GapBuffer::reference GapBuffer::get_at_cursor() {
    // TODO: Part 1

    return _elems[0]; // only here so it will compile
}

typename GapBuffer::reference GapBuffer::at(size_t pos) {
    // TODO: Part 1

    (void) pos;
    return _elems[0]; // only here so it will compile
}

typename GapBuffer::size_type GapBuffer::size() const {
    // TODO: Part 2

    return 0;
}

typename GapBuffer::size_type GapBuffer::cursor_index() const {
    // TODO: Part 2

    return 0; // only here so it will compile
}

bool GapBuffer::empty() const {
    // TODO: Part 2

    return false; // only here so it will compile
}

// Implement Part 3 functions here
// Members and non-member non-friends.





/* We've implemented these for you, do not edit! */
void GapBuffer::move_cursor(int delta) {
    int new_index = _cursor_index + delta;
    if (new_index < 0 || new_index > static_cast<int>(_buffer_size)) {
        throw std::string("move_cursor: delta moves cursor out of bounds");
    }
    if (delta > 0) {
        pointer begin_move = _elems + _cursor_index + _gap_size;
        pointer end_move = begin_move + delta;
        pointer destination = _elems + _cursor_index;
        std::move(begin_move, end_move, destination);
    } else {
        pointer end_move = _elems + _cursor_index;
        pointer begin_move = end_move + delta;
        pointer destination = _elems + _cursor_index + _gap_size + delta;
        std::move(begin_move, end_move, destination);
    }
    _cursor_index += delta;
}

void GapBuffer::reserve(size_type new_size) {
    if (size() >= new_size) return;
    pointer new_elems = new char[new_size];
    std::move(_elems, _elems + _cursor_index, new_elems);
    size_t new_gap_size = new_size - _buffer_size;
    std::move(_elems+ _cursor_index, _elems + _buffer_size,
              new_elems + _cursor_index + new_gap_size);
    _buffer_size = new_size;
    _elems = std::move(new_elems);
    _gap_size = new_gap_size;
}

void GapBuffer::debug() const {
    std::cout << "[";
    for (size_t i = 0; i < _buffer_size; ++i) {
        if (i == _cursor_index) {
            std::cout << "|";
        } else {
            std::cout << " ";
        }
        if (i >= _cursor_index && i < _cursor_index + _gap_size) {
            std::cout << "*";
        } else {
            std::cout << _elems[i];
        }
    }
    std::cout << (_cursor_index == _buffer_size ? "|" : " ");
    std::cout << "]" << std::endl;
}

typename GapBuffer::size_type GapBuffer::to_external_index(size_type array_index)  {
    if (array_index < _cursor_index) {
        return array_index;
    } else if (array_index >= _cursor_index + _gap_size){
        return array_index - _cursor_index;
    } else {
        throw ("to_external_index: array_index is out of bounds!");
    }
}

typename GapBuffer::size_type GapBuffer::to_array_index(size_type external_index)  {
    if (external_index < _cursor_index) {
        return external_index;
    } else {
        return external_index + _gap_size;
    }
}

#endif // GAPBUFFER_H
