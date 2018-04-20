#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "cloth.h"
#include "collision/plane.h"
#include "collision/sphere.h"

using namespace std;

Cloth::Cloth(double width, double height, int num_width_points,
             int num_height_points, float thickness) {
  this->width = width;
  this->height = height;
  this->num_width_points = num_width_points;
  this->num_height_points = num_height_points;
  this->thickness = thickness;

  buildGrid();
  buildClothMesh();
}

Cloth::~Cloth() {
  point_masses.clear();
  springs.clear();

  if (clothMesh) {
    delete clothMesh;
  }
}

void Cloth::buildGrid() {
  // TODO (Part 1.1): Build a grid of masses.

//  float dh = static_cast<float>(height) / num_height_points;
//  float dw = static_cast<float>(width) / num_width_points;
//
//  for (int i = 0; i < num_height_points; i++) {
//    for (int j = 0; j < num_width_points; j++) {
//      if (orientation == HORIZONTAL) {
//        point_masses.emplace_back(PointMass(Vector3D(j * dw, 1.0, i * dh), false));
//      }
//      else {
//        auto offset = static_cast<float>(((static_cast<float>(2.0 * (static_cast<float>(rand()) / RAND_MAX))) - 1.0) / 1000.0);
//        point_masses.emplace_back(PointMass(Vector3D(j * dw, i * dh, offset), false));
//      }
//    }
//  }
//
//  for (auto &i : pinned) {
//    point_masses[i[0] + i[1] * num_width_points].pinned = true;
//  }
//
//  // TODO (Part 1.2): Add springs
//
//  for (int i = 0; i < num_height_points; i++) {
//    for (int j = 0; j < num_width_points; j++) {
//      PointMass* pm_a = &point_masses[i * num_width_points + j];
//
//      if (i != 0) {
//        PointMass* pm_b = pm_a - num_width_points;
//        if (j != 0) {
//          springs.emplace_back(pm_a, pm_b - 1, SHEARING);
//        }
//        if (j != num_width_points - 1) {
//          springs.emplace_back(pm_a, pm_b + 1, SHEARING);
//        }
//        springs.emplace_back(pm_a, pm_b, STRUCTURAL);
//      }
//
//      if (j != 0) {
//        PointMass* pm_b = pm_a - 1;
//        springs.emplace_back(pm_a, pm_b, STRUCTURAL);
//      }
//      if (i >= 2) {
//        PointMass* pm_b = pm_a - 2 * num_width_points;
//        springs.emplace_back(pm_a, pm_b, BENDING);
//      }
//      if (j >= 2) {
//        PointMass* pm_b = pm_a - 2;
//        springs.emplace_back(pm_a, pm_b, BENDING);
//      }
//    }
//  }

}

double pow(double num, int index) {
    if (index == 0) {
        return 1;
    }
    double result = 1;
    for (int i = 0; i < index; i++) {
        result = result * num;
    }
    return result;
}

void Cloth::simulate(double frames_per_sec, double simulation_steps, ClothParameters *cp,
                     vector<Vector3D> external_accelerations,
                     vector<CollisionObject *> *collision_objects) {
  double mass = width * height * cp->density / num_width_points / num_height_points;
  double delta_t = 1.0f / frames_per_sec / simulation_steps;

  // TODO (Part 2.1): Compute total force acting on each point mass.

//    for (PointMass &pm : point_masses) {
//        Vector3D a = Vector3D(0, 0, 0);
//        for (Vector3D ex_a: external_accelerations) {
//            a += ex_a;
//        }
//        pm.forces = mass * a;
//    }
//
//    for (Spring &spring: springs) {
//
//        Vector3D positionDiff = spring.pm_a->position - spring.pm_b->position;
//        double ks = cp->ks;
//        if (cp->enable_bending_constraints && spring.spring_type == BENDING) {
//            ks = cp->ks * 0.2;
//        }
//        double fs = ks * (sqrt( pow(positionDiff[0], 2) +
//                                           pow(positionDiff[1], 2) +
//                                           pow(positionDiff[2], 2)) - spring.rest_length);
//
//        if ((cp->enable_bending_constraints && spring.spring_type == BENDING) ||
//                (cp->enable_shearing_constraints && spring.spring_type == SHEARING) ||
//                    (cp->enable_structural_constraints && spring.spring_type == STRUCTURAL)) {
//            Vector3D offset = positionDiff.unit() * fs;
//            spring.pm_a->forces = spring.pm_a->forces - offset;
//            spring.pm_b->forces = spring.pm_b->forces + offset;
//        }
//    }

  // TODO (Part 2.2): Use Verlet integration to compute new point mass positions
//    for (PointMass &pm : point_masses) {
//        if (!pm.pinned) {
//            Vector3D new_position = pm.position +
//                    (1.0 - cp->damping / 100.0) * (pm.position - pm.last_position) +
//                    pm.forces / mass * pow(delta_t, 2);
//            pm.last_position = pm.position;
//            pm.position = new_position;
//        }
//    }


  // This won't do anything until you complete Part 4.
//  build_spatial_map();
//  for (PointMass &pm : point_masses) {
//    self_collide(pm, simulation_steps);
//  }

  // This won't do anything until you complete Part 3.
//  for (PointMass &pm : point_masses) {
//    for (CollisionObject *co : *collision_objects) {
//      co->collide(pm);
//    }
//  }


  // TODO (Part 2.3): Constrain the changes to be such that the spring does not change
  // in length more than 10% per timestep [Provot 1995].
//    for (Spring &spring: springs) {
//        Vector3D positionDiff = spring.pm_b->position - spring.pm_a->position;
//        double distSpring = sqrt( pow(positionDiff[0], 2) +
//                           pow(positionDiff[1], 2) +
//                           pow(positionDiff[2], 2));
//        double restSpring = 1.1 * spring.rest_length;
//
//        if (distSpring > restSpring) {
//            double distStretch = (distSpring - restSpring) / 2.0;
//            Vector3D offset1 = positionDiff * restSpring / distSpring;
//            Vector3D offset2 = positionDiff * distStretch / distSpring;
//
//            if (spring.pm_a->pinned && !spring.pm_b->pinned) {
//                spring.pm_b->position = spring.pm_a->position + offset1;
//
//            } else if (spring.pm_b->pinned) {
//                spring.pm_a->position = spring.pm_b->position - offset1;
//
//            } else {
//                spring.pm_a->position = spring.pm_a->position + offset2;
//                spring.pm_b->position = spring.pm_b->position - offset2;
//            }
//        }
//    }
}

void Cloth::build_spatial_map() {
  for (const auto &entry : map) {
    delete(entry.second);
  }
  map.clear();

  // TODO (Part 4.2): Build a spatial map out of all of the point masses.

//    for (PointMass &pm : point_masses) {
//        float position = hash_position(pm.position);
//        if (map.find(position) == map.end()) {
//            auto * newpos = new vector<PointMass *>();
//            newpos->push_back(&pm);
//            map[position] = newpos;
//        } else {
//            map[position]->push_back(&pm);
//        }
//    }
}

void Cloth::self_collide(PointMass &pm, double simulation_steps) {
  // TODO (Part 4.3): Handle self-collision for a given point mass.
//    float position = hash_position(pm.position);
//    Vector3D b = Vector3D(0, 0, 0);
//    float cases = 0;
//    for (PointMass* pointm: *map[position]) {
//        Vector3D distanceDiff = pm.position - pointm->position;
//        bool isSelf = pointm == &pm;
//        bool tooClose = sqrt(pow(distanceDiff[0], 2) +
//                                     pow(distanceDiff[1], 2) +
//                                     pow(distanceDiff[2], 2)) < (2 * thickness);
//        if (!isSelf && tooClose) {
//            Vector3D correction = distanceDiff.unit() * 2 * thickness - distanceDiff;
//            b += correction;
//            cases += 1;
//        }
//    }
//    if (cases != 0) {
//        pm.position = pm.position + b / cases / simulation_steps;
//    }
}

float getHash(std::array<float, 3> array) {
    float hash = 0;
    for (float num : array) {
        hash = num * num + hash * hash;
    }
    return hash;
}

float Cloth::hash_position(Vector3D pos) {
  // TODO (Part 4.1): Hash a 3D position into a unique float identifier that represents
  // membership in some uniquely identified 3D box volume.

//    auto w = static_cast<float>(3 * width / num_width_points);
//    auto h = static_cast<float>(3 * height / num_height_points);
//    float t = max(w, h);
//
//    std::array<float, 3> array = {static_cast<float>(fmod(pos.x, w)),
//                                  static_cast<float>(fmod(pos.y, h)),
//                                  static_cast<float>(fmod(pos.z, t))};
//    return getHash(array);
}

///////////////////////////////////////////////////////
/// YOU DO NOT NEED TO REFER TO ANY CODE BELOW THIS ///
///////////////////////////////////////////////////////

void Cloth::reset() {
  PointMass *pm = &point_masses[0];
  for (int i = 0; i < point_masses.size(); i++) {
    pm->position = pm->start_position;
    pm->last_position = pm->start_position;
    pm++;
  }
}

void Cloth::buildClothMesh() {
  if (point_masses.size() == 0) return;

  ClothMesh *clothMesh = new ClothMesh();
  vector<Triangle *> triangles;

  // Create vector of triangles
  for (int y = 0; y < num_height_points - 1; y++) {
    for (int x = 0; x < num_width_points - 1; x++) {
      PointMass *pm = &point_masses[y * num_width_points + x];
      // Both triangles defined by vertices in counter-clockwise orientation
      triangles.push_back(new Triangle(pm, pm + num_width_points, pm + 1));
      triangles.push_back(new Triangle(pm + 1, pm + num_width_points,
                                       pm + num_width_points + 1));
    }
  }

  // For each triangle in row-order, create 3 edges and 3 internal halfedges
  for (int i = 0; i < triangles.size(); i++) {
    Triangle *t = triangles[i];

    // Allocate new halfedges on heap
    Halfedge *h1 = new Halfedge();
    Halfedge *h2 = new Halfedge();
    Halfedge *h3 = new Halfedge();

    // Allocate new edges on heap
    Edge *e1 = new Edge();
    Edge *e2 = new Edge();
    Edge *e3 = new Edge();

    // Assign a halfedge pointer to the triangle
    t->halfedge = h1;

    // Assign halfedge pointers to point masses
    t->pm1->halfedge = h1;
    t->pm2->halfedge = h2;
    t->pm3->halfedge = h3;

    // Update all halfedge pointers
    h1->edge = e1;
    h1->next = h2;
    h1->pm = t->pm1;
    h1->triangle = t;

    h2->edge = e2;
    h2->next = h3;
    h2->pm = t->pm2;
    h2->triangle = t;

    h3->edge = e3;
    h3->next = h1;
    h3->pm = t->pm3;
    h3->triangle = t;
  }

  // Go back through the cloth mesh and link triangles together using halfedge
  // twin pointers

  // Convenient variables for math
  int num_height_tris = (num_height_points - 1) * 2;
  int num_width_tris = (num_width_points - 1) * 2;

  bool topLeft = true;
  for (int i = 0; i < triangles.size(); i++) {
    Triangle *t = triangles[i];

    if (topLeft) {
      // Get left triangle, if it exists
      if (i % num_width_tris != 0) { // Not a left-most triangle
        Triangle *temp = triangles[i - 1];
        t->pm1->halfedge->twin = temp->pm3->halfedge;
      } else {
        t->pm1->halfedge->twin = nullptr;
      }

      // Get triangle above, if it exists
      if (i >= num_width_tris) { // Not a top-most triangle
        Triangle *temp = triangles[i - num_width_tris + 1];
        t->pm3->halfedge->twin = temp->pm2->halfedge;
      } else {
        t->pm3->halfedge->twin = nullptr;
      }

      // Get triangle to bottom right; guaranteed to exist
      Triangle *temp = triangles[i + 1];
      t->pm2->halfedge->twin = temp->pm1->halfedge;
    } else {
      // Get right triangle, if it exists
      if (i % num_width_tris != num_width_tris - 1) { // Not a right-most triangle
        Triangle *temp = triangles[i + 1];
        t->pm3->halfedge->twin = temp->pm1->halfedge;
      } else {
        t->pm3->halfedge->twin = nullptr;
      }

      // Get triangle below, if it exists
      if (i + num_width_tris - 1 < 1.0f * num_width_tris * num_height_tris / 2.0f) { // Not a bottom-most triangle
        Triangle *temp = triangles[i + num_width_tris - 1];
        t->pm2->halfedge->twin = temp->pm3->halfedge;
      } else {
        t->pm2->halfedge->twin = nullptr;
      }

      // Get triangle to top left; guaranteed to exist
      Triangle *temp = triangles[i - 1];
      t->pm1->halfedge->twin = temp->pm2->halfedge;
    }

    topLeft = !topLeft;
  }

  clothMesh->triangles = triangles;
  this->clothMesh = clothMesh;
}
