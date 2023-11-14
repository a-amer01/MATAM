#include "Skill.h"

using namespace mtm;


Skill::Skill( int id , std::string skill_name , int points):
        id(id),points(points),skill_name(skill_name){}

Skill::Skill(int id):id(id){}


int Skill::getRequiredPoints() const {
    return points;
}

int Skill::getId() const{
    return id;
}

std::string  Skill::getName() const{
    return skill_name;
}


Skill& Skill::operator+=(const int points)
{
    if (points<0){
        throw NegativePoints();
    }

    (this->points)+=points;
    return *this;
}

Skill Skill::operator++(int)
{
    Skill temp = *this;
    (this->points)++;
    return temp;
}

Skill operator+(const Skill& first ,const Skill& second)
{//using += deals with exception.

    Skill result = first;
    result += (second.getRequiredPoints());

    return result;
}

Skill Skill::operator+(int to_add)
{
    if (to_add<0){
        throw NegativePoints();
    }

    Skill temp =*this;
    temp.points=temp.points+to_add;
    return temp;
}


bool mtm::operator<(const Skill& first, const Skill& second ) {
    return first.getId() < second.getId();
}

bool mtm::operator==(const Skill& first, const Skill& second ){
    return (first.getId()==second.getId());
}

bool mtm::operator!=(const Skill& first , const Skill& second){
    return (!(first==second));
}

bool mtm::operator>(const Skill& first , const Skill& second ){
    return !((first<second) || (first==second));
}

bool mtm::operator<=(const Skill& first , const Skill& second){
    return (!(first>second));
}

bool mtm::operator>=(const Skill& first, const Skill& second){
    return (!(first<second));
}



//the end of the overloaded function and file




