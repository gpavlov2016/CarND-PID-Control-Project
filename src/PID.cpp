#include "PID.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Kd = Kd;
    this->Ki = Ki;
    p_error = 0;
    i_error = 0;
    d_error = 0;
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error; 
    p_error = cte;
    i_error += cte;
}

double PID::TotalError() {
	return i_error;
}

