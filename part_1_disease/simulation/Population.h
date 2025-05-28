#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <set>
#include "Person.h"
#include "Disease.h"
#include <iostream>

class Population {
private:
    std::vector<Person> people;
    std::set<Person*> MonitoredPeople;

public:
    
    Population(int size);
    //for vaccination rate 1.0
    //int random_infection(const Disease& d, int count);
    
    void random_infection(const Disease& d, int count);
    void random_vaccination(int count);
    int count_infected() const;
    int count_vaccinated() const;
    int count_recovered() const;
    int count_susceptible() const;
    void one_more_day();
    void display() const;
    void spread_to_neighbors(const Disease& d);
    void spread_randomly(const Disease& d, int interactions_per_person);
    void MonitorInfectedPeople(Person *p);
    void GetOutOfMointoring(Person *p);

};

#endif // POPULATION_H
