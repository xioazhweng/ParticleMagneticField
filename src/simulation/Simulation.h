#pragma once
#include "../particle/Particle.h"
#include "../magnetic_field/MagneticField.h"
#include <vector>
#include <deque>

class Simulation {
    private:
        Particle particle_;
        MagneticField B_;
        std::deque<std::array<double, 3>> trajectory_;
        bool paused_;
        bool showTrail_;
        double timeScale_;
    public:
        Simulation();
        void step(double dt);
        void pause() { paused_ = true; };
        void resume() { paused_ = false; };
        void reset();
        void set_time_scale(double scale) {timeScale_ = scale;};
        void add_trajectory_point();
        void update_particle_q(double q) {particle_.setQ(q);};
        void update_particle_m(double m) {particle_.setM(m);};
        void update_particle_v(double x, double y, double z) {
            particle_.setVelocity(x, y, z);};
        void reset_trajevtory() {trajectory_.clear();};
        void update_particle_r(double vx, double vy, double vz) {
            particle_.setPosition(vx, vy, vz);};
        void update_B(double x, double y, double z) {B_.setB(x, y, z);};
        double getX(void) const {return particle_.get_X();}; 
        double getY(void) const {return particle_.get_Y();};
        double getZ(void) const {return particle_.get_Z();};
        const std::deque<std::array<double, 3>> & get_trajectory() const {return trajectory_;};

};