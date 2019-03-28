#ifndef warp_camera_hpp
#define warp_camera_hpp

//#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

// ============================================================================
namespace warp {
  namespace camera {

    // ============================================================================
    class CameraEuler
    {
    public:

      CameraEuler(
                  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
                  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
                  float yawDeg = -90.0f,
                  float pitchDeg = 0.0f) :
      worldUp_(glm::normalize(worldUp)),
      camPositionCurr_(position),
      camPositionPrev_(position),
      camFront_(glm::normalize(front)),
      camZoom_(45.0f),
      camNear_(0.1f),
      camFar_(20.0f),
      eulerYawDegCurr_(yawDeg),
      eulerPitchDegCurr_(pitchDeg)
      {
        eulerYawDegPrev_ = eulerYawDegCurr_;
        eulerPitchDegPrev_ = eulerPitchDegCurr_;
        eulerYawDegDelta_ = 0.0f;
        eulerPitchDegDelta_ = 0.0f;
        updateCameraVectors_();
      }

      void setPositionByDirection(glm::vec3 direction, float amount)
      {
        camPositionPrev_ = camPositionCurr_;
        camPositionCurr_ += glm::normalize(direction) * amount;
      }

      void setPositionByDelta(glm::vec3 delta)
      {
        camPositionPrev_ = camPositionCurr_;
        camPositionCurr_ += delta;
      }

      // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
      void setDirectionDelta(float xoffset, float yoffset, bool constrainPitch = true)
      {
        eulerYawDegPrev_ = eulerYawDegCurr_;
        eulerPitchDegPrev_ = eulerPitchDegCurr_;

        eulerYawDegCurr_   += xoffset;
        eulerPitchDegCurr_ += yoffset;

        // Son, this isn't quat camera!
        if (constrainPitch)
        {
          if (eulerPitchDegCurr_ > 89.0f)
            eulerPitchDegCurr_ = 89.0f;
          if (eulerPitchDegCurr_ < -89.0f)
            eulerPitchDegCurr_ = -89.0f;
        }

        eulerYawDegDelta_ = eulerYawDegCurr_ - eulerYawDegPrev_;
        eulerPitchDegDelta_ = eulerPitchDegCurr_ - eulerPitchDegPrev_;

        // Update camFront_, camRight_ and Up Vectors using the updated Euler angles
        updateCameraVectors_();
      }

      void setZoom(float zoomOffset)
      {
        if (camZoom_ >= 1.0f && camZoom_ <= 45.0f)
          camZoom_ -= zoomOffset;
        if (camZoom_ <= 1.0f)
          camZoom_ = 1.0f;
        if (camZoom_ >= 45.0f)
          camZoom_ = 45.0f;
      }

      // Return view matrix ready to be used in MVP worfkflow
      glm::mat4 getViewMatrix() const
      {
        return glm::lookAt(camPositionCurr_, camPositionCurr_ + camFront_, camUp_);
      }

      float getNear() const {
        return camNear_;
      }
      float getFar() const {
        return camFar_;
      }
      float getZoom() const {
        return camZoom_;
      }
      glm::vec3 getPositionCurr() const {
        return camPositionCurr_;
      }
      glm::vec3 getPositionPrev() const {
        return camPositionPrev_;
      }

    protected:

      glm::vec3 getWorldFront() const {
        return worldFront_;
      }
      glm::vec3 getWorldUp() const {
        return worldUp_;
      }

      glm::vec3 getCamPositionCurr_() const {
        return camPositionCurr_;
      }
      glm::vec3 getCamFront() const {
        return camFront_;
      }
      glm::vec3 getCamUp() const {
        return camUp_;
      }
      glm::vec3 getCamRight() const {
        return camRight_;
      }

      // World attributes
      glm::vec3 worldUp_;
      glm::vec3 worldFront_;

      // Camera attributes
      glm::vec3 camPositionCurr_;
      glm::vec3 camPositionPrev_;
      glm::vec3 camFront_;
      glm::vec3 camUp_;
      glm::vec3 camRight_;

      float camZoom_;
      float camNear_;
      float camFar_;

      // Euler Angles
      float eulerYawDegCurr_;
      float eulerPitchDegCurr_;
      float eulerYawDegPrev_;
      float eulerPitchDegPrev_;
      float eulerYawDegDelta_;
      float eulerPitchDegDelta_;

      void updateCameraVectors_()
      {
        // Calculate the new camFront_ vector
        glm::vec3 tmpFront = glm::normalize(camFront_);

        // jaw
        // rotate around world up
        tmpFront = glm::rotate(tmpFront, glm::radians(-eulerYawDegDelta_), worldUp_);
        tmpFront = glm::normalize(tmpFront);

        // pitch
        // rotate around right vector
        glm::vec3 tmpRight = glm::normalize(glm::cross(worldUp_, tmpFront));
        tmpFront = glm::rotate(tmpFront, glm::radians(-eulerPitchDegDelta_), tmpRight);
        tmpFront = glm::normalize(tmpFront);

        camFront_ = glm::normalize(tmpFront);

        camRight_ = glm::normalize(glm::cross(camFront_, worldUp_));
        camUp_    = glm::normalize(glm::cross(camRight_, camFront_));

        worldFront_ = glm::normalize(glm::cross(worldUp_, camRight_));
      }

    };

    // ============================================================================
    enum CameraControllerStrafeCodes {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT,
      UP,
      DOWN
    };

    // ============================================================================
    // A simple keyboard + mouse WASD controller, no lean left/right
    class CameraControllerWasdSimple : public CameraEuler
    {
    public:
      using CameraEuler::CameraEuler;

      void setPositionStrafeInWorld(warp::camera::CameraControllerStrafeCodes direction, float frameTimeSeconds = 0.016f) {
        // 2.5f;
        float velocity = sensitivityMove_ * frameTimeSeconds;
        glm::vec3 newPosition;

        if (direction == warp::camera::FORWARD)
          newPosition += getWorldFront() * velocity;
        if (direction == warp::camera::BACKWARD)
          newPosition += getWorldFront() * -velocity;
        if (direction == warp::camera::LEFT)
          newPosition += getCamRight() * -velocity;
        if (direction == warp::camera::RIGHT)
          newPosition += getCamRight() * velocity;
        if (direction == warp::camera::UP)
          newPosition += getWorldUp() * velocity;
        if (direction == warp::camera::DOWN)
          newPosition += getWorldUp() * -velocity;


        setPositionByDelta(newPosition);
      }

      void setDirectionMouseDelta(float xoffset, float yoffset, float frameTimeSeconds = 0.016f) {
        // 0.1f;
        setDirectionDelta(xoffset * sensitivityDirection_ * frameTimeSeconds, yoffset * sensitivityDirection_ * frameTimeSeconds);
      }

      void setSensitivityDirection(float sensitivity) {
        sensitivityDirection_ = sensitivity;
      }

      void setSensitivityMove(float sensitivity) {
        sensitivityMove_ = sensitivity;
      }

    private:
      float sensitivityMove_ = 2.5f;
      float sensitivityDirection_ = 6.25f;

    };

  } // namespace camera
} // namespace warp

#endif // warp_camera_hpp


