#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "particles.h"
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

particles::~particles() {
}

void particles::simulate(double frames_per_sec, double simulation_steps,
                     Vector3D external_forces,
                     vector<CollisionObject *> *collision_objects) {

  double delta_t = 1.0f / frames_per_sec / simulation_steps;

  for (Sphere i : particle_list)
  {
    i.velocity += delta_t * external_forces;
    i.predicted_position = i.origin + delta_t * i.velocity;
  }

  for (Sphere i : particle_list)
  {
    i.Neighbor = findNeighbors(i);// Note that, we try to find neighbors of predicted position of i
  }

  int MAX_iter =100;
  for (int iter=0; iter < MAX_iter ; iter++)
  {
    for (Sphere i: particle_list){
      i.lambda   = findLambda(i);     // see equation (1) - (9)
    }
    for (Sphere i: particle_list){
      i.delta_p  = findDeltaP(i);     // see eqaution (1) - (9). Change of position
      perform_Collision_Detection(i); // if collsion, change delta_p;
    }
    for (Sphere i: particle_list){
      i.predicted_position += i.delta_p;
    }
  }

  for (Sphere i : particle_list){
    i.velocity = (i.predicted_position - i.origin) / delta_t;

    // apply vorticity confinement and XSPH viscosity
    // Not sure what to do

    i.origin = i.predicted_position;

  }
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

