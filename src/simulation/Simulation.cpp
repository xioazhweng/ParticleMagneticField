#include "Simulation.h"
#include <cmath>


Simulation::Simulation() 
    : particle_(), B_(), paused_(false), showTrail_(true), timeScale_(1e-12) {};

void Simulation::step(double dt)
{
    if (paused_)
        return;

    dt *= timeScale_;

    auto r = particle_.position();
    auto v = particle_.velocity();
    double q = particle_.getQ();
    double m = particle_.getM();
    auto B = B_.getB();
    double q_over_m = q / m;
    

    // поворот скорости магнитным полем (метод Бориса)
    // Вычисляем вектор t = (q*B*dt)/(2m)
    double t_magnitude = q_over_m * dt * 0.5;
    std::array<double, 3> t = {
        B[0] * t_magnitude,
        B[1] * t_magnitude,
        B[2] * t_magnitude
    };
    
    // t² = t·t
    double t2 = t[0]*t[0] + t[1]*t[1] + t[2]*t[2];
    
    // v' = v + v × t
    std::array<double, 3> v_prime = {
        v[0] + (v[1]*t[2] - v[2]*t[1]),
        v[1] + (v[2]*t[0] - v[0]*t[2]),
        v[2] + (v[0]*t[1] - v[1]*t[0])
    };
    
    // s = 2t/(1 + t²)
    double factor = 2.0 / (1.0 + t2);
    std::array<double, 3> s = {
        t[0] * factor,
        t[1] * factor,
        t[2] * factor
    };
    
    // v_plus = v + v' × s
    std::array<double, 3> v_plus = {
        v[0] + (v_prime[1]*s[2] - v_prime[2]*s[1]),
        v[1] + (v_prime[2]*s[0] - v_prime[0]*s[2]),
        v[2] + (v_prime[0]*s[1] - v_prime[1]*s[0])
    };
    
    double vx_new = v_plus[0];
    double vy_new = v_plus[1];
    double vz_new = v_plus[2];
    
    double rx_new = r[0] + 0.5 * (v[0] + vx_new) * dt;
    double ry_new = r[1] + 0.5 * (v[1] + vy_new) * dt;
    double rz_new = r[2] + 0.5 * (v[2] + vz_new) * dt;
    
    //double v_old_mag = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    //double v_new_mag = sqrt(vx_new*vx_new + vy_new*vy_new + vz_new*vz_new);
    
    particle_.setPosition(rx_new, ry_new, rz_new);
    particle_.setVelocity(vx_new, vy_new, vz_new);
    if (showTrail_) {
        trajectory_.push_back({rx_new, ry_new, rz_new});
        const size_t MAX_TRAIL = 500;
        if (trajectory_.size() > MAX_TRAIL) {
            trajectory_.pop_front();
        }
    }
}

void Simulation::reset() {
    particle_ = Particle();
    trajectory_.clear();
}