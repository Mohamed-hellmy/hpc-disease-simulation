cmake_minimum_required(VERSION 3.10)
project(DiseaseSimulation)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(simulation)

file(GLOB SIM_SRC
    "simulation/main.cpp"
    "simulation/simulation.cpp"
    "simulation/Disease.cpp"
    "simulation/Person.cpp"
    "simulation/Population.cpp"
)

add_executable(main_exec ${SIM_SRC})

add_executable(test_person
    simulation/test_person.cpp
    simulation/Person.cpp
    simulation/Disease.cpp
    simulation/Population.cpp
)

add_executable(test_population
    simulation/test_population.cpp
    simulation/Population.cpp
    simulation/Person.cpp
    simulation/Disease.cpp
)

add_executable(test_touch
    simulation/test_touch.cpp
    simulation/Person.cpp
    simulation/Disease.cpp
    simulation/Population.cpp
)

add_executable(test_disease
    simulation/test_disease.cpp
    simulation/Disease.cpp
)

add_executable(test simulation/test.cpp
simulation/Person.cpp
simulation/Population.cpp
simulation/Disease.cpp
simulation/simulation.cpp
)
