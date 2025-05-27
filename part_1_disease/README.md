# Infectious Disease Simulation

This project simulates the spread of an infectious disease through a population over time, using simple C++ classes and configuration files.

## 🗂 Project Structure

```
project-root/
├── build/                    
│   └── ...                  
├── configExample/
│   └── disease_in.ini       
├── examples/
│   ├── deterministic/
│   │   └── disease_in.ini
│   └── single_population/
│       └── disease_in.ini
├── include/
│   ├── doctest.h            
│   └── INIReader.h          
├── report_data/
│   ├── disease_details.csv  
│   ├── disease_stats.csv    
│   └── final_plot.png        
├── simulation/
│   ├── Disease.cpp / .h
│   ├── Person.cpp / .h
│   ├── Population.cpp / .h
│   ├── simulation.cpp / .h
│   ├── main.cpp
│   ├── test.cpp
│   ├── test_disease.cpp
│   ├── test_person.cpp
│   ├── test_population.cpp
│   └── test_touch.cpp
├── CMakeLists.txt          
├── plot_simulation.py       
└── README.md               
```

## 🧪 How to Run the Simulation

### 1. Compile the Project
```bash
cd part_1_disease
mkdir build
cd build
cmake ..
make
```

### 2. Run the Simulation
```bash
./main_exec
```
> This will use the `disease_in.ini` file inside the `configExample` folder.

### 3. Check the Output
- `report_data/disease_details.csv`: detailed daily stats for each simulation run
- `report_data/disease_stats.csv`: summary stats for each simulation run

## 📊 Generate the Graph

Make sure Python 3 is installed, then install required libraries:
```bash
pip3 install matplotlib pandas
```

Then run:
```bash
python3 plot_simulation.py
```

This will generate a figure like the one shown below.

## 🖼️ Example Output

![Simulation Plot](report_data/final_plot.png)

## ⚙️ Parameters Used
- Duration (D): 4
- Contacts per day (C): 6
- Transmission Probability (β): 0.2
- Vaccination rate: 0.9
- Population size: 4000

## 👨‍💻 Author  
*Mohamed Mahmoud Helmy Mohamed Hamed Mohamed*  
Email: mohamed.mohamed2@stud.th-deg.de  
Marticulation Nummber: 12503239
