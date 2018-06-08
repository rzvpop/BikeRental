#ifndef BIKERENTAL_TESTS_HPP
#define BIKERENTAL_TESTS_HPP

#include "set.hpp"

class Test
{
public:
    Test();
    void TestSet();
    void TestIterator();

private:
    Set<std::string> set{5};
};


#endif //BIKERENTAL_TESTS_HPP
