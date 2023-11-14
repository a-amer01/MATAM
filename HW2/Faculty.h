#ifndef _FACULTY_H_
#define  _FACULTY_H_
#include "Employee.h"

namespace mtm{

    template<class T>
    class Faculty
    {
    private:
        int id;
        Skill skill;
        int added_points;
        T*  isAccepted;
    public:
//constructors and destructors
        Faculty( int id,Skill skill, int added_points,T* isAccepted);
        ~Faculty()=default;

//getters for the specified class fields
        Skill getSkill() const;
        int getId() const;
        int getAddedPoints() const;

//method to teach an employee a skill and add it to his set of skills,if he matches the condition otherwise
//we throw an EmployeeNotAccepted exception
        void teach(Employee* employee);

    };

/*a class to be inherited from in the main,a condition (function object) for being able to learn in the faculty*/
    class Condition{
    public:
        virtual bool operator()(Employee* employee) = 0;
    };

}//end of the namespace mtm


using namespace mtm ;
template <typename T>
Faculty<T>::Faculty( int id,Skill skill ,int added_points,T* isAccepted):
        id(id),skill(skill), added_points(added_points),isAccepted(isAccepted){}

template <typename T>
Skill Faculty<T>::getSkill() const{
    return skill;
}

template <typename T>
int Faculty<T>::getId() const{
    return id;
}

template <typename T>
int  Faculty<T>::getAddedPoints() const{
    return added_points;
}

template <typename T>
void Faculty<T>::teach(Employee* employee)
{
    if (!(*isAccepted)(employee)){
        throw EmployeeNotAccepted();
    }

    employee->learnSkill(skill);
    employee->setScore(added_points);
}

#endif