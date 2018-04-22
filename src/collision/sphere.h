#ifndef COLLISIONOBJECT_SPHERE_H
#define COLLISIONOBJECT_SPHERE_H

#include "collisionObject.h"
#include "CGL/vector3D.h"

using namespace CGL;
using namespace std;

struct Sphere : public CollisionObject {
public:
  // Modified by Jiannan
  Sphere(const Vector3D &origin, double radius, double friction)
      : origin(origin), radius(radius), radius2(radius * radius),
        friction(friction) {
            velocity = Vector3D();
            predicted_position = origin;
            delta_p  = Vector3D();
            lambda   = 0;
            Neighbor = std::vector<Sphere>();
        }

  void render(GLShader &shader);
  void collide();
  
  // Added by Jiannan
  Vector3D origin;
  Vector3D velocity;
  Vector3D predicted_position;
  Vector3D delta_p;
  vector<Sphere> Neighbor;
  double lambda;
  // End Add
    
    
    
    

private:
  double radius;
  double radius2;

  double friction;
};

#endif /* COLLISIONOBJECT_SPHERE_H */
