#ifndef warp_controls_hpp
#define warp_controls_hpp

#include "glm/vec2.hpp"

// ============================================================================
// State saver structure for usual WASD + SPACE and CTRL
namespace warp {
  namespace controls {

    // ============================================================================
    struct ControlsWASDState_t {
      bool w;
      bool a;
      bool s;
      bool d;
      bool space;
      bool ctrl;
      ControlsWASDState_t():
      w(false),
      a(false),
      s(false),
      d(false),
      space(false),
      ctrl(false)
      {
      }
    };

    // ============================================================================
    struct ControlsMouseState_t {
      glm::vec2 prevAbs;
      glm::vec2 currAbs;
      glm::vec2 deltaAbs;
      bool itialized;
      ControlsMouseState_t():
      prevAbs(glm::vec2(0.0f)),
      currAbs(glm::vec2(0.0f)),
      deltaAbs(glm::vec2(0.0f)),
      itialized(false)
      {
      }
    };

  } // namespace controls
} // namespace warp

#endif // warp_controls_hpp


