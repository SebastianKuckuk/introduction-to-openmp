#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    constexpr auto numSeats = 4;

    //# TODO: set the number of threads equal to numSeats

    int seats[numSeats];    //# one seat for each guest
    int place;              //# the place each guest takes
    int drinksLeft = 2;     //# the amount of drinks left per guest

    #pragma omp parallel default(none) //# TODO: add data sharing attributes
    {
        place = ???; //# TODO: each guest is assigned the place equal to their index

        seats[place] = place;
        std::cout << "Guest " << place << " takes a seat" << std::endl;

        while (drinksLeft) {
            std::cout << seats[place] << " drinks" << std::endl;
            --drinksLeft;
        }
    }

    std::cout << "The party is over" << std::endl;
}
