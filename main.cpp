#include <iostream>
#include <fstream>
#include <ctime>
#include "set.hpp"
#include "rental.hpp"
#include "tests.hpp"

void PrintMenu();

int main()
{
    Test test;

    int n;
    std::ifstream f("number");

    f >> n;
    f.close();

    Set<Rental> rentals(n);
    int comm;

    PrintMenu();
    while(1)
    {
        std::cout << ">>";

        std::cin >> comm;

        if(comm == 0)
            exit(0);
        else if(comm == 1)
            PrintMenu();
        else if(comm == 2)
        {
            std::string cnp;

            std::cout << "Type CNP: ";
            std::cin >> cnp;

            try
            {
                rentals.add(Rental(cnp, time(nullptr)));
                std::cout << "Rented!";
            }
            catch(SetException &ex)
            {
                std::cout << ex.GetMsg() << '\n';
            }
        }
        else if(comm == 3)
        {
            std::string cnp;

            std::cout << "Type CNP: ";
            std::cin >> cnp;

            try
            {
                rentals.remove(Rental(cnp));
                std::cout << "Returned!";
            }
            catch(SetException &ex)
            {
                std::cout << ex.GetMsg() << '\n';
            }
        }
        else if(comm == 4)
        {
            SetIterator<Rental> it(&rentals);

            for(; it.valid(); ++it)
                std::cout << " - " << it.getCurrent().GetCNP() << '\n';
        }
        else if(comm == 5)
        {
            SetIterator<Rental> it(&rentals);

            for(; it.valid(); ++it)
            {
                int mins = (int)(it.getCurrent().GetTime() - time(nullptr)) / 60;

                if(mins > 60)
                    std::cout << " - " << it.getCurrent().GetCNP() << " | " << mins <<
                              " | " << ((mins - 60) / 30 + 1) * 4 << " RON(penalty)" << '\n';
            }
        }
        else if(comm == 6)
        {
            SetIterator<Rental> it(&rentals);

            for(; it.valid(); ++it)
            {
                int mins = (int)(it.getCurrent().GetTime() - time(nullptr)) / 60;

                if(mins > 660)
                    std::cout << " - " << it.getCurrent().GetCNP() << '\n';
            }
        }
        else
            std::cout << "Invalid command!\n";
    }

    //pdf(completez cu chestii notate, text problema)

return 0;
}

void PrintMenu()
{
    std::cout << "0. Exit\n" <<
                 "1. Help\n" <<
                 "2. Rent\n" <<
                 "3. Return\n" <<
                 "4. Display all\n" <<
                 "5. Display with delay\n";
                 "6. Display possibly stolen\n\n";
}