#include "Employee.h"

using namespace mtm;

Employee::Employee( int id ,std::string first_name ,std::string last_name, int birth_year)
        :Citizen(id,first_name,last_name,birth_year),salary(0),score(0),skills(){}



int Employee::getSalary() const{
    return salary;
}

int Employee::getScore() const {
    return score;
}

void Employee::setSalary(int raise){
    salary+=raise;
    if(salary<0){
        salary=0;
    }
}

void Employee::setScore(int score){
    (this->score)+=score;
    if (score<0){
        this->score=0;
    }
}



void Employee::learnSkill(const Skill skill)
{
    if (score<skill.getRequiredPoints()){
        throw CanNotLearnSkill();
    }
    std::pair<std::set<Skill>::iterator,bool> condition;
    condition = skills.insert(skill);//by value.

    if (condition.second==false){
        throw SkillAlreadyLearned();
    }

}


void Employee::forgetSkill(const  int skill)
{

    Skill temp_skill(skill);
    if (skills.count(temp_skill)==false){
        throw  DidNotLearnSkill();
    }

    skills.erase(temp_skill);
}

bool Employee::hasSkill( int skill) const
{
    Skill temp_skill ={skill};
    int exists = skills.count(temp_skill);
//returns one(true) in the case of the skill being learned and zero(false) otherwise
    return exists;
}



std::ostream& Employee::printShort(std::ostream& os) const
{
    os<< first_name << " " << last_name << std::endl;
    os<<"Salary: " << salary << " Score: " << score <<std::endl;
    return os;
}


std::ostream& Employee::printLong(std::ostream& os) const
{
    std::set<Skill>::iterator itr ;
    os<< first_name << " " << last_name << std::endl;
    os<<"id - "<< id << " birth_year - " << birth_year<<std::endl;
    os<<"Salary: " << salary << " Score: " << score;

    if (skills.size()>0){
        os<< " Skills: " <<std::endl;

    }else{
        os<<std::endl;
    }


    for (itr = skills.begin(); itr != skills.end(); itr++) {


        std::string skill_name =(*itr).getName();
        os << skill_name <<std::endl;
    }

    return os;
}


Employee* Employee::clone() const
{
    Employee* clone_emp = static_cast<Employee*>(new Employee(*this));
    clone_emp->salary=this->salary;

    clone_emp->skills=skills;//the = operator of std::set will do the work
    return clone_emp;
}