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
      : last_origin(origin), origin(origin), radius(radius), friction(friction) {
        
}
  Vector3D origin;
  double radius;
  void render(GLShader &shader);
  void collide();
  Vector3D last_origin;
  Vector3D force;
  double friction;
  double lambda;
  double C;//constrain
  Vector3D C_Gradient;

    Vector3D velocity;
    Vector3D predicted_position;
    Vector3D delta_p;
    vector<Sphere> neighbors;
};


#endif /* COLLISIONOBJECT_SPHERE_H */
