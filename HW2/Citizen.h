#ifndef CITIZEN_H_
#define CITIZEN_H_
#include <iostream>
#include <string>

namespace mtm{//including the h file inside the name space

    class Citizen
    {
    protected://protected so  derived classes can have access to those filed,mainly for printing
        int id;
        std::string first_name;
        std::string last_name;
        int birth_year;

    public:
//constructors and destructors
        Citizen( int id ,std::string first_name ,std::string last_name, int birth_year);
        virtual ~Citizen()=default;
        Citizen(const Citizen&) =default;

//methods for acquiring basic information of a certain Citizen
        int getId() const ;
        int getBirthYear() const ;
        std::string getFirstName() const ;
        std::string getLastName() const ;
        virtual int getSalary() const=0;

//abstract methods to print a description of a certain Citizen,implemented for employee and manager
        virtual std::ostream& printShort(std::ostream& os) const=0  ;
        virtual std::ostream&  printLong(std::ostream& os) const=0  ;

//overloaded operators for comparing citizen based on id,works for employees and managers
        friend bool operator<(const Citizen&, const Citizen&);
        friend bool operator==(const Citizen&, const Citizen&);

//abstract method for cloning a Citizen (manager/employee) and returning a pointer to the created class
//creates a new copy of said Citizen and returns a pointer to it
        virtual Citizen* clone() const=0;
    };

//overloaded operators for comparing between Citizens based on id
    bool operator>(const Citizen& first , const Citizen& second );
    bool operator<=(const Citizen&, const Citizen&);
    bool operator>=(const Citizen&, const Citizen&);
    bool operator!=(const Citizen&, const Citizen&);


    inline bool operator<(const Citizen& first, const Citizen& second){
        return (first.id<second.id);
    }


    inline bool operator==(const Citizen& first, const Citizen& second){
        return (first.id==second.id);
    }

    struct setElementsCompare
    {
        bool operator()(const Citizen* first ,const Citizen* second){
            return first->getId()<second->getId();
        }

    };


}
#endif 