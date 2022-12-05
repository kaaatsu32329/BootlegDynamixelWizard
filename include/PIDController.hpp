#ifndef PID_HPP
#define PID_HPP

class PIDController
{
public:
    PIDController(double kp, double ki, double kd);
    double calculate(double target, double current);

private:
    double m_kp;
    double m_ki;
    double m_kd;
    double m_latestError;
    double m_integral;
};

#endif /* PID_HPP */
