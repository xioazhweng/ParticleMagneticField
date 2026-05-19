#pragma once
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <math.h>
#include <deque>
class SceneView {
    private:
        GLFWwindow * window_;
        GLfloat xAlpha = 5;
        GLfloat zAlpha = 5;
        GLfloat posx = 0, posy = 0;
        GLfloat cameraDistance = 0;
        GLfloat scale = 10e5;
    public:
        SceneView(GLFWwindow * window): window_(window) {};
        void ShowWorld();
        void DrawDecardSystem(GLfloat length = 10e10);
        void MoveCamera();
        void DrawParticle(GLfloat x, GLfloat y, GLfloat z);
        void DrawTrajectory(const std::deque<std::array<double,3>>& trajectory);
    };