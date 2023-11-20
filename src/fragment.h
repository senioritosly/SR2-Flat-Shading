#pragma once
#include <glm/glm.hpp>
#include "color.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    Color color;
};

struct Fragment {
    glm::ivec2 position; // X and Y coordinates of the pixel (in screen space)
    Color color; // r, g, b, a values for color
    double z;  // zbuffer
    float intensity;  // light intensity
};

struct FragColor {
  Color color;
  double z; // instead of z buffer
};