#ifndef _MANAGER_H_
#define _MANAGER_H_
#include <set>
#include "Employee.h"


namespace mtm
{

    class Manager : public Citizen
    {
    private:
        int salary;
        std::set<Employee*,setElementsCompare> employees_set;

    public:
//constructors and destructors
        Manager(int id,std::string first_name,std::string last_name,int birth_year);
        ~Manager() override =default;

//setters and getters for the salary of the Manager
        int getSalary() const override;
        void setSalary(int raise);

//managing the employees underneath the Manager
        void addEmployee(Employee* employee);
        void removeEmployee(int employee);

//method for getting of a Manger's EmployeeSet ,mainly to use for the workplace for adjusting the salary
        std::set<Employee*,setElementsCompare> getEmployeeSet() const;

//printing a description of the manager,long being the more informative
        std::ostream& printShort(std::ostream& os) const override ;
        std::ostream& printLong(std::ostream& os) const override ;

//creating copy of the manager and returning a pointer to it.
        Manager* clone() const override;


    };


}

#endif