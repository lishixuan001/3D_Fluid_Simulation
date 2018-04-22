#ifndef PARTICLES_H
#define PARTICLES_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "CGL/CGL.h"
#include "CGL/misc.h"
#include "collision/sphere.h"
#include "collision/collisionObject.h"

using namespace CGL;
using namespace std;

enum e_orientation { HORIZONTAL = 0, VERTICAL = 1 };

struct particles {
  particles() {}
  particles(double width, double height, double length, int num_width_points,
        int num_height_points, int num_length_points);
  ~particles();

  void simulate(double frames_per_sec, double simulation_steps,
                           Vector3D external_forces,vector<CollisionObject *> *collision_objects);
  void reset();
  float hash_position(Vector3D pos);
    
  vector<Sphere*> findNeighbors(Sphere i){
        return vector<Sphere*>();
    }
  
  double findLambda(Sphere i){
      return 0.0;
    }

  Vector3D findDeltaP(Sphere i){
        return Vector3D();
    }
    
    void perform_Collision_Detection(Sphere i){
        return;
    }
    
    
    
  // Cloth properties
  double width;
  double height;
  double length;
  int num_width_points;
  int num_height_points;
  int num_length_points;
  e_orientation orientation;

  vector<Sphere> particle_list;

};

#endif /* CLOTH_H */
