#pragma once

// Possible health states of a person
enum class HealthState { Susceptible, Infectious, Recovered, Vaccinated };

class Person {
private:
    HealthState healthState; // current health status

public:
    Person(HealthState initialState);            // initialize with a state
    HealthState getHealthState() const;          // return current state
    void setHealthState(HealthState newState);   // update to new state
};



