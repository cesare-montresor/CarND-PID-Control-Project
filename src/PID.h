

#ifndef PID_H
#define PID_H

#include <stdio.h>
#include <iostream>



using namespace std;


class PID {
public:
  double previous_time;
  bool firstRun = true;

  double iterations_;
  double safe_iterations_;
  double total_error_;
  double prev_cte_;
  double total_cte_;
  double max_iterations_;
  
  /*
  * Coefficients
  */ 
  double Kp_;
  double Ki_;
  double Kd_;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  double Update(double cte);

  /*
   * Calculate the total PID error.
   */
  double Error();
  
  bool isEvaluable();
  
};

#endif /* PID_H */
