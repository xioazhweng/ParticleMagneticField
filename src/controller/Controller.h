#pragma once
#include <GLFW/glfw3.h>
#include "../simulation/Simulation.h"
#include <memory>

class Controller {
    private:
        int width;
        int height;
        GLFWwindow* create_window();
        std::unique_ptr<Simulation> simulation;
    public:
        void run();
};