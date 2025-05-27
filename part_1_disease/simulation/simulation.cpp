#include "simulation.h"
#include "INIReader.h"
#include "Disease.h"
#include "Population.h"
#include <iostream>
#include <fstream>
#include <filesystem>

Simulation::Simulation(const std::string& filename)
    : input_file(filename) {}

void Simulation::start() {
    INIReader reader(input_file);

    if (reader.ParseError() != 0) {
        std::cerr << "Can't load INI file: " << input_file << std::endl;
        return;
    }

    std::string disease_name = reader.Get("disease", "name", "unknown");
    int duration = reader.GetInteger("disease", "duration", 4);
    double transmissibility = reader.GetReal("disease", "transmissibility", 0.2);

    int size = reader.GetInteger("population_1", "size", 100);
    double vaccination_rate = reader.GetReal("population_1", "vaccination_rate", 0.0);
    bool patient_zero = reader.GetBoolean("population_1", "patient_0", false);

    int simulation_runs = reader.GetInteger("global", "simulation_runs", 1);
    std::string city_name = reader.Get("population_1", "name", "City");

    
    std::filesystem::create_directory("../report_data");

    
    std::ofstream csv("../report_data/disease_details.csv");
    csv << "run,day,name,infectious,recovered,susceptiple,vaccinated\n";

    std::ofstream summary("../report_data/disease_stats.csv");
    summary << "key,value\n";

    std::cout << "Simulation: " << disease_name << std::endl;
    std::cout << "City: " << city_name << std::endl;

    for (int run = 1; run <= simulation_runs; ++run) {
        std::cout << "\nRun " << run << ":" << std::endl;

        Disease disease(duration, transmissibility);
        Population pop(size);
        pop.random_vaccination(size * vaccination_rate);
        if (patient_zero) pop.random_infection(disease, 1);

        int total_steps = 0;

        while (true) {
            ++total_steps;
            int infected = pop.count_infected();
            int recovered = pop.count_recovered();
            int vaccinated = pop.count_vaccinated();
            int susceptible = pop.count_susceptible();

            std::cout << "Day " << total_steps << ":\n";
            std::cout << "  Infected:    " << infected << std::endl;
            std::cout << "  Recovered:   " << recovered << std::endl;
            std::cout << "  Vaccinated:  " << vaccinated << std::endl;
            std::cout << "  Susceptible: " << susceptible << std::endl;

            csv << run << "," << total_steps << "," << city_name << ","
                << infected << "," << recovered << ","
                << susceptible << "," << vaccinated << "\n";

            pop.spread_randomly(disease, 6);
            pop.one_more_day();

            if (pop.count_infected() == 0) {
                std::cout << "No more infected people" << std::endl;
                csv << run << "," << total_steps << "," << city_name << ","
                    << pop.count_infected() << "," << pop.count_recovered() << ","
                    << pop.count_susceptible() << "," << pop.count_vaccinated() << "\n";
                break;
            }
        }

        int final_recovered = pop.count_recovered();
        int final_vaccinated = pop.count_vaccinated();
        int final_susceptible = pop.count_susceptible();

        summary << "total_steps," << total_steps << "\n";
        summary << "susceptiple_persons," << final_susceptible << "\n";
        summary << "recovered_persons," << final_recovered << "\n";
        summary << "vaccinated_persons," << final_vaccinated << "\n";

        std::cout << "Simulation finished." << std::endl;
    }

    csv.close();
    summary.close();

    std::cout << "Results saved to report_data/disease_details.csv and report_data/disease_stats.csv" << std::endl;
}