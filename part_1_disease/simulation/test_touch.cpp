#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Person.h"
#include "Disease.h"
#include "Population.h"

TEST_CASE("Touch with guaranteed infection") {
    Population pop(2);
    Person p1(&pop), p2(&pop);
    Disease d(4, 1.0);

    p1.infect(d);
    p1.touch(p2, d);
    CHECK(p2.get_status() == SICK);
}

TEST_CASE("Touch with zero infection") {
    Population pop(2);
    Person p1(&pop), p2(&pop);
    Disease d(4, 0.0);

    p1.infect(d);
    p1.touch(p2, d);
    CHECK(p2.get_status() == SUSCEPTIBLE);
}