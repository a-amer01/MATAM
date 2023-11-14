#include "Workplace.h"

using namespace mtm;

Workplace::Workplace( int id ,std::string workplace_name,int employee_salary ,
                      int manager_salary):id(id),employee_salary(employee_salary) ,
                                          manager_salary(manager_salary),workplace_name(workplace_name),Workplace_employees(),Workplace_managers(){}



std::string Workplace::getName() const{
    return workplace_name;
}

int Workplace::getId() const{
    return id;
}

int  Workplace::getWorkersSalary() const{
    return employee_salary;
}

int  Workplace::getManagersSalary() const{
    return manager_salary;
}


void Workplace::hireManager(Manager* manager)
{
    std::set<Manager*>::iterator itr ;
    for (itr = Workplace_managers.begin(); (*itr) != (*(Workplace_managers.end())); itr++){
        if ((*itr)->getId()==manager->getId()){
            throw ManagerAlreadyHired();
        }
    }


    if (manager->getSalary()>0){
        throw CanNotHireManager();
    }

    std::set<Employee*,setElementsCompare> manager_emps_set =(*manager).getEmployeeSet();
    std::set<Employee*,setElementsCompare>::iterator manager_emps = manager_emps_set.begin();

    for (unsigned int i=0;i<(manager_emps_set.size());i++){
        (*manager_emps)->setSalary(employee_salary);
        manager_emps++;
    }

    manager->setSalary(manager_salary);
    Workplace_managers.insert(manager);
}




void Workplace::fireManager(int manager)
{

    bool flag= false;
    std::set<Manager*>::iterator itr ;
    for (itr = Workplace_managers.begin(); (*itr) != (*(Workplace_managers.end())); itr++){
        if ((*itr)->getId()==manager){
            (*itr)->setSalary((-manager_salary));
            flag= true;
            break;
        }
    }

    if(flag==false){
        throw ManagerIsNotHired();
    }


    std::set<Employee*,setElementsCompare> manager_emps_set =(*itr)->getEmployeeSet();
    std::set<Employee*,setElementsCompare>::iterator manager_emps = manager_emps_set.begin();

    for (unsigned int i=0;i<(manager_emps_set.size());i++){
        (*manager_emps)->setSalary(-employee_salary);
        manager_emps++;
    }


    Workplace_managers.erase(itr);
}


void Workplace::fireEmployee(int manager , int employee)
{

    bool flag=true;
    std::set<Manager*>::iterator itr ;
    for (itr = Workplace_managers.begin(); (*itr) != (*(Workplace_managers.end())); itr++){
        if ((*itr)->getId()==manager){
            flag=false;
            break;
        }
    }

    if(flag!=false){
        throw ManagerIsNotHired();
    }

    (*(*itr)).removeEmployee(employee);

    std::set<Employee*>::iterator emp ;
    for (emp = Workplace_employees.begin(); (*emp) != (*(Workplace_employees.end())); emp++){
        if ((*emp)->getId()==employee){
            (*emp)->setSalary(-employee_salary);
            Workplace_employees.erase(emp);
            return;//our job here is done
        }
    }

}


Workplace* Workplace::clone() const
{
    return new Workplace(*this);
}


bool Workplace::hiredEmployeeInWorkplace(const Employee*  employee) const
{

    for (auto i:Workplace_employees){
        if (i->getId()==employee->getId()){
            return true;
        }

    }

    return false;
}