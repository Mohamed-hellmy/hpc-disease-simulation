#ifndef PERSON_H
#define PERSON_H

#include "Disease.h"


enum Status { SUSCEPTIBLE, SICK, RECOVERED, VACCINATED };

class Population;

class Person {
private:
    Status status;
    int daysSick;
    Population *myNation;

public:
    Person(Population *p);
    void infect(const Disease& d);
    void vaccinate();
    void one_more_day();
    Status get_status() const;
    void touch(Person& other, const Disease& d);
};

#endif 
