#include "PID.h"





PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  Kp_ = Kp;
  Ki_ = Ki;
  Kd_ = Kd;
  
  prev_cte_ = 0;
  total_cte_ = 0;
  iterations_ = 0;
  max_iterations_ = 200;
  safe_iterations_ = max_iterations_/2;
  total_error_ = 0;
  
  firstRun = true;
  
  cout<<"Init: p: "<<Kp_<<" | i: "<<Ki_<<" | d: "<<Kd_<<"\n";
  
}

double PID::Update(double cte) {
  if (firstRun){ // prev_cte_ == 0 was probably good enough
    prev_cte_ = cte;
    firstRun = false;
  }
  
  const double diff_cte = (cte - prev_cte_);
  total_cte_ += cte;
  prev_cte_ = cte;
  
  
  const double result = -Kp_ * cte - Kd_ * diff_cte - Ki_ * total_cte_;
  
  if ( iterations_ > safe_iterations_ ){
    total_error_ += cte * cte;
  }
  
  iterations_++;
  
  return result;
}


bool PID::isEvaluable(){
  return iterations_ >= max_iterations_;
}

double PID::Error() {
  return total_error_/iterations_;
}




