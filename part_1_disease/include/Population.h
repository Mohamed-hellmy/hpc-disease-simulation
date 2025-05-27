#pragma once
#include "Person.h"
#include <vector>

// Represents a group of people
class Population {
private:
    std::vector<Person> people;

public:
    Population(int numberOfPeople, double vaccinationRate); // create population

    int countSusceptiblePeople() const;
    int countInfectiousPeople() const;
    int countRecoveredPeople() const;
    int countVaccinatedPeople() const;
};





