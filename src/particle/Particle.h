#pragma once
#include "../magnetic_field/MagneticField.h"
#include <array>

class Particle {
    private:
        double q_;
        double m_;
        std::array<double,3> r_;
        std::array<double,3> v_;
    public:
        Particle(double q = 1.6e-19, double m = 9.11e-31): q_(q), m_(m), r_{0,0,0}, v_{50000,50000,50000} {};
        void setQ(double q) {q_ = q;};
        void setM(double m) {m_ = m;};
        double getQ() const { return q_; };
        double getM() const { return m_; };
        void setPosition(double x, double y, double z) {
            r_[0] = x;
            r_[1] = y;
            r_[2] = z;
        };
        void setVelocity(double vx, double vy, double vz) {
            v_[0] = vx;
            v_[1] = vy;
            v_[2] = vz;
        };
        double get_X() const { return r_[0];};
        double get_Y() const { return r_[1];};
        double get_Z() const { return r_[2];};
        double get_vX() const { return v_[0];};
        double get_vY() const { return v_[1];};
        double get_vZ() const { return v_[2];};
        const std::array<double,3>& position() const { return r_; }
        const std::array<double,3>& velocity() const { return v_; }

};