#include "pid_control.hpp"

PIDController::PIDController(double kp, double ki, double kd, double pid_max_output, double pid_min_output) {
    kp = kp;
    ki = ki;
    kd = kd;

    pid_max_output = pid_max_output;
    pid_min_output = pid_min_output;

    prev_error = 0;
    prev_measurement = 0;
    porportional = 0;
    integral = 0;
    derivative = 0;
    pid_output = 0;
}

OdysseyStatus PIDController::pid_controller_init(PIDController *pid) {
    pid->integral = 0;
    pid->prev_error = 0;
    pid->prev_measurement = 0;
    pid->pid_output = 0;

    return ODYSSEY_OK;
};

OdysseyStatus PIDController::pid_controller_update(PIDController *pid, double set_point, double measurement) {
    // Porpotional Control
    pid->porportional = pid->kp * (set_point - measurement);

    // Integral Control
    return ODYSSEY_OK;
}