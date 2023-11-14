#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include <set>
#include "Citizen.h"
#include "Skill.h"

namespace mtm{

    class Employee : public Citizen
    {
    private:
        int salary;
        int score;
        std::set<Skill> skills;

    public:
//constructors and destructors
        Employee( int id ,std::string first_name ,std::string last_name, int birth_year);
        ~Employee() override =default ;
        Employee(const Employee&) =default;

//methods for getting/setting salary and score information of a certain Employee
        int getSalary() const override  ;
        int getScore() const ;
        void setSalary(int raise);
        void setScore(int score);

//methods for handling a certain Employee's skills
        void learnSkill(const Skill skill)  ;
        void forgetSkill(const  int skill);
        bool hasSkill( int skill) const;

//printing a description for an employee
        std::ostream& printShort(std::ostream& os) const override ;
        std::ostream& printLong(std::ostream& os) const override ;

//creates a new copy of said Employee and returns a pointer to it
        Employee* clone() const override;

    };

}
#endif


