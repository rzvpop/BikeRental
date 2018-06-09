#include "rental.hpp"

std::string Rental::GetCNP()
{
    return cnp;
}

time_t Rental::GetTime()
{
    return time;
}

bool Rental::operator==(const Rental &r) const
{
    return (cnp == r.cnp);
}
