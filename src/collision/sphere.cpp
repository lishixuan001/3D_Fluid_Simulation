#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../misc/sphere_drawing.h"
#include "sphere.h"

using namespace nanogui;
using namespace CGL;

void Sphere::collide(PointMass &pm) {
  // TODO (Part 3.1): Handle collisions with spheres.

  Vector3D positionMassDiff = origin - pm.position;
  double rMass = sqrt( pow(positionMassDiff[0], 2) +
                       pow(positionMassDiff[1], 2) +
                       pow(positionMassDiff[2], 2));
  if (rMass <= radius) {
    Vector3D intersection = origin - positionMassDiff * radius / rMass;
    Vector3D correction = intersection - pm.last_position;
    pm.position = pm.last_position + correction * (1 - friction);

  }
}

void Sphere::render(GLShader &shader) {
  // We decrease the radius here so flat triangles don't behave strangely
  // and intersect with the sphere when rendered
  Misc::draw_sphere(shader, origin, radius * 0.92);
}
