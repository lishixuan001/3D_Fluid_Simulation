#ifndef COLLISIONOBJECT
#define COLLISIONOBJECT

#include <nanogui/nanogui.h>


using namespace CGL;
using namespace std;
using namespace nanogui;

class CollisionObject {
public:
  virtual void render(GLShader &shader) = 0;
  virtual void collide() = 0;

private:
  double friction;
};

#endif /* COLLISIONOBJECT */
