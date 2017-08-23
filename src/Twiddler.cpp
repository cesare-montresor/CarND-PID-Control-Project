//
//  Twiddler.cpp
//  PIDController
//
//  Created by Cesare on 21/08/2017.
//
//

#include "Twiddler.h"


Twiddler::Twiddler() {
  if (!load()){
    p = {0,0,0}; //udacity defaults
    dp = {1,1,1};
  }
  
  inc = 1.1;
  dec = 0.9;
  
  index_ = 0;
  state_ = 0;
  best_err_ = __FLT_MAX__;
  reset_thresh_ = 0.00001;
  save();
}


void Twiddler::Twiddle(const double err){
  if (dp[0]+dp[1]+dp[2]<reset_thresh_){
    reset();
  }
  
  if (state_ == 0){
    cout<<"T: UP"<<"\n";
    p[index_] += dp[index_];
    state_ = 1;
    return;
  }
  
  if (state_ == 1){
    if (err < best_err_){
      cout<<"T: UP: success"<<"\n";
      best_err_ = err;
      dp[index_] *= inc;
      //index_ = (index_ + 1) % dp.size();
      state_ = 0;
      save();
    }else{
      cout<<"T: DOWN"<<"\n";
      p[index_] -= 2 * dp[index_];
      state_ = 2;
      return;
    }
  }
  
  if (state_ == 2){
    if (err < best_err_){
      cout<<"T: DOWN: success"<<"\n";
      best_err_ = err;
      dp[index_] *= -inc; //invert direction and increase
    }else{
      cout<<"State: RESTRICT!"<<"\n";
      p[index_] += dp[index_];
      dp[index_] *= dec;
      index_ = (index_ + 1) % dp.size();
    }
    save();
    
    state_ = 0;
  }
}

bool Twiddler::load(){
  
  ifstream file (PARAMS_FILE, ifstream::in); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
  string value;
  if ( !(bool)file ){
    return false;
  }
  unsigned cnt = 0;
  while ( file.good() && cnt<6 )
  {
    getline ( file, value ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
    double val = stof(value);
    
    if (cnt < 3){
      p.push_back(val);
    }else{
      dp.push_back(val);
    }
    cnt++;
  }
  file.close();
  
  return true;
}

bool Twiddler::save(){
  ofstream file (PARAMS_FILE, ifstream::out); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
  file<<p[0]<<"\n"<<p[1]<<"\n"<<p[2]<<"\n";
  file<<dp[0]<<"\n"<<dp[1]<<"\n"<<dp[2];
  file.close();
  return true;
}


void Twiddler::reset(){
  cout<<"Resetting!";
  best_err_ = __FLT_MAX__;
  dp[0] = p[0]/2;
  dp[1] = p[1]/2;
  dp[2] = p[2]/2;
  
  index_ = 0;
  state_ = 0;
}
