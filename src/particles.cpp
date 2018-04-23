#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "particles.h"
#include "sphere.h"
#include "CGL/vector3D.h"
#include "collisionObject.h"
#include "plane.h"

using namespace std;

particles::particles(double width, double height, double length, int num_width_points,
             int num_height_points, int num_length_points, float radius, float friction) {
  this->width = width;
  this->height = height;
  this->length = length;
  this->num_width_points = num_width_points;
  this->num_height_points = num_height_points;
  this->num_length_points = num_length_points;
  this->radius = radius;
  this->friction = friction;
  this->origin = Vector3D(3, 3, 3);
//  buildGrid();
}

void particles::buildGrid() {
  for (int i=0; i<num_height_points; i++) {
    for (int j=0; j<num_width_points; j++) {
      for (int k=0; k<num_length_points; k++) {
        Sphere sp = Sphere(origin+Vector3D(2*radius*i, 2*radius*j, 2*radius*k), radius, friction);
        particle_list.emplace_back(sp);
      }
    }
  }
}

particles::~particles() {
}

void particles::simulate(double frames_per_sec, double simulation_steps, vector<Vector3D> external_forces,
                         vector<CollisionObject *> *collision_objects) {

  double delta_t = 1.0f / frames_per_sec / simulation_steps;

  for (Sphere &sp : particle_list) {
    for (const Vector3D &external_force : external_forces) {
        sp.velocity += delta_t * external_force;
    }
    sp.predicted_position = sp.origin + delta_t * sp.velocity;
  }

//  for (Sphere i : particle_list)
//  {
//    i.neighbors = findNeighbors(i);// Note that, we try to find neighbors of predicted position of i
//  }
//
//  for (Sphere i: particle_list) {
//    i.lambda = findLambda(i);     // see equation (1) - (9)
//  }
//
//  for (Sphere i: particle_list) {
//    i.delta_p = findDeltaP(i);     // see eqaution (1) - (9). Change of position
//    perform_Collision_Detection(i); // if collsion, change delta_p;
//  }
//
//  for (Sphere i: particle_list) {
//    i.predicted_position += i.delta_p;
//  }

    for (Sphere &sp : particle_list) {
        sp.velocity = (sp.predicted_position - sp.origin) / delta_t;
        sp.last_origin = sp.origin;
        sp.origin = sp.predicted_position;
    }

    build_spatial_map();
    for (Sphere &sp : particle_list) {
        self_collide(sp, simulation_steps);
    }

//    for (Sphere &sp : particle_list) {
//        for (CollisionObject *co : *collision_objects) {
//            co->collide(sp);
//        }
//    }
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

void particles::self_collide(Sphere sp, double simulation_steps) {
    float position = hash_position(sp.origin);
    Vector3D corrections = Vector3D(0, 0, 0);
    float cases = 0;

    for (Sphere* item : *map[position]) {

        Vector3D distanceDiff = sp.origin - item->origin;
        bool isSelf = (item == &sp);
        bool tooClose = sqrt(pow(distanceDiff[0], 2) +
                             pow(distanceDiff[1], 2) +
                             pow(distanceDiff[2], 2)) < (2 * sp.radius);
        if (!isSelf && tooClose) {
            Vector3D correction = distanceDiff.unit() * 2 * sp.radius - distanceDiff;
            corrections += correction;
            cases += 1;
        }
    }
    if (cases != 0) {
        sp.origin = sp.origin + corrections / cases / simulation_steps;
    }
}

vector<Sphere*> findNeighbors(Sphere sp){
    return vector<Sphere*>();
}

double findLambda(Sphere sp){
    return 0.0;
}

Vector3D findDeltaP(Sphere sp){
    return Vector3D();
}

void perform_Collision_Detection(Sphere sp){
    return;
}

void particles::build_spatial_map() {
    for (const auto &entry : map) {
        delete(entry.second);
    }
    map.clear();

    for (Sphere &sp : particle_list) {

        float position = hash_position(sp.origin);

        if (map.find(position) == map.end()) {
            auto * new_position = new vector<Sphere *>();
            new_position->push_back(&sp);
            map[position] = new_position;
        } else {
            map[position]->push_back(&sp);
        }
    }
}

float getHash(std::array<float, 3> array) {
    float hash = 0;
    for (float num : array) {
        hash = num * num + hash * hash;
    }
    return hash;
}

float particles::hash_position(Vector3D pos) {
    // TODO (Part 4.1): Hash a 3D position into a unique float identifier that represents
    // membership in some uniquely identified 3D box volume.

    auto w = static_cast<float>(3 * width / num_width_points);
    auto h = static_cast<float>(3 * height / num_height_points);
    float t = max(w, h);

    std::array<float, 3> array = {static_cast<float>(fmod(pos.x, w)),
                                  static_cast<float>(fmod(pos.y, h)),
                                  static_cast<float>(fmod(pos.z, t))};
    return getHash(array);
}


///////////////////////////////////////////////////////
/// YOU DO NOT NEED TO REFER TO ANY CODE BELOW THIS ///
///////////////////////////////////////////////////////

void particles::reset() {
}

