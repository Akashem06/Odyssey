#include "pid_control.hpp"

OdysseyStatus PIDController::pid_controller_init(PIDController *pid) {
    pid->integral = 0;
    pid->prev_error = 0;
    pid->prev_measurement = 0;
    pid->pid_output = 0;

    return ODYSSEY_OK;
};

OdysseyStatus PIDController::pid_controller_update(PIDController *pid, double set_point, double measurement) {
    // Porpotional Control
    pid->porportional = pid->kp * (set_point - measurement)

    // Integral Control
    pid->integral = 
}