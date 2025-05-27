#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

class Simulation {
private:
    std::string input_file;

public:
    Simulation(const std::string& filename); 
    void start();                            
};

#endif
