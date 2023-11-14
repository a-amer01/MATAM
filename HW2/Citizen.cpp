#include "Citizen.h"

using namespace mtm;

Citizen::Citizen( int id ,std::string first_name ,std::string last_name, int birth_year):
        id(id),first_name(first_name),last_name(last_name),birth_year(birth_year){}

//basic methods////////
int Citizen::getId() const {
    return id;
}

int Citizen::getBirthYear() const {
    return birth_year;
}

std::string Citizen::getFirstName() const {
    return first_name;
}

std::string Citizen::getLastName() const {
    return last_name;
}



bool mtm::operator<=(const Citizen& first , const Citizen& second ){
    return (!(first>second));
}

bool  mtm::operator>(const Citizen& first, const Citizen& second ){
    return !((first<second) || (first==second));
}

bool mtm::operator>=(const Citizen& first , const Citizen& second ){
    return (!(first<second));
}

bool mtm::operator!=(const Citizen& first , const Citizen& second ){
    return (!(first==second));
}