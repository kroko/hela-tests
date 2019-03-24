#include "HelloFBdevNucleus.hpp"

namespace hln = hela::nucleus;

// ----------------------------------------------------------------------------
// no event callbacks overriden that are relevant for FBdev

// ...

// Override window resize callback for devbench
// ----------------------------------------------------------------------------
void HelloFBdev::eventWindowResize(int width, int height) {
  glViewport(0, 0, width, height);
}
