#include "Population.h"
#include "Person.h"
#include <cstdlib>
#include <iostream>
using namespace std;


Person::Person(Population *pop) : status(SUSCEPTIBLE), daysSick(0), myNation(pop) {}

void Person::infect(const Disease& d) {
    if (status == SUSCEPTIBLE) {
        status = SICK;
        daysSick = d.getDuration(); 
        this -> myNation -> MonitorInfectedPeople(this);
    }
}


void Person::vaccinate() {
    if (status == SUSCEPTIBLE) {
        status = VACCINATED;
    }
}

void Person::one_more_day() {
    if (status == SICK) {
        --daysSick;
        if (daysSick <= 0) {
            status = RECOVERED;
            this -> myNation -> GetOutOfMointoring(this);

            cout << "Number of days remaining: " << daysSick << endl;
        }
    }
}


Status Person::get_status() const {
    return status;
}

void Person::touch(Person& other, const Disease& d) {
    if (status == SICK && other.status == SUSCEPTIBLE) {
        double r = static_cast<double>(std::rand()) / RAND_MAX;
        if (r < d.getInfectivity()) {
            other.infect(d);
        }
    }
    else if(status == SUSCEPTIBLE && other.status == SICK){
        double r = static_cast<double>(std::rand()) / RAND_MAX;
        if (r < d.getInfectivity()) {
            this -> infect(d);
        }
    }
    else{

    }
}

