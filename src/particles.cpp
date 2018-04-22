#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "particles.h"
#include "collision/sphere.h"
#include "CGL/vector3D.h"

using namespace std;

particles::particles(double width, double height, double length, int num_width_points,
             int num_height_points, int num_length_points) {
  this->width = width;
  this->height = height;
  this->length = length;
  this->num_width_points = num_width_points;
  this->num_height_points = num_height_points;
  this->num_length_points = num_length_points;
  // buildGrid();
}

// void particles::buildGrid() {
//   for (int i=0; i<num_height_points; i++) {
//     for (int j=0; j<num_width_points; j++) {
//       for (int k=0; k<num_length_points; k++) {
//         particle_list.emplace_back(PointMass(Vector3D(j*ww, 1.0, i*hh), false));
//       }
//     }
//   }
// }

particles::~particles() {
}

void particles::simulate(double frames_per_sec, double simulation_steps,
                     vector<Vector3D> external_accelerations,
                     vector<CollisionObject *> *collision_objects) {
    
    
    
    
    
}


float particles::hash_position(Vector3D pos) {
  // TODO (Part 4.1): Hash a 3D position into a unique float identifier that represents
  // membership in some uniquely identified 3D box volume.
  float w = 3 * width / num_width_points;
  float h = 3 * height / num_height_points;
  float t = max(w,h);
  int a = (int) floor(pos.x / w);
  int b = (int) floor(pos.y / h);
  int c = (int) floor(pos.z / t);
  return (31*a+b)*31+c;

}

///////////////////////////////////////////////////////
/// YOU DO NOT NEED TO REFER TO ANY CODE BELOW THIS ///
///////////////////////////////////////////////////////

void particles::reset() {
}

