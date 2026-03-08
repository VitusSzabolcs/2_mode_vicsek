#include "oscillator.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <numbers>

using namespace std;

oscillator::oscillator(int id_, double x_, double y_, double ta_, double tb1_, double tb2_, double tc_, float pulse_, float fstar_, double dt_){
    ID = id_;
    X     = x_;
    Y     = y_;
    TA    = ta_;
    TB    = new double[2];
    TB[0] = tb1_;
    TB[1] = tb2_;
    TC    = tc_;
    Fstar = fstar_;
    Mode  = 1;
    Timer = rand()/(RAND_MAX+1.0) * (ta_ + tb2_ + tc_);
    Pulse = pulse_;
    OutputPulse = Timer>TA+TB[Mode] ? Pulse : 0.0;
    dt = dt_;
    faze = Timer / (ta_ + tb2_ + tc_) * std::numbers::pi;
    v_x = 0;
    v_y = 0;
  }
  
oscillator::~oscillator() {
    // delete if TB array existed
    if(TB != nullptr){
        delete TB;
    }
}
  
void oscillator::setTB(double *tb_) {
    // delete if TB array existed
    if(TB != nullptr){
        delete TB;
    }
    TB = tb_;
}
  
void oscillator::setTB(int tb1_, int tb2_) {
    // delete if TB array existed
    if(TB != nullptr){
        delete TB;
    }
    // create new TB array
    TB = new double[2];
    TB[0] = tb1_;
    TB[1] = tb2_;
}
  
void oscillator::increaseTimer(vector<oscillator*> Osc){ //returns true if the averageValue needs to be calculated again
    int T = TA+TB[Mode]+TC;
    Timer += dt;
    Timer = Timer > T ? 0 : Timer; // if Timer > T set to 0, else Timer remains
    faze = Timer / T * 2 * std::numbers::pi;
  
    double Pulse = 0;
  
    vector<oscillator*>::iterator it;
    for(it = Osc.begin(); it < Osc.end(); it++){
        if(this != (*it)){
            //double x_diff = (*it)->getX() - X;
            //double y_diff = (*it)->getY() - Y;
            //double distance_squared = pow(x_diff, 2)+pow(y_diff, 2);
            double distance_squared = 1;
            Pulse += (*it)->getOutputPulse()/sqrt(distance_squared); // 1/r dependence of the pulse 
        }
    }
  
    if(Timer > TA && Timer < TA + dt) Mode  = Pulse < Fstar ? 0 : 1; // the oscillator decides his mode
      // at moment TA the Mode is decided: 0 or 1
    OutputPulse = Timer>TA+TB[Mode] ? this->Pulse : 0.0; // if Timer is in TC phase, the oscillator emits pulse
  
}
  
string oscillator::toString() {
    return "OSCILLATOR:  X=" + to_string(X) + " Y="+to_string(Y) + "\nTA=" + to_string(TA) + " TB1=" + to_string(TB[0]) + " TB2=" + to_string(TB[1]) + " TC=" + to_string(TC) + "\nMode=" + to_string(Mode) + " Fstar=" + to_string(Fstar) + " Timer=" + to_string(Timer) + " Pulse=" + to_string(Pulse) + " OutputPulse=" + to_string(OutputPulse) + "\n";
}