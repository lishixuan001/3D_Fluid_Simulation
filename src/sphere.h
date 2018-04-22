#ifndef SPHERE_H
#define SPHERE_H

#include <nanogui/nanogui.h>
#include "CGL/vector3D.h"

using namespace CGL;
using namespace std;
using namespace nanogui;

struct Sphere {
public:
  Sphere(const Vector3D &origin, double radius, double friction)
      : lastOrigin(origin), origin(origin), radius(radius), radius2(radius * radius),friction(friction) {
        
}
  Vector3D origin;
  double radius;
  void render(GLShader &shader);
  void collide();
  Vector3D lastOrigin;
  Vector3D force;
  double friction;
  double radius2;
  double lambda;
};


#endif /* COLLISIONOBJECT_SPHERE_H */
