add_library(sceneview SceneView.h SceneView.cpp)
target_link_libraries(sceneview
    GL
    GLU
    GLEW
    glut
    simulation
    particle

)