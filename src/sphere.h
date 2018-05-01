#ifndef SPHERE_H
#define SPHERE_H

#include <nanogui/nanogui.h>
#include "CGL/vector3D.h"

using namespace CGL;
using namespace std;
using namespace nanogui;

struct Sphere {
public:
  Sphere(const Vector3D &origin, double radius, Vector3D velocity)
      : last_origin(origin), origin(origin), radius(radius), start_position(origin), velocity(velocity){
        
}
  Vector3D start_position;
  Vector3D origin;
  double radius;
  void render(GLShader &shader);
  void collide();
  Vector3D last_origin;
  Vector3D force;
  double friction;
  double lambda;
  double C;//constrain
  double rho;
  Vector3D C_Gradient;
  Vector3D temp_Gradient;
    Vector3D velocity;
    Vector3D next_velocity;
    Vector3D predicted_position;
    Vector3D delta_p;
    vector<Sphere*> neighbors;
};


#endif /* COLLISIONOBJECT_SPHERE_H */
