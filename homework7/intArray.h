#pragma once
#ifndef INTARRAY_H
#define INTARRAY_H

#include <algorithm> 
#include "myexception.h"


class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length) :
        m_length{ length }
    {
        if (length <= 0) 
        {
            throw bad_length();
        };

        if (length > 0)
            m_data = new int[length] {};
    }

    ~IntArray()
    {
        delete[] m_data;
        
    }

    IntArray(const IntArray& a) : IntArray(a.getLength())
    {
        std::copy_n(a.m_data, m_length, m_data); 
    }

    IntArray& operator=(const IntArray& a)
    {
        
        if (&a == this)
            return *this;

        
        reallocate(a.getLength());
        std::copy_n(a.m_data, m_length, m_data); 

        return *this;
    }

    void erase()
    {
        delete[] m_data;
       
        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        if (index < 0 || index > m_length) 
        {
            throw  bad_range();
        };
        return m_data[index];
    }



    void reallocate(int newLength)
    {
      
        erase();

       
        if (newLength <= 0)
            return;

      
        m_data = new int[newLength];
        m_length = newLength;
    }

 
    void resize(int newLength)
    {
        
        if (newLength == m_length)
            return;

       
        if (newLength <= 0)
        {
            erase();
            return;
        }

       

        
        int* data{ new int[newLength] };

       
        if (m_length > 0)
        {
            int elementsToCopy{ (newLength > m_length) ? m_length : newLength };
            std::copy_n(m_data, elementsToCopy, data); // copy the elements
        }

       
        delete[] m_data;

  
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        
        if (index < 0 || index > m_length)
        {
            throw  bad_range();
        };

     
        int* data{ new int[m_length + 1] };

       
        std::copy_n(m_data, index, data);

      
        data[index] = value;

       
        std::copy_n(m_data + index, m_length - index, data + index + 1);

        
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
       
        if (index < 0 || index > m_length)
        {
            throw  bad_range();
        };

        
        if (m_length == 1)
        {
            erase();
            return;
        }

       
        int* data{ new int[m_length - 1] };

       
        std::copy_n(m_data, index, data);

        
        std::copy_n(m_data + index + 1, m_length - index - 1, data + index);

        
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    
    void insertAtBeginning(int value) { insertBefore(value,0); }
    void insertAtEnd(int value) { insertBefore(value, m_length); }

    int getLength() const { return m_length; }
};

#endif