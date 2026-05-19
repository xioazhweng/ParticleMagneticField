add_library(simulation Simulation.h Simulation.cpp)
target_link_libraries(simulation PRIVATE
    magneticfield
    particle)   