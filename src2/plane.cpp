#include "iostream"
#include <nanogui/nanogui.h>

#include "ParticleSimulator.h"
#include "plane.h"

using namespace std;
using namespace CGL;

#define SURFACE_OFFSET 0.0001

void Plane::collide(Sphere &sp) {
    cout << "\norigin: " << sp.origin << endl;
    cout << "last_origin: " << sp.last_origin << endl;
    Vector3D positionDiff = sp.origin - sp.last_origin;
  double correction = dot(point - sp.last_origin, normal) / dot(positionDiff, normal);

  bool isInside = dot(sp.origin - point, normal) > 0 && dot(sp.last_origin - point, normal) <= 0;
  bool isOutside = dot(sp.origin - point, normal) < 0 && dot(sp.last_origin - point, normal) >= 0;

  if (isInside || isOutside) {
      sp.origin =
            sp.last_origin +
            normal * SURFACE_OFFSET +
            correction * positionDiff * (1 - friction);
  }
}

void Plane::render(GLShader &shader) {
  nanogui::Color color(0.7f, 0.7f, 0.7f, 1.0f);

  Vector3f sPoint(point.x, point.y, point.z);
  Vector3f sNormal(normal.x, normal.y, normal.z);
  Vector3f sParallel(normal.y - normal.z, normal.z - normal.x,
                     normal.x - normal.y);
  sParallel.normalize();
  Vector3f sCross = sNormal.cross(sParallel);

  MatrixXf positions(3, 4);
  MatrixXf normals(3, 4);

  positions.col(0) << sPoint + 2 * (sCross + sParallel);
  positions.col(1) << sPoint + 2 * (sCross - sParallel);
  positions.col(2) << sPoint + 2 * (-sCross + sParallel);
  positions.col(3) << sPoint + 2 * (-sCross - sParallel);

  normals.col(0) << sNormal;
  normals.col(1) << sNormal;
  normals.col(2) << sNormal;
  normals.col(3) << sNormal;

  if (shader.uniform("in_color", false) != -1) {
    shader.setUniform("in_color", color);
  }
  shader.uploadAttrib("in_position", positions);
  shader.uploadAttrib("in_normal", normals);

  shader.drawArray(GL_TRIANGLE_STRIP, 0, 4);
}
