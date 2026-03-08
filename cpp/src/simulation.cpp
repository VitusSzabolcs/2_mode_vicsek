#include "simulation.h"
#include <random>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

simulation::simulation(int tau, int timeB1, int timeB2, int timeC, float fstar, int N_, double x_min, double x_max, double y_min, double y_max, double dt_, double J_){
    next_ID = 1;
    default_random_engine generator; // random number generator
    exponential_distribution<double> distribution(1.0/tau);
    this->x_min = x_min;
    this->x_max = x_max;
    this->y_min = y_min;
    this->y_max = y_max;
    N = N_;
    dt = dt_;
    for(int i = 0; i < N; i++){
        double timeA = distribution(generator);
        double x = (double)rand()/(RAND_MAX + 1.0) * (x_max - x_min) + x_min;
        double y = (double)rand()/(RAND_MAX + 1.0) * (y_max - y_min) + y_min;
        Osc.push_back(new oscillator(next_ID, x, y, timeA, timeB1, timeB2, timeC, 1.0/N, fstar, dt_));
        next_ID++;
    }
    J = J_;
  }
  
  float simulation::CalculatePulse(){ // calculates all the emitted pulse 
    float Pulse = 0;
    vector<oscillator*>::iterator it;
    for(it = Osc.begin(); it < Osc.end(); it++)
    {
      Pulse += (*it)->getOutputPulse();
    } 
    return Pulse;
  }
  
  void simulation::step(){ 
    random_shuffle(Osc.begin(), Osc.end());
    vector<oscillator*>::iterator it;
    for(it = Osc.begin(); it < Osc.end(); it++)
    {
      (*it)->increaseTimer(Osc);
    } 

  }
  
  void simulation::writetofile_binary(string filename, bool first){ // writes the coordinates and the Pulse variable into a file
    vector<oscillator*>::iterator it;
    if(first){
      fstream g(filename, ios::out | ios::binary);
      g.write(reinterpret_cast<const char *>(&N), sizeof(N));
      g.close();
    }
    fstream g(filename, ios::out | ios::app | ios::binary);
    for(it = Osc.begin(); it < Osc.end();it++){
        double X = (*it)->getX();
        double Y = (*it)->getY();
        double Pulse = (*it)->getOutputPulse() == 0 ? 0.0 : 1.0;
        g.write(reinterpret_cast<const char *>(&X), sizeof(X));
        g.write(reinterpret_cast<const char *>(&Y), sizeof(Y));
        g.write(reinterpret_cast<const char *>(&Pulse), sizeof(Pulse));
    }
    g.close();
  }
  
  void simulation::writetofile(string filename, bool first){
    vector<oscillator*>::iterator it;
    if(first){
      ofstream g;
      g.open(filename);
      g<<N<<" "<<"1"<<endl;
      g.close();
    }
    ofstream g(filename, ios::app);
    for(it = Osc.begin(); it < Osc.end();it++){
      double X = (*it)->getX();
      double Y = (*it)->getY();
      double Pulse = (*it)->getOutputPulse() == 0 ? 0 : 1;
      double Faze = (*it)->getFaze();
      double ID = (*it)->getID();
      g<<ID<<" "<<X<<" "<<Y<<" "<<Pulse<<" "<<Faze<<endl;
    }
    g.close();
  }