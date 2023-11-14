#include "Manager.h"


using namespace mtm;

Manager::Manager( int id ,std::string first_name ,std::string last_name, int birth_year):
        Citizen(id,first_name,last_name,birth_year),salary(0),employees_set(){}




int Manager::getSalary()const{
    return salary;
}

void Manager::setSalary(int raise){
    salary+=raise;
    if (salary<0){
        salary=0;
    }
}



void Manager::addEmployee(Employee* employee)
{
    std::set<Employee*>::iterator emp;
    for (emp = employees_set.begin(); (*emp) != (*(employees_set.end())); emp++){
        if ((*emp)->getId()==employee->getId()){
            throw EmployeeAlreadyHired();
        }
    }

    employees_set.insert(employee);
}


void Manager::removeEmployee(int employee)
{
    for(auto i:employees_set){
        if (i->getId()==employee){
            employees_set.erase(i);
            return;
        }
    }
    throw EmployeeIsNotHired();
}

std::set<Employee*,setElementsCompare> Manager::getEmployeeSet() const
{
    return employees_set;
}

std::ostream& Manager::printShort(std::ostream& os) const
{
    os<<first_name<<" " <<last_name<<std::endl;
    os<<"Salary: "<<salary<<std::endl;
    return os;
}

std::ostream& Manager::printLong(std::ostream& os) const
{
    std::set<Employee*>::iterator it = employees_set.begin();
    os<< first_name << " " << last_name << std::endl;
    os<<"id - "<< id << " birth_year - " << birth_year<<std::endl;
    os<<"Salary: " << salary <<std::endl;

    if (employees_set.size()>0){
        os<<"Employees: " <<std::endl;
    }

    for(auto emp:employees_set){

        emp->printShort(os);
    }

    return os;
}

Manager* Manager::clone() const
{
    Manager* clone_manager = static_cast<Manager*>(new Manager(*this));
    clone_manager->salary=this->salary;
    return clone_manager;
}