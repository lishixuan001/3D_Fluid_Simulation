#ifndef COLLISIONOBJECT
#define COLLISIONOBJECT

#include <nanogui/nanogui.h>
#include "CGL/vector3D.h"

using namespace CGL;
using namespace std;
using namespace nanogui;

class CollisionObject {
public:
  virtual void render(GLShader &shader) = 0;
  virtual void collide() = 0;
  Vector3D origin;

private:
  double friction;
};

#endif /* COLLISIONOBJECT */
