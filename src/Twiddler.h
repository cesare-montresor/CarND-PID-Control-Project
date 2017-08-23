//
//  Twiddler.hpp
//  PIDController
//
//  Created by Cesare on 21/08/2017.
//
//

#ifndef TWIDDLER_H
#define TWIDDLER_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

#define PARAMS_FILE "../../../params.txt"

class Twiddler {
  unsigned index_;
  unsigned state_;
  double reset_thresh_;
  
  public:
    vector<double> p;
    vector<double> dp;
    double max_iterations_;
    double best_err_;
    double inc;
    double dec;
  
    Twiddler();
    void Twiddle(const double err);
  
    bool load();
    bool save();
    void reset();
};



#endif /* TWIDDLER_H */
