#ifndef HelloFBdevNucleus_hpp
#define HelloFBdevNucleus_hpp

#include "nucleus/Nucleus.hpp"

#define GLsizeiToGLvoid(i) (GLvoid*)(uintptr_t)(i)
#define UNBIND 0
#define UNUSE 0

class HelloFBdev : public hela::nucleus::Nucleus {

public:

  static void prepareNucleus(hela::nucleus::Nucleus::NucleusSettings * prepNucleus);
  static void prepareMotor(hela::motor::Motor::MotorSettings * prepMotor);

public:

  void setup() override;
  // void update() override;
  void draw() override;
  void cleanup() override;

  // void eventKeyboardKey(unsigned short key, int action) override;
  // void eventMousePositionDelta(int xpos, int ypos) override;
  // void eventMouseButton(unsigned short button, int action) override;
  // void eventMouseWheel(int xoffset, int yoffset) override;
   void eventWindowResize(int width, int height) override;
  // void eventWindowDrop(int count, const char** paths) override;

private:

  GLuint m_helloShaderProgram;
  GLuint m_helloVAO;
  GLuint m_helloVBO;
  GLuint m_uTimeLoc;

}; // HelloFBdev

#endif // HelloFBdevNucleus_hpp
