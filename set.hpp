#ifndef BIKERENTAL_SET_HPP
#define BIKERENTAL_SET_HPP

#include <iostream>
#include <utility>

class SetException
{
public:
    explicit SetException(std::string _msg) : message(std::move(_msg)) {}
    virtual std::string GetMsg() const
    {
        return message;
    }

private:
    std::string message;
};

class SetContainerException : public SetException
{
public:
    explicit SetContainerException(std::string _msg = "") : SetException(std::move(_msg)) {}

};

class SetIteratorException : public SetException
{
public:
    explicit SetIteratorException(std::string _msg = "") : SetException(std::move(_msg)) {}

};

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
    bool find(const T&) const;
    int getSize() const;

    template <typename U>
    friend class SetIterator;

private:
    TNode<T> *v;
    int size{};
    int capacity{};
    int head = -1;
    int tail = -1;
    int first_empty = -1;

    int findPos(const T&) const;
    void Resize(int n = 2);
};

template <typename T>
Set<T>::Set(int n) : capacity(n)
{
    //descr: create a new empty set
    //pre: true
    //post: s є S, s is an empty set, with a given capacity(n)

    if(capacity <= 0)
        throw SetContainerException{"Set capacity must be greater than 0."};

    v = new TNode<T>[capacity];
    first_empty = 0;
    for(int i = 0; i < capacity - 1; ++i)
        v[i].next = i + 1;
}

template <typename T>
Set<T>::~Set()
{
    //descr: destroys a set
    //pre: s є S
    //post: the set s was destroyed

    delete[] v;
    v = nullptr;
}

template <typename T>
Set<T>::Set(const Set<T> &s) : capacity(s.capacity), size(s.size)
{
    //copy constructor

    for(int i = 0; i < size; ++i)
        v[i] = s.v[i];
}

template <typename T>
Set<T>& Set<T>::operator=(const Set<T> &s)
{
    //copy operator

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
int Set<T>::getSize() const
{
    //descr: returns the number of elements in set
    //pre: s є S
    //post: size ← number of elements from s

    return size;
}

template <typename T>
int Set<T>::findPos(const T &t) const
{
    //returns position of t in dlla or -1 if it doesn't exist

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
bool Set<T>::find(const T &t) const
{
    //descr: verifies if an element is in the set
    //pre: s Є S, t Є Telem
    //post: returns true if t is in the set or false otherwise

    return (findPos(t) != -1);
}

template <typename T>
void Set<T>::add(const T &t)
{
    //descr: adds a new element to the set
    //pre: s є S, e є Telem
    //post: s’ є S, s’ = s U {t} (t is added only if it is not in s yet.
    //       If s contains the element e already, no change is made).

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
        else
            throw SetContainerException{"Element already exists."};
    }
    else
        throw SetContainerException{"Set is full."};
}

template <typename T>
void Set<T>::remove(const T &t)
{
    //descr: removes an element from the set
    //pre: s є S, e є Telem
    //post: s ∈ S, s 0 = s \ {t} (if t is not in s, s is not changed)

    int pos = findPos(t);

    if(pos != -1)
    {
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

        --size;
    }
    else
        throw SetContainerException{"Element doesn't exist."};
}

template <typename T>
class SetIterator
{
public:
    explicit SetIterator(Set<T>* _set) : set(_set)
    {
        //set: a set on dlla
        //currentElem: integer(representing the position in dlla,
        //              initialized with the position of the header)

        current = set->head;
    }

    void next();
    bool valid() const;
    T getCurrent() const;
    void operator++();
    void reset();

private:
    Set<T>* set;
    int current;
};

template <typename T>
void SetIterator<T>::next()
{
    //descr: moves the current element from the set to the 	next or makes it invalid
    //pre: it є I is valid
    //post: it points to the next element from the container, if ex-current was valid

    if(valid())
        current = set->v[current].next;
    else
        throw SetIteratorException{"Iterator isn't valid."};
}

template <typename T>
void SetIterator<T>::operator++()
{
    if(valid())
        current = set->v[current].next;
    else
        throw SetIteratorException{"Iterator isn't valid."};
}

template <typename T>
bool SetIterator<T>::valid() const
{
    //descr: verifies if the iterator is valid
    //pre: it є I
    //post: returns true if it points to a valid element or false otherwise

    return current != -1;
}

template <typename T>
T SetIterator<T>::getCurrent() const
{
    //descr: returns the current element from the iterator
    //pre: it є I is valid
    //post: t є TElem, t is the current element from it

    if(valid())
        return set->v[current].info;
    else
        throw SetIteratorException{"Iterator isn't valid."};
}

template <typename T>
void SetIterator<T>::reset()
{
    //make iterator point to the head element of the container

    current = set->head;
}

#endif //BIKERENTAL_SET_HPP
