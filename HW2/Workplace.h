#ifndef WORKPLACE_H_
#define WORKPLACE_H_
#include <iostream>
#include <set>
#include "Manager.h"


namespace mtm{


    class Workplace
    {
    private:
        int id;
        int employee_salary;
        int manager_salary;
        std::string workplace_name;
        std::set<Employee*,setElementsCompare> Workplace_employees;//set of all the Employees in the company
        std::set<Manager*,setElementsCompare> Workplace_managers;//set of all the managers in the company

    public:
//constructors and destructors
        Workplace( int id,std::string workplace_name ,int employee_salary,int manager_salary);
        ~Workplace()=default;

//methods for acquiring basic information of a certain Workplace
        std::string getName() const;
        int getId() const;
        int getWorkersSalary() const;
        int getManagersSalary() const;

//method to check the possibility of an employee being accepted into the workplace according to a certain
//hiring condition and if he does match that condition, we add him to the workplace under the manager we have received
        template<typename T>
        void hireEmployee(T hiring_cond , Employee*  employee , int manager_id);

//methods to  handle hiring and firing of an employee and manager(including the above method)
        void hireManager(Manager* manager);
        void fireManager( int manager);
        void fireEmployee( int manger ,  int employee);

//additional helper method for use in the city class, it receives an Employee and returns true if he works in
//the Workplace otherwise it returns false
        bool hiredEmployeeInWorkplace(const Employee* employee) const ;

//method for printing a description of the workplace
        friend std::ostream& operator<<(std::ostream& os ,const Workplace& workplace);
//
        Workplace* clone() const;

    };


    template<typename T>
    void Workplace::hireEmployee(T hiring_cond ,Employee* employee , int manager_id)
    {
        if (hiring_cond(employee)!=true){
            throw EmployeeNotSelected();
        }

        bool flag=true;
        std::set<Manager*>::iterator manager_itr ;
        for (manager_itr = Workplace_managers.begin(); (*manager_itr) != (*(Workplace_managers.end())); manager_itr++){
            if ((*(*manager_itr)).getId()==manager_id){
                flag=false;
                break;
            }
        }


        if (flag==true){
            throw ManagerIsNotHired();
        }

        (*(*manager_itr)).addEmployee(employee);
        Workplace_employees.insert(employee);
        employee->setSalary(employee_salary);
    }


    inline std::ostream& operator<<(std::ostream& os ,const Workplace& workplace)
    {
        std::set<Manager*>::iterator itr ;
        os<<"Workplace name - "<<workplace.workplace_name;

        if (workplace.Workplace_managers.size()>0){
            os<<" Groups:"<<std::endl;
        }else{
            os<<std::endl;
        }

        for (itr =workplace.Workplace_managers.begin(); (itr)!=((workplace.Workplace_managers.end())); itr++){
            os<<"Manager ";
            (*(*itr)).printLong(os);
        }

        return os;
    }




}

#endif