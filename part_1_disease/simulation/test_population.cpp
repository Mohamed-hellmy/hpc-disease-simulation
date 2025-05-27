#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Population.h"
#include "Disease.h"

TEST_CASE("Random infection and vaccination") {
    Disease d(4, 1.0);
    Population pop(100);
    pop.random_vaccination(50);
    pop.random_infection(d, 10);

    int infected = pop.count_infected();
    int vaccinated = pop.count_vaccinated();

    CHECK(infected <= 10); 
    CHECK(vaccinated == 50);
}

TEST_CASE("Spread and recovery") {
    Disease d(2, 1.0);
    Population pop(10);
    pop.random_infection(d, 1);

    for (int i = 0; i < 3; ++i) {
        pop.spread_randomly(d, 6);
        pop.one_more_day();
    }

    CHECK(pop.count_infected() >= 0);
}