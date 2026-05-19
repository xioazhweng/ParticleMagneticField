#include "SceneView.h"
#include <stdexcept>
#include <cmath>
#include <array>
#include <algorithm>
#include <iostream>

void SceneView::ShowWorld() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,           // угол обзора по вертикали
                1.0,            // отношение ширины к высоте окна
                0.1, 1000.0);   // ближняя и дальняя плоскость отсечения

    // Настройка камеры
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 25,    // позиция камеры
            0, 0, 0, // куда смотрим
            0, 1, 0);            // вектор "вверх"
}
void SceneView::MoveCamera() { 
    glRotatef(-xAlpha, 1, 0, 0); 
    glRotatef(-zAlpha, 0, 0, 1); 
   
    if (glfwGetKey(window_, GLFW_KEY_W)) { 
        xAlpha += (xAlpha > 360 ? 0 : 5); 
        } 
    if (glfwGetKey(window_, GLFW_KEY_S)) { 
        xAlpha -= (xAlpha < 20 ? 0 : 5); 
    } 
    if (glfwGetKey(window_, GLFW_KEY_A)) { 
        zAlpha += (zAlpha > 360 ? 0 : 5); 
    } 
    if (glfwGetKey(window_, GLFW_KEY_D)) { 
        zAlpha -= (zAlpha < 20 ? 0 : 5); 
    } 
    if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
        cameraDistance -= 1.0f;
       // if (cameraDistance < 0.1f) cameraDistance = 0.1f; 
    }
    if (glfwGetKey(window_, GLFW_KEY_E) == GLFW_PRESS) {
        cameraDistance += 1.0f;
       // if (cameraDistance > 100.0f) cameraDistance = 100.0f; 
    }
    glTranslatef(-posx, -posy, -cameraDistance);
}

void SceneView::DrawDecardSystem(GLfloat far) {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // X-axis
        glColor3f(1,0,0);
        glVertex3f(-far,0,0);
        glVertex3f(far,0,0);

        // Y-axis
        glColor3f(0,1,0);
        glVertex3f(0,-far,0);
        glVertex3f(0,far,0);

        // Z-axis
        glColor3f(0,0,1);
        glVertex3f(0,0,-far);
        glVertex3f(0,0,far);
    glEnd();

};


void SceneView::DrawParticle(GLfloat x, GLfloat y, GLfloat z)
{
    x *= scale;
    y *= scale;
    z *= scale;
    glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(0.0f, 0.0f, 0.0f);
        GLUquadric* quad = gluNewQuadric();
        gluSphere(quad, 0.2f, 16, 16);
        gluDeleteQuadric(quad);
    glPopMatrix();

}

void SceneView::DrawTrajectory(const std::deque<std::array<double,3>>& trajectory) {
    if (trajectory.empty()) return;
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    int n = trajectory.size();
    for (int i = 0; i < n; ++i) {
        glColor3f(0.0f, 0.0f , 0.3f*float(i) / n); // синий цвет с затуханием
        glVertex3d(
            static_cast<GLfloat>(trajectory[i][0] * scale),
            static_cast<GLfloat>(trajectory[i][1] * scale),
            static_cast<GLfloat>(trajectory[i][2] * scale)
          
        );

    }
  

    glEnd();
}