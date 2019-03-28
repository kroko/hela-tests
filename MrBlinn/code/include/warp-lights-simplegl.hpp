#ifndef warp_lights_simplegl_hpp
#define warp_lights_simplegl_hpp

#include "glm/vec3.hpp"

// light structs suitable for oldschool shading model

namespace warp {
  namespace lights {

    struct Directional_t {
      glm::vec3 direction;

      glm::vec3 ambient;
      glm::vec3 diffuse;
      glm::vec3 specular;

      Directional_t():
      direction(glm::vec3(-1.0f)),
      ambient(glm::vec3(0.1f)),
      diffuse(glm::vec3(0.1f)),
      specular(glm::vec3(0.1f))
      {
      }
    };

    struct Spot_t {
      glm::vec3 position;
      glm::vec3 direction;

      glm::vec3 ambient;
      glm::vec3 diffuse;
      glm::vec3 specular;

      float cutOff;
      float outerCutOff;

      float constant;
      float linear;
      float quadratic;

      Spot_t():
      position(glm::vec3(1.0)),
      direction(glm::vec3(-1.0)),
      ambient(glm::vec3(0.1f)),
      diffuse(glm::vec3(0.1f)),
      specular(glm::vec3(0.1f)),
      cutOff(0.8f),
      outerCutOff(1.0f),
      constant(1.0f),
      linear(1.0f),
      quadratic(1.0f)
      {
      }
    };

    struct Point_t {
      glm::vec3 position;
      glm::vec3 direction;

      glm::vec3 ambient;
      glm::vec3 diffuse;
      glm::vec3 specular;

      float constant;
      float linear;
      float quadratic;

      Point_t():
      position(glm::vec3(1.0)),
      direction(glm::vec3(-1.0)),
      ambient(glm::vec3(0.1f)),
      diffuse(glm::vec3(0.1f)),
      specular(glm::vec3(0.1f)),
      constant(1.0f),
      linear(1.0f),
      quadratic(1.0f)
      {
      }
    };

  } // lights
} //warp

#endif // warp_lights_simplegl_hpp

