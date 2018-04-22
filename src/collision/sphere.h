#ifndef COLLISIONOBJECT_SPHERE_H
#define COLLISIONOBJECT_SPHERE_H

#include "collisionObject.h"
#include "CGL/vector3D.h"
#include "CGL/CGL.h"
#include "CGL/misc.h"
#include "CGL/vector3D.h"


using namespace CGL;
using namespace std;

struct Sphere : public CollisionObject {
public:
    // Modified by Jiannan
    Sphere(const Vector3D &origin, double radius)
            : origin(origin), radius(radius){
        velocity = Vector3D();
        predicted_position = origin;
        delta_p  = Vector3D();
        lambda   = 0;
        vector<Sphere*> Neighbor;
    }

    void render(GLShader &shader);
    void collide();

    // Added by Jiannan
    Vector3D normal();
    Vector3D origin;
    Vector3D velocity;
    Vector3D predicted_position;
    Vector3D delta_p;
    vector<Sphere*> Neighbor;
    double lambda;
    double radius;
    // End Add

};

#endif /* COLLISIONOBJECT_SPHERE_H */
