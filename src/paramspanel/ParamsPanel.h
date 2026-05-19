#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include "backends/imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <array>

struct SystemParams {
    double q_e19;
    double m_MeV;
    double Bx;
    double Bz;
    std::array<float, 3> r;
    std::array<float, 3> v;
    float timescale;
    SystemParams(): q_e19(1.6), m_MeV(0.511), Bx(0.0), 
                    Bz(0.5), r{0, 0, 0}, v{5e4, 5e4, 5e4}, timescale(1.0f) {}
};

class ParamsPanel {
    private:
        GLFWwindow * window_;
        GLfloat width_;
        GLfloat height_;
        GLfloat offset_;
        SystemParams params;
        void initPanel();
        void closePanel();
        bool paused_ = false;
        bool need_reset_ = false;
    public:
        ParamsPanel(GLFWwindow * window);
        ParamsPanel(GLFWwindow * window, GLfloat width, GLfloat height, GLfloat offset);
        void drawPanel();
        void render();
        bool is_paused() const {return paused_; };
        bool to_reset() const {return need_reset_; };
        const SystemParams & getSystemParams() const;
        ~ParamsPanel();
};  