#pragma once
#include <exception>


class bad_range : public std::exception 
{
public:
    virtual const char* what() const noexcept override
    {
        return "ERROR:bad range";
    }
};
class bad_length : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ERROR: bad_length";
    }
};