#ifndef DISEASE_H
#define DISEASE_H

class Disease {
private:
    int duration;
    double infectivity;
public:
    Disease(int dur, double inf);
    int getDuration() const;
    double getInfectivity() const;
};

#endif // DISEASE_H

