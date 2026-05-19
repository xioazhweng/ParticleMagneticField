#pragma once
#include <array>


class MagneticField {
    private:
         std::array<double,3> B_;
    public:
        MagneticField(double Bx = 0.0, double By = 0.0, double Bz = 0.5): B_{Bx, By, Bz} {};
        void setBx(double Bx) {B_[0] = Bx;};
        void setBy(double By) {B_[1] = By;};
        void setBz(double Bz) {B_[2] = Bz;};
        void setB(double Bx, double By, double Bz) {
            B_[0] = Bx;
            B_[1] = By;
            B_[2] = Bz;
        };
        double getX(void) const {return B_[0];};
        double getY(void) const {return B_[1];};
        double getZ(void) const {return B_[2];};
        const std::array<double,3>& getB() const { return B_; };

};