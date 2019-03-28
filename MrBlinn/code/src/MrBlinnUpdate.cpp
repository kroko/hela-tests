#include "MrBlinnNucleus.hpp"

namespace hln = hela::nucleus;

// ----------------------------------------------------------------------------
void MrBlinn::update() {
  timeUpdate();
  controlsUpdate();
  cameraUpdate();
}

// ----------------------------------------------------------------------------
void MrBlinn::timeUpdate() {
  m_currTime = hln::getElapsedSeconds();
  timerProgramHolder.curr = m_currTime;
  timerProgramHolder.delta = timerProgramHolder.curr - timerProgramHolder.prev;
  timerProgramHolder.prev = timerProgramHolder.curr;

  // spdlog::trace("timerProgramHolder.delta {}", timerProgramHolder.delta);
}

// ----------------------------------------------------------------------------
void MrBlinn::controlsUpdate() {
  // On every frame detect the state of our keyboard keys that we are interested in for movement and pass to camera controller
  if (!(controlsWasdState.w && controlsWasdState.s)) {
    if (controlsWasdState.w) {
      cameraController1.setPositionStrafeInWorld(warp::camera::FORWARD, timerProgramHolder.delta);
    }
    if (controlsWasdState.s) {
      cameraController1.setPositionStrafeInWorld(warp::camera::BACKWARD, timerProgramHolder.delta);
    }
  }
  if (!(controlsWasdState.a && controlsWasdState.d)) {
    if (controlsWasdState.a) {
      cameraController1.setPositionStrafeInWorld(warp::camera::LEFT, timerProgramHolder.delta);
    }
    if (controlsWasdState.d) {
      cameraController1.setPositionStrafeInWorld(warp::camera::RIGHT, timerProgramHolder.delta);
    }
  }
  if (!(controlsWasdState.space && controlsWasdState.ctrl)) {
    if (controlsWasdState.space) {
      cameraController1.setPositionStrafeInWorld(warp::camera::UP, timerProgramHolder.delta);
    }
    if (controlsWasdState.ctrl) {
      cameraController1.setPositionStrafeInWorld(warp::camera::DOWN, timerProgramHolder.delta);
    }
  }
}

// ----------------------------------------------------------------------------
void MrBlinn::cameraUpdate() {
  view = cameraController1.getViewMatrix();
  projection = glm::perspective(
                                glm::radians(cameraController1.getZoom()),
                                static_cast<float>(sizeWindow.x) / static_cast<float>(sizeWindow.y),
                                cameraController1.getNear(),
                                cameraController1.getFar()
                                );
}
