#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Person.h"
#include "Disease.h"
#include "Population.h"

TEST_CASE("Person infection and recovery") {
    Population pop(1);
    Person p(&pop);
    Disease d(4, 1.0);

    CHECK(p.get_status() == SUSCEPTIBLE);
    p.infect(d);
    CHECK(p.get_status() == SICK);

    for (int i = 0; i < 4; ++i)
        p.one_more_day();

    CHECK(p.get_status() == RECOVERED);
}

TEST_CASE("Person vaccination") {
    Population pop(1);
    Person p(&pop);

    p.vaccinate();
    CHECK(p.get_status() == VACCINATED);
}