#include "Controller.h"
#include "../sceneview/SceneView.h"
#include "../paramspanel/ParamsPanel.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <stdexcept>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* Controller::create_window() {
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
     std::cout << "Window size after maximize: " << mode->width << "x" << mode->height << std::endl;
    if (mode == nullptr) throw std::runtime_error("glfwGetVideoMode returned nullptr");
    width = mode->width;
    height = mode->height;
    GLFWwindow* window =
            glfwCreateWindow(
            mode->width,
            mode->height,
            "ParticleMotion",
            nullptr,
            nullptr
        );

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Couldn't create window");
    }
    glfwMaximizeWindow(window);
    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwMakeContextCurrent(window);
    
    return window;
}
void Controller::run() {
    glfwInit();
    GLFWwindow* window = create_window();
    SceneView scene(window);
    ParamsPanel panel(window, width , height, 300);
    simulation = std::make_unique<Simulation>();
    glEnable(GL_DEPTH_TEST);
    scene.ShowWorld();
    

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        panel.drawPanel();
        glClearColor(255.0f, 255.0f, 255.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        glPushMatrix();
           scene.MoveCamera(); 
           scene.DrawDecardSystem(1000.0f);
            scene.DrawParticle(simulation->getX(), simulation->getY(), simulation->getZ());
             scene.DrawTrajectory(simulation->get_trajectory());
        glPopMatrix();
        if (!panel.is_paused()) {
            simulation->step(1);
        } 
    
        
        panel.render();
        const auto & params = panel.getSystemParams();
        double MeV_to_kg = 1.78266192e-30;
        
        if (panel.to_reset()) {
            simulation->update_particle_r(params.r[0], params.r[1], params.r[2]);
            simulation->update_particle_v(params.v[0], params.v[1], params.v[2]);
            simulation->reset_trajevtory();
            simulation->update_particle_m(params.m_MeV * MeV_to_kg);
            simulation->update_particle_q(params.q_e19 * 1e-19);
            simulation->update_B(params.Bx, 0, params.Bz);
        }
        
        simulation->set_time_scale(params.timescale * 1e-12);
       
        glfwPollEvents();
        glfwSwapBuffers(window);
        
       
    }
    glfwTerminate();  
}