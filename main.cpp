#include <iostream>
#include "set.hpp"

int main()
{
    Set<int> s(10);

    s.add(10);
    s.add(30);
    s.add(20);
    s.remove(20);
    s.remove(40);
    s.add(50);

    std::cout << s.getSize() << ' ' << s.find(10) << '\n';

return 0;
}