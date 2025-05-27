#include "Person.h"
#include "Population.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


Population::Population(int size)
    : people(size, Person(this)) {
    std::srand(std::time(nullptr));
}


void Population::random_infection(const Disease& d, int count) {
    int infected = 0;
    int size = people.size();

    while (infected < count) {
        int index = std::rand() % size;
        if (people[index].get_status() == SUSCEPTIBLE) {
            people[index].infect(d);
            ++infected;
        }
    }
}


void Population::random_vaccination(int count) {
    int vaccinated = 0;
    int size = people.size();

    while (vaccinated < count) {
        int index = std::rand() % size;
        if (people[index].get_status() == SUSCEPTIBLE) {
            people[index].vaccinate();
            ++vaccinated;
        }
    }
}


int Population::count_infected() const {
    int count = 0;
    for (const Person& p : people) {
        if (p.get_status() == SICK) {
            ++count;
        }
    }
    return count;
}


int Population::count_vaccinated() const {
    int count = 0;
    for (const Person& p : people) {
        if (p.get_status() == VACCINATED) {
            ++count;
        }
    }
    return count;
}


int Population::count_recovered() const {
    int count = 0;
    for (const Person& p : people) {
        if (p.get_status() == RECOVERED) {
            ++count;
        }
    }
    return count;
}


int Population::count_susceptible() const {
    int count = 0;
    for (const Person& p : people) {
        if (p.get_status() == SUSCEPTIBLE) {
            ++count;
        }
    }
    return count;
}


void Population::one_more_day() {
    for (Person& p : people) {
        p.one_more_day();
    }
}


void Population::display() const {
    std::cout << "Currently infected: " << count_infected() << std::endl;
}


void Population::spread_to_neighbors(const Disease& d) {
    for (size_t i = 0; i + 1 < people.size(); ++i) {
        people[i].touch(people[i + 1], d);
        people[i + 1].touch(people[i], d);
    }
}


void Population::spread_randomly(const Disease& d, int interactions_per_person) {
    int size = people.size();

    if(this -> count_infected()){
        
        for (Person* p : MonitoredPeople) {
            if (p != nullptr) {
                for (int j = 0; j < interactions_per_person; ++j) {
                    int random_index = std::rand() % size;
                    p -> touch(people[random_index], d);
                }
            }
        }


    }
}

void Population::MonitorInfectedPeople(Person *p){

    MonitoredPeople.insert(p);

}

void Population::GetOutOfMointoring(Person *p){

    MonitoredPeople.erase(p);

}