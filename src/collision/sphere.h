#ifndef COLLISIONOBJECT_SPHERE_H
#define COLLISIONOBJECT_SPHERE_H

#include "collisionObject.h"

using namespace CGL;
using namespace std;

struct Sphere : public CollisionObject {
public:
  Sphere(const Vector3D &origin, double radius, double friction)
      : origin(origin), radius(radius), radius2(radius * radius),
        friction(friction) {}

  void render(GLShader &shader);
  void collide();

private:
  Vector3D origin;
  double radius;
  double radius2;

  double friction;
};

#endif /* COLLISIONOBJECT_SPHERE_H */
