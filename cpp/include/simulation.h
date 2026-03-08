#include "oscillator.h"
#include <vector>
#include <string>

using namespace std;

class simulation{
    private:
        double x_min, x_max, y_min, y_max;
        int N;
        vector<oscillator*> Osc;
        double J;
        double dt;
        int next_ID;
    public:
        //constructor
        simulation(int, int, int, int, float, int, double, double, double, double, double, double);
        ~simulation();
        //other functions
        float CalculatePulse();
        void step();
        void writetofile_binary(string, bool);
        void writetofile(string, bool);
        vector<oscillator*> getOsc(){return Osc;};
};
