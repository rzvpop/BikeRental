#ifndef BIKERENTAL_RENTAL_HPP
#define BIKERENTAL_RENTAL_HPP

#include <string>
#include <utility>

class Rental
{
public:
    explicit Rental(std::string _cnp = "", time_t _time = 0) : cnp(std::move(_cnp)), time(_time) {}

    std::string GetCNP();
    time_t GetTime();

    bool operator==(const Rental&) const;

private:
    std::string cnp;
    time_t time;
};


#endif //BIKERENTAL_RENTAL_HPP
