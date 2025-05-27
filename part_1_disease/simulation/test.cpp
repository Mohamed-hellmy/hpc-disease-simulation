#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "simulation.h"

TEST_CASE("Test simulation class") {
    Simulation sim("../configExample/disease_in.ini");
    sim.start();  
}
