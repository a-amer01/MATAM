#include "City.h"

using namespace mtm;
City::City(std::string city_name):city_name(city_name),employees(),managers(),work_places(),faculties(){}

City::~City()
{


    for(auto i:employees){
        if(i != nullptr){
            delete (i);
            i=nullptr;
        }
    }

    for(auto i:managers){
        if(i != nullptr){
            delete (i);
            i=nullptr;
        }
    }

    for(auto i:work_places){
        if(i != nullptr){
            delete (i);
            i=nullptr;
        }
    }

    for(auto i:faculties){
        if(i != nullptr){
            delete (i);
            i=nullptr;
        }
    }

}



//helper function for ease of read and  code duplication and maintenance
void City::existingCitizen(int citizen) const
{
    std::set<Manager*>::iterator man;
    std::set<Employee*>::iterator itr;

    for (itr = employees.begin(); itr != (employees.end()); itr++){
        if ((*itr)->getId()==citizen){
            throw CitizenAlreadyExists();
        }
    }


    for (man = managers.begin(); man != managers.end(); man++){
        if ((*man)->getId()==citizen){
            throw CitizenAlreadyExists();
        }
    }

}

Employee* City::findEmployee(int employee) const
{
    std::set<Employee*>::iterator emp;
    for (emp = employees.begin(); emp != employees.end(); emp++){
        if ((*emp)->getId()==employee){
            return (*emp);
        }
    }
    throw EmployeeDoesNotExist();
}

Manager* City::findManager(int manager) const
{
    std::set<Manager*>::iterator man;
    for (man = managers.begin(); man != managers.end(); man++){
        if ((*man)->getId()==manager){
            return (*man);
        }
    }
    throw ManagerDoesNotExist();
}

Workplace* City::findWorkPlace(int workplace) const
{
    std::set<Workplace*>::iterator w_plc ;
    for (w_plc = work_places.begin(); w_plc != work_places.end(); w_plc++){
        if ((*w_plc)->getId()==workplace){
            return (*w_plc);
        }
    }
    throw WorkplaceDoesNotExist();
}
//end of helper functions


void City::addEmployee( int id ,std::string first_name ,std::string last_name, int birth_year)
{
    existingCitizen(id);
    Employee emp1(id,first_name,last_name,birth_year);
    Employee* employee=emp1.clone();
    employees.insert(employee);
}



void City::addManager( int id ,std::string first_name ,std::string last_name, int birth_year)
{
    existingCitizen(id);
    Manager man1(id,first_name,last_name,birth_year);
    Manager* manager=man1.clone();
    managers.insert(manager);
}

void City::addFaculty( int id,Skill skill ,int added_points,Condition* cond)
{
    std::set<Faculty<Condition>*>::iterator itr ;
    for (itr = faculties.begin(); itr != faculties.end(); itr++){
        if ((*itr)->getId()==id){
            throw FacultyAlreadyExists();
        }
    }
//we didn't make a clone method for this one.
    Faculty<Condition>* faculty =new Faculty<Condition>(id,skill,added_points,cond);
    faculties.insert(faculty);
}



void City::createWorkplace( int id,std::string workplace_name , int employee_salary,int manager_salary)
{

    std::set<Workplace*>::iterator itr ;
    for (itr = work_places.begin();itr != work_places.end(); itr++){
        if ((*itr)->getId()==id){
            throw WorkplaceAlreadyExists();
        }
    }

    Workplace* work_place =new Workplace(id ,workplace_name,employee_salary,manager_salary);
    work_places.insert(work_place);

}

void City::teachAtFaculty( int  employee ,  int faculty)
{
    Employee* emp=findEmployee(employee);


    std::set<Faculty<Condition>*>::iterator itr ;
    for (itr = faculties.begin();itr != faculties.end(); itr++){
        if ((*itr)->getId()==faculty){
            ((*itr))->teach(emp);
            return;
        }
    }

    throw FacultyDoesNotExist();
}





void City::hireManagerAtWorkplace( int manager, int workplace)
{
    Manager* man=findManager(manager);
    Workplace* w_place=findWorkPlace(workplace);
    w_place->hireManager(man);
}


void City::fireEmployeeAtWorkplace( int employee, int manager, int workplace)
{
    Employee* emp=findEmployee(employee);
    Manager* man=findManager(manager);
    Workplace* w_place=findWorkPlace(workplace);
    w_place->fireEmployee(man->getId(),emp->getId());
}


void City::fireManagerAtWorkplace( int manager, int workplace)
{
    Manager* man=findManager(manager);
    Workplace* w_place=findWorkPlace(workplace);


    std::set<Employee*>::iterator emp ;
    auto test = man->getEmployeeSet();

    for (emp = test.begin(); emp != test.end(); emp++){
        w_place->fireEmployee(manager,(*emp)->getId());
    }

    w_place->fireManager(man->getId());

}



int City::getAllAboveSalary(std::ostream& os ,int salary) const
{
    int counter=0;
    std::set<Manager*>::iterator man=managers.begin();
    std::set<Employee*>::iterator emp=employees.begin();

    while ((man)!=managers.end() && emp!=employees.end()){
        if ((*man)->getId()<(*emp)->getId()){
            if ((*man)->getSalary()>=salary){
                (*man)->printShort(os);  counter++;
            }
            man++;
        }else{
            if ((*emp)->getSalary()>=salary){
                (*emp)->printShort(os);   counter++;
            }
            emp++;
        }
    }

    while ((man)!=managers.end()){
        if ((*man)->getSalary()>=salary){
            (*man)->printShort(os); counter++;
        }
        man++;
    }

    while ((emp)!=employees.end()){
        if ((*emp)->getSalary()>=salary){
            (*emp)->printShort(os); counter++;
        }
        emp++;
    }

    return counter;
}

/*loop iterating over the managers and using set,contains twice to see if they both are in the set;*/
bool City::isWorkingInTheSameWorkplace( int first ,  int second) const
{
    Employee* emp_1=findEmployee(first);
    Employee* emp_2=findEmployee(second);

    std::set<Workplace*>::iterator w_plc ;
    for (w_plc = work_places.begin(); (*w_plc) != (*(work_places.end())); w_plc++){
        bool exists1 = (*w_plc)->hiredEmployeeInWorkplace(emp_1);
        bool exists2 = (*w_plc)->hiredEmployeeInWorkplace(emp_2);

        if (exists1 && exists2){
            return true;
        }
    }

    return false;
}

void City::printAllEmployeesWithSkill(std::ostream& os ,Skill skill) const
{
    std::set<Employee*>::iterator emp;
    for (emp = employees.begin(); (*emp) != (*(employees.end())); emp++){
        if ((*emp)->hasSkill(skill.getId())==true){
            (*emp)->printShort(os);
        }
    }
}