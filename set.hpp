#ifndef BIKERENTAL_SET_HPP
#define BIKERENTAL_SET_HPP

#include <iostream>

template <typename T>
struct TNode
{
    T info;
    int next;
    int prev;
};

template <typename T>
class Set
{
public:
    explicit Set(int n = 0);
    Set(const Set &s);
    ~Set();

    Set& operator=(const Set &s);

    void add(const T&);
    void remove(const T&);
    bool find(const T&);
    int getSize();
    T getElemOnPos(int pos);
    void Print()
    {
        for(int i = 0; i < size; ++i)
            std::cout << i << '-' << v[i].info << ' ';
        std::cout << '\n';
    }

private:
    TNode<T> *v;
    int size{};
    int capacity{};
    int head = -1;
    int tail = -1;
    int first_empty = -1;

    int findPos(const T&);
    void Resize(int n = 2);
};

template <typename T>
Set<T>::Set(int n) : capacity(n)
{
    v = new TNode<T>[capacity];
    first_empty = 0;
    for(int i = 0; i < capacity - 1; ++i)
        v[i].next = i + 1;


}

template <typename T>
Set<T>::~Set()
{
    delete[] v;
}

template <typename T>
Set<T>::Set(const Set<T> &s) : capacity(s.capacity), size(s.size)
{
    for(int i = 0; i < size; ++i)
        v[i] = s.v[i];
}

template <typename T>
Set<T>& Set<T>::operator=(const Set<T> &s)
{
    if(this == &s)
        return *this;

    delete[] v;
    v = nullptr;

    capacity = s.capacity;
    size = s.size;

    v = new T[capacity];

    for(int i = 0; i < size; ++i)
        v[i] = s.v[i];

    return  *this;
}

template <typename T>
T Set<T>::getElemOnPos(int pos)
{
    int curr_node = head;

    if(pos < size)
    {
        while(pos)
        {
            curr_node = v[curr_node].next;
            --pos;
        }

        return v[curr_node].info;
    }
}

template <typename T>
void Set<T>::Resize(int n)
{
    capacity = n * capacity + 1;
    auto *new_v = new TNode<T>[capacity];

    for(int i = 0; i < size; ++i)
        new_v[i] = v[i];

    delete[] v;

    v = new_v;
}

template <typename T>
int Set<T>::getSize()
{
    return size;
}

template <typename T>
int Set<T>::findPos(const T &t)
{
    int cnode = head, pos = -1;

    while(pos == -1 && cnode != -1)
    {
        if(v[cnode].info == t)
        {
            pos = cnode;
        }

        cnode = v[cnode].next;
    }

    return pos;
}

template <typename T>
bool Set<T>::find(const T &t)
{
    return findPos(t) != -1;
}

template <typename T>
void Set<T>::add(const T &t)
{
    if(size < capacity)
    {
        if(findPos(t) == -1)
        {
            if (head == -1)
            {
                head = 0;
                tail = 0;
                first_empty = 1;
                v[head].next = -1;
                v[head].prev = -1;
                v[head].info = t;
            }
            else
            {
                v[tail].next = first_empty;
                v[first_empty].prev = tail;
                tail = first_empty;
                first_empty = v[first_empty].next;
                v[tail].next = -1;
                //std::cout << first_empty << '\n';
                v[tail].info = t;
            }
            ++size;
        }
    }
}

template <typename T>
void Set<T>::remove(const T &t)
{
    int pos = findPos(t);

    if(pos != -1)
    {
        --size;

        if(v[pos].prev != -1)
            v[v[pos].prev].next = v[pos].next;
        else
            head = v[pos].next;
        if(v[pos].next != -1)
            v[v[pos].next].prev = v[pos].prev;
        else
            tail = v[pos].prev;

        v[pos].prev = -1;
        v[first_empty].prev = pos;
        v[pos].next = first_empty;
        first_empty = pos;
    }
}

template <typename T>
class SetIterator
{
public:
    explicit SetIterator(Set<T>* _set, int pos = 0) : set(_set), current(pos)
    {
        if(pos >= set->getSize())
            pos = 0;
    }

    void next();
    bool valid();
    T getCurrent();

private:
    Set<T>* set;
    int current;
};

template <typename T>
void SetIterator<T>::next()
{
    if(valid())
        ++current;
}

template <typename T>
bool SetIterator<T>::valid()
{
    return current < set->getSize();
}

template <typename T>
T SetIterator<T>::getCurrent()
{
    return set->getElemOnPos(current);
}

#endif //BIKERENTAL_SET_HPP
