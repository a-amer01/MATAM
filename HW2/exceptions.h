#ifndef HW2_EXCEPTIONS_H
#define HW2_EXCEPTIONS_H
#include <exception>

namespace mtm{

    class Exception: public std::exception{};
    class NegativePoints: public Exception{};
    class SkillAlreadyLearned: public Exception{};
    class CanNotLearnSkill: public Exception{};
    class DidNotLearnSkill: public Exception{};
    class EmployeeAlreadyHired: public Exception {};
    class EmployeeNotHired: public Exception {};
    class EmployeeNotSelected: public Exception {};
    class EmployeeIsNotHired: public Exception {};
    class ManagerIsNotHired: public Exception {};
    class ManagerAlreadyHired: public Exception {};
    class CanNotHireManager: public Exception {};
    class EmployeeNotAccepted: public Exception {};
    class FacultyAlreadyExists: public Exception {};
    class WorkplaceAlreadyExists: public Exception {};
    class FacultyDoesNotExist: public Exception{};
    class ManagerDoesNotExist: public Exception {};
    class WorkplaceDoesNotExist: public Exception {};
    class EmployeeAlreadyExists: public Exception{};
    class ManagerAlreadyExists: public Exception{};
    class EmployeeDoesNotExist: public  Exception{};
    class CitizenAlreadyExists: public Exception{};
}


#endif //HW2_EXCEPTIONS_H