#pragma once

#include <random>
#include <string>
#include <sstream>

std::string Random_Name()
{
    std::vector<std::string> first_names{
    "Ann      ",
    "Andrew   ",
    "John     ",
    "Jane     ",
    "Bob      ",
    "Alice    ",
    "Bertram  ",
    "Monica   ",
    "Laura    ",
    "Eric     ",
    "Richard  ",
    "Karen    ",
    "Clara    ",
    "Rupert   ",
    "Bruce    ",
    "Martha   ",
    "Elizabeth",
    "Corey    ",
    "Nancy    ",
    "Joe      ",
    "Amy      ",
    "Mike     ",
    };

    std::vector<std::string> last_names{
    "Hendricks ",
    "Smith     ",
    "Gates     ",
    "Stein     ",
    "Warren    ",
    "Booker    ",
    "Williamson",
    "Walters   ",
    "Dunn      ",
    "Swanson   ",
    "Knope     ",
    "Haverford ",
    "Ludgate   ",
    "Meagle    ",
    "Favreau   ",
    "Vietor    ",
    "Lovett    ",
    "Pfeifer   ",
    "Rhodes    ",
    "Abrams    ",
    "McFaul    ",
    "Stone     ",
    "Sisley    ",
    "Hanneman  ",
    };
    std::mt19937 generator(std::random_device{}());

    std::uniform_int_distribution<std::size_t> fnd{ 0, first_names.size() - 1 };
    std::uniform_int_distribution<std::size_t> lnd{ 0, last_names.size() - 1 };

    std::size_t number_first_names = fnd(generator);
    std::size_t number_last_names = lnd(generator);

    std::stringstream Name;
    Name << first_names[number_first_names] << ' ' <<
        last_names[number_last_names];

    return Name.str();
}

std::string Random_Book_Name()
{
    std::vector<std::string> result{
    "Podstawy zapisu konstrukcji J. Bajkowski               ",
    "Rysunek techniczny maszynowy T. Dobrzanski             ",
    "Mechanika ogolna Leyko                                 ",
    "Mechanika ogolna J. Misiak                             ",
    "Mechanika techniczna J. Misiak                         ",
    "Zadania z mechaniki ogolnej J. Misiak                  ",
    "Mechanika analityczna R. Gutowski                      ",
    "Podstawy mechaniki plynow Grybos                       ",
    "Mechanika plynow M. Cialkowski                         ",
    "Dynamika gazow A. Tarnogrodzki                         ",
    "Hydrodynamika L.D. Landau, E.M. Lifszyc                ",
    "Wytrzymalosc materialow Z. Brzoska                     ",
    "Mechanika materialow i konstrukcji Bijak-Zochowsk      ",
    "Teoria statecznosci sprezystej S. Timoshenko, J.H. Gere"
    };

    // gets 'entropy' from device that generates random numbers itself
    // to seed a mersenne twister (pseudo) random generator
    std::mt19937 generator(std::random_device{}());

    // make sure all numbers have an equal chance. 
    // range is inclusive (so we need -1 for vector index)
    std::uniform_int_distribution<std::size_t> distribution(0, result.size() - 1);

    std::size_t number = distribution(generator);

    return result[number];
}

int Random_Book_Number()
{
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<std::mt19937::result_type> result(10, 20);
    return result(generator);
}

int Random_Account_Type()
{
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<std::mt19937::result_type> result(0, 1);      //0 - student, 1 - pracownik
    return result(generator);
}

bool Random_Privileges()
{
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<std::mt19937::result_type> result(0, 1);
    return result(generator);
}

