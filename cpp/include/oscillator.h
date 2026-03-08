#include <string>
#include <vector>
#include <iostream>

using namespace std;

class oscillator{
    private:
      int ID; // the unique id of the oscillator
      double X, Y; // coordinates of the oscillator
      int Mode; // 0 if the oscillator is in slow mode, 1 if the oscillator is in fast mode ...
      float Timer; // describes the current phase the oscillator is
      float Pulse; // the default emitted pulse intensity
      float OutputPulse; // the emitted pulse: 0 or Pulse depending on Timer
      float Fstar; // the desired intensity at which mode changes
      double TA; // the length of the first phase (A)
      double *TB; // the lengths of the second phases in an array
      double TC; // the length of the pulse emitting phase (C)
      double dt;// the timestep
      double faze; // the current faze
      double v_x, v_y; // the current velocity
  
    public:
      //constructor
      oscillator(int, double, double, double, double, double, double, float, float, double);
      // standard get and set methods
      double getX(){ return X; }
      void setX(double x_){ X = x_;};
      double getY(){ return Y; };
      void setY(double y_){ Y = y_; };
      int getMode(){ return Mode; };
      void setMode(int mode_){ Mode=mode_; };
      int getTimer(){ return Timer; };
      void setTimer(int t_){ Timer=t_; };
      float getFstar(){ return Fstar; };
      void setFstar(float fstar_){ Fstar = fstar_; };
      float getPulse(){ return Pulse; };
      void setPulse(float pulse_) { Pulse = pulse_; };
      int getTA(){ return TA; }
      void setTA(int ta_){ TA = ta_; };
      double* getTB(){ return TB; }
      int getTC(){ return TC;}
      void setTC(int tc_){ TC = tc_; };
      float getOutputPulse(){ return OutputPulse; };
      double getFaze(){return faze; };
      int getID(){return ID;};
      
      // custom methods
      void setXY(double, double);
      void setTB(double*);
      void setTB(int, int);
      void increaseTimer(vector<oscillator*>);
      
      // print the object
      string toString();
      
      // destructor
      ~oscillator();
  };