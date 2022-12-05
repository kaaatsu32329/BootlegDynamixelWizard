#include "PIDController.hpp"

PIDController::PIDController(double kp, double ki, double kd)
    : m_kp(kp), m_ki(ki), m_kd(kd), m_latestError(0), m_integral(0)
{
}

double PIDController::calculate(double target, double current)
{
    double error = target - current;
    m_integral += error;

    double derivative = error - m_latestError;
    double output = m_kp * error + m_ki * m_integral + m_kd * derivative;

    m_latestError = error;

    return output;
}
