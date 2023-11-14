#ifndef _CITY_H_
#define _CITY_H_
#include "Workplace.h"
#include "Faculty.h"

namespace mtm{

    class City
    {
    private:
        std::string city_name;
        std::set<Employee*,setElementsCompare> employees;
        std::set<Manager*,setElementsCompare>  managers;
        std::set<Workplace*> work_places;
        std::set<Faculty<Condition>*>  faculties ;

//private methods for code readability and maintenance
        Employee* findEmployee(int employee) const;
        Manager* findManager(int manager) const;
        Workplace* findWorkPlace(int workplace) const;
        void existingCitizen(int citizen) const;
    public:

//constructors and destructors
        City(std::string city_name);
        ~City();

//methods for adding elements in the city class
        void addEmployee( int id ,std::string first_name ,std::string last_name, int birth_year);
        void addManager( int id ,std::string first_name ,std::string last_name, int birth_year);
        void addFaculty( int id,Skill skill, int added_points,Condition* cond);
        void createWorkplace( int id,std::string workplace_name , int employee_salary,int manager_salary);

//method for teaching an employee a skill if he's accepted to learn at the faculty that teaches it
        void teachAtFaculty( int employee ,  int faculty);

//methods for managing managers and employees inside the work place
        template<typename T>
        void hireEmployeeAtWorkplace(T cond, int employee, int manager, int workplace);
        void hireManagerAtWorkplace( int manager, int workplace);
        void fireEmployeeAtWorkplace( int employee, int manager, int workplace);
        void fireManagerAtWorkplace( int manager, int workplace);

//method for printing the names of all the employees in the city that has a salary above the one sent to the method
        int  getAllAboveSalary(std::ostream& os ,int salary) const;

//method for checking(boolean) if two given employees work at the same workplace
        bool isWorkingInTheSameWorkplace( int first ,  int second) const;

//method for printing all the employees in the city that have a given skill
        void printAllEmployeesWithSkill(std::ostream& os ,Skill (skill)) const;
    };



    template<typename T>
    void City::hireEmployeeAtWorkplace(T cond, int employee, int manager, int workplace)
    {
        Employee* emp=findEmployee(employee);
        Manager* man=findManager(manager);
        Workplace* w_place=findWorkPlace(workplace);
        w_place->hireEmployee(cond,emp,man->getId());
        //the reason to use get id for manager is to not have an unused variable
    }
}

#endif