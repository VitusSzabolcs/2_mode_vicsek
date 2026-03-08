//
//  main.cpp
//  swarmalators2mode
//

#include "simulation.h"
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
  srand(time(NULL));

  int T = 1000;

  int tau = 1.0;
  int tauB1 = 4.0;
  int tauB2 = 8.0;
  int tauC = 1.0;
  double dt = 0.1;

  float fstar[4] = {-1.0, 0.1, 0.2, 1.0};

  int N = 100;

  int x_min = -1.5;
  int x_max = 1.5;
  int y_min = -1.5;
  int y_max = 1.5;

  double J = 0.1;

  simulation **sims = new simulation*[4];


  for(int i = 0; i < 4; i++){
    sims[i] = new simulation(tau, tauB1, tauB2, tauC, fstar[i], N, x_min, x_max, y_min, y_max, dt, J);
  }

  ofstream g;

  g.open("output/main_output.txt");

  float Pulse[4];

  for(float t = 0; t<T; t+=dt){
    cout<<t<<endl;
    for(int i = 0; i < 4; i++){
        sims[i]->step();
    }
    for(int i = 0; i < 4; i++){
        Pulse[i] = sims[i]->CalculatePulse();
    }

    g<<t<<" "<<Pulse[0]<<" "<<Pulse[1]<<" "<<Pulse[2]<<" "<<Pulse[3]<<endl;
  }
  g.close();
  
  return 0;
}
