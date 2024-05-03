#ifndef PID_CONTROL_HPP
#define PID_CONTROL_HPP

#include <iostream>
#include "odyssey_status.hpp"

class PIDController {
    private:
        double kp, ki, kd;
        double prev_error, prev_measurement;
        double porportional, integral, derivative;
        double pid_max_output, pid_min_output;
        double pid_output;
    public:
        PIDController(double kp, double ki, double kd) : kp(kp), ki(ki), kd(kd), prev_error(0), integral(0) {}
        OdysseyStatus pid_controller_init(PIDController *pid);
        OdysseyStatus pid_controller_update(PIDController *pid, double set_point, double measurement);
};

#endif
