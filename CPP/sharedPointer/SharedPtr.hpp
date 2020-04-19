
#ifndef SMART_PTR_HPP_INCLUDED
#define SMART_PTR_HPP_INCLUDED

#include <iostream>
#include <cassert>

namespace ilrd
{

/**************** SharedPtr Class ****************/

template<typename T>
class SharedPtr
{

public:

    explicit SharedPtr(T* ptr = NULL);
    ~SharedPtr();
    SharedPtr(const SharedPtr& other);
    const SharedPtr& operator=(SharedPtr other);
    T* operator->();
    T& operator*();
    bool operator!() const;

    template<typename V>
    SharedPtr(const SharedPtr<V>& other);

private:

    template<typename V>
    friend class SharedPtr;
    size_t* m_ref_counter;
    T* m_ptr;
    void CleanUp();
};

/***********************************class function*****************************/

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr ) : m_ptr(ptr), m_ref_counter(new size_t(1)) {}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
    CleanUp();
}

template<typename T>
void SharedPtr<T>::CleanUp()
{
    if (!(--(*m_ref_counter)))
    {
        delete m_ptr;
        delete m_ref_counter;
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) : m_ref_counter(other.m_ref_counter), m_ptr(other.m_ptr)
{
    (*m_ref_counter)++;
}

template<typename T>
const SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr other)
{
    std::swap(m_ptr, other.m_ptr);
    std::swap(m_ref_counter, other.m_ref_counter);

    return *this;
}

template<typename T>
T* SharedPtr<T>::operator->()
{
    assert(*m_ref_counter >= 1 && "Invalid Pointer");

    return m_ptr;
}

template<typename T>
T& SharedPtr<T>::operator*()
{
    assert(*m_ref_counter >= 1 && "Invalid Pointer");

    return *m_ptr;
}

template<typename T>
bool SharedPtr<T>::operator!() const
{
    assert(*m_ref_counter >= 1 && "Invalid Pointer");

    return !m_ptr;
}

template<typename T>
template<typename V>
SharedPtr<T>::SharedPtr(const SharedPtr<V>& other) : m_ref_counter(other.m_ref_counter), m_ptr(other.m_ptr)
{
    (*m_ref_counter)++;
}


} // end namespace ilrd



#endif // SMART_PTR_HPP_INCLUDED

