#include "Disease.h"

Disease::Disease(int dur, double inf) : duration(dur), infectivity(inf) {}

int Disease::getDuration() const { return duration; }

double Disease::getInfectivity() const { return infectivity; }
