#ifndef NUM_RANGE_HPP
#define NUM_RANGE_HPP

#include <type_traits>

template<typename T>
class num_iterator
{
    static_assert(std::is_integral_v<T>);
public:
    explicit num_iterator(T position = 0) noexcept : i{position} {}

    T operator*() const noexcept { return i; }
    num_iterator& operator++() noexcept { ++i; return *this; }
    bool operator!=(const num_iterator& other) const noexcept
    { return i != other.i; }    
private:
    T i;
};

/*
 * Represents a range of numbers which can be iterated.
 */    
template<typename T>
class num_range
{
public:
    num_range(T from, T to) noexcept : a{from}, b{to} {}
    num_iterator<T> begin() const noexcept { return num_iterator<T>{a}; }
    num_iterator<T> end() const noexcept { return num_iterator<T>{b}; }
private:
    T a, b;
};
    
#endif // NUM_RANGE_HPP
