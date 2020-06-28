#pragma once
#include <cstddef>

template <size_t n>
class Fibonacci
{
public:
    enum {value = (Fibonacci<n-1>::value + Fibonacci<n-2>::value)};
};

template<>
class Fibonacci<0>
{
    public:
    enum {value = 0};
};

template<>
class Fibonacci<1>
{
    public:
    enum {value = 1};
};

int fibonacci(int n)
{
    if(n<2)
    {
        return n;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}