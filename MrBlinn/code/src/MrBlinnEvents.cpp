#include "MrBlinnNucleus.hpp"

namespace hln = hela::nucleus;

// ----------------------------------------------------------------------------
void MrBlinn::eventKeyboardKey(unsigned short key, int action) {
  spdlog::trace("eventKeyboardKey {} {}", key, action);
  switch(key) {
    case KEY_ESC:
      quit();
      break;
    case KEY_W:
      if(action == HELA_RELEASE) {
        controlsWasdState.w = false;
      } else {
        controlsWasdState.w = true;
      }
      break;
    case KEY_A:
      if(action == HELA_RELEASE) {
        controlsWasdState.a = false;
      } else {
        controlsWasdState.a = true;
      }
      break;
    case KEY_S:
      if(action == HELA_RELEASE) {
        controlsWasdState.s = false;
      } else {
        controlsWasdState.s = true;
      }
      break;
    case KEY_D:
      if(action == HELA_RELEASE) {
        controlsWasdState.d = false;
      } else {
        controlsWasdState.d = true;
      }
      break;
    case KEY_SPACE:
      if(action == HELA_RELEASE) {
        controlsWasdState.space = false;
      } else {
        controlsWasdState.space = true;
      }
      break;
    case KEY_LEFTCTRL:
    case KEY_RIGHTCTRL:
      if(action == HELA_RELEASE) {
        controlsWasdState.ctrl = false;
      } else {
        controlsWasdState.ctrl = true;
      }
      break;
    default:
      // unused key
      break;
  }
}

// ----------------------------------------------------------------------------
void MrBlinn::eventMousePositionDelta(int xpos, int ypos) {
  if (!controlsMouseState.itialized) {
    controlsMouseState.itialized = true;
  }
  cameraController1.setDirectionMouseDelta(-xpos, ypos);
}

// Override window resize callback for devbench
// ----------------------------------------------------------------------------
void MrBlinn::eventWindowResize(int width, int height) {
  sizeWindow = glm::ivec2(width, height);
  sizeBuffer = sizeWindow;
  glViewport(0, 0, sizeWindow.x, sizeWindow.y);
}
