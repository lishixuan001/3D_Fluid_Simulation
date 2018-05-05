#ifndef PARTICLES_H
#define PARTICLES_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "CGL/CGL.h"
#include "CGL/misc.h"
#include "sphere.h"
#include "collisionObject.h"

using namespace CGL;
using namespace std;

enum e_orientation { HORIZONTAL = 0, VERTICAL = 1 };

struct particles {
  particles() {}
  particles(double width, double height, double length, int num_width_points,
        int num_height_points, int num_length_points, float radius, float friction);
  ~particles();

  void simulate(double frames_per_sec, double simulation_steps, vector<Vector3D> external_forces, vector<CollisionObject *> *collision_objects, int concat, int x, int y, float intensity, int drop);
  void buildExtraGrid();
  void self_collide(Sphere sp, double simulation_steps);
  void reset();
  float hash_position(Vector3D pos);
  void build_spatial_map();
  void buildGrid();
  vector<Sphere*> find_neighbors(Sphere &sp);

  // Cloth properties
  double width;
  double height;
  double length;
  int num_width_points;
  int num_height_points;
  int num_length_points;
  Vector3D origin;
  float radius;
  float friction;
  e_orientation orientation;
  double h;

    double bounce_rate;
    double x_bounce;
    double y_bounce;
    double z_bounce;
    double box_x;
    double box_z;



  vector<Sphere> particle_list;

  // Spatial hashing
  unordered_map<float, vector<Sphere *> *> map;

};

#endif /* CLOTH_H */
