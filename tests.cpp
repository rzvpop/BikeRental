#include "tests.hpp"
#include <cassert>
#include <vector>

Test::Test()
{
    TestSet();
    TestIterator();
}


void Test::TestSet()
{
    set.add("apple");
    set.add("banana");
    set.add("weed");
    set.remove("banana");
    set.add("blackberry");

    std::string str = "banana";

    assert(!set.find("banana"));
    assert(set.find("weed"));
    assert(set.getSize() == 3);



    try
    {
        Set<int> set1(0);
    }
    catch(SetContainerException &ex)
    {
        assert(ex.GetMsg() == "Set capacity must be greater than 0.");
    }

    try
    {
        set.add("weed");
    }
    catch(SetContainerException &ex)
    {
        assert(ex.GetMsg() == "Element already exists.");
    }

    try
    {
        set.add("pear");
        set.add("peach");
        set.add("kiwi");
    }
    catch(SetContainerException &ex)
    {
        assert(ex.GetMsg() == "Set is full.");
    }

    try
    {
        set.remove("sth");
    }
    catch(SetContainerException &ex)
    {
        assert(ex.GetMsg() == "Element doesn't exist.");
    }
}

void Test::TestIterator()
{
    std::vector<std::string> v{"apple", "weed", "blackberry", "pear", "peach"};
    int i = 0;
    SetIterator<std::string> it(&set);

    for(; it.valid(); it.next())
    {
        assert(it.getCurrent() == v[i]);
        ++i;
    }

    it.reset(), i = 0;
    for(; it.valid(); ++it)
    {
        assert(it.getCurrent() == v[i]);
        ++i;
    }

    try
    {
        it.next();
    }
    catch(SetIteratorException &ex)
    {
        assert(ex.GetMsg() == "Iterator isn't valid.");
    }

    try
    {
        ++it;
    }
    catch(SetIteratorException &ex)
    {
        assert(ex.GetMsg() == "Iterator isn't valid.");
    }

    try
    {
        it.getCurrent();
    }
    catch(SetIteratorException &ex)
    {
        assert(ex.GetMsg() == "Iterator isn't valid.");
    }
}