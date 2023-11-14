#ifndef SKILL_H_
#define SKILL_H_
#include <iostream>
#include <string>
#include "exceptions.h"

namespace mtm{

    class Skill
    {
    private:
        int id;
        int points;
        std::string skill_name;

    public:
//constructors and destructors and so...,the default = operator in enough
        Skill( int id , std::string skill_name , int point);
        Skill(int id);
        Skill(const Skill& skill) =default;
        ~Skill()=default;

//methods for acquiring basic information of a certain skill
        int getRequiredPoints() const;
        int getId() const ;
        std::string getName() const ;

//operator overloading for compare skills based on their id
        Skill& operator+=(const int);
        Skill operator++(int);
        Skill operator+(int);
        friend Skill operator+(int to_add, const Skill&);
        friend std::ostream& operator<<(std::ostream&, const Skill& Skill);

    };

//functions for having basic comparison between skills based on their id
    bool operator<(const Skill&, const Skill&);
    bool operator==(const Skill&, const Skill&);
    bool operator>(const Skill& first , const Skill& second );
    bool operator<=(const Skill&, const Skill&);
    bool operator>=(const Skill&, const Skill&);
    bool operator!=(const Skill&, const Skill&);
    Skill operator+(const Skill&, const Skill&);
    Skill operator+(int to_add, const Skill&);
    std::ostream& operator<<(std::ostream&, const Skill& Skill);

    inline Skill operator+(int to_add, const Skill& skill)
    {
        if (to_add<0){
            throw NegativePoints();
        }
        Skill temp =skill;
        temp.points=temp.points+to_add;
        return temp;
    }

    inline std::ostream& operator<<(std::ostream& os, const Skill& skill){
        os << skill.getName() <<std::endl;
        return os;
    }

}


#endif //SKILL_H_