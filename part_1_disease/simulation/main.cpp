#include "simulation.h"

int main() {
    Simulation sim("../configExample/disease_in.ini");
    sim.start();
    return 0;
}