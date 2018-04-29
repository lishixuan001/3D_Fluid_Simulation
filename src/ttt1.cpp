#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <unordered_set>
#include <unordered_map>

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
    this->num_width_points = 5;//num_width_points;
    this->num_height_points = 5;//num_height_points;
    this->num_length_points = 5;//num_length_points;
    this->radius = radius;
    this->friction = friction;
    this->origin = Vector3D(0, 0, 0);
//  buildGrid();
}

void particles::buildGrid() {
    for (int i=0; i<num_height_points; i++) {
        for (int j=0; j<num_width_points; j++) {
            for (int k=0; k<num_length_points; k++) {
                Sphere sp = Sphere(origin+Vector3D(2.5*radius*i, 3*radius*j, 3*radius*k), radius, friction);
                sp.velocity = Vector3D(0,0,0);
                particle_list.emplace_back(sp);
                //cout<<sp.origin<<endl;
            }
        }
    }
}

particles::~particles() {
}

void particles::build_spatial_map() {
        for (const auto &entry : map) {
            delete(entry.second);
        }
        map.clear();
        // TODO (Part 4.2): Build a spatial map out of all of the point masses.
        for (Sphere &sp : particle_list) {
            float pos = 10000*floor(sp.origin.x/radius)+100*floor(sp.origin.y/radius)+floor(sp.origin.z/radius);
            if (map.find(pos) == map.end()) {
                vector<Sphere *> * s = new vector<Sphere *>();
                s->push_back(&sp);
                map[pos]=s;
            }
            else {
                map[pos]->push_back(&sp);
            }
        }

    }
vector<Sphere*> particles::find_neighbors(Sphere &sp) {
    vector<Sphere*> res;
    float pos = 10000*floor(sp.origin.x/radius)+100*floor(sp.origin.y/radius)+floor(sp.origin.z/radius);
    for (int i = -1; i <= 1; i++) {
        for (int j =-1; j <= 1; j++) {
            for (int k=-1; k <= 1; k++) {
                float updated = pos+10000*i+100*j+k;
                if (map.find(updated) != map.end()) {
                    for (Sphere *sp: *map[updated]) {
                        res.push_back(sp);
                    }
                }
            }
        }
    }
    return res;


}
void particles::simulate(double frames_per_sec, double simulation_steps, vector<Vector3D> external_forces,
                         vector<CollisionObject *> *collision_objects) {

    double delta_t = 1.0f / frames_per_sec / simulation_steps;
    build_spatial_map();
    for (Sphere &sp : particle_list) {
        for (const Vector3D &external_force : external_forces) {
            sp.velocity += delta_t * external_force;
        }
        sp.predicted_position   = sp.origin + delta_t * sp.velocity;
        if (sp.predicted_position.y <0)
        {
            sp.predicted_position.y = 0;
            sp.velocity.y           = 0;
        }
        if (sp.predicted_position.x <-0.2)
        {
            sp.predicted_position.x =-0.2;
            sp.velocity.y           = 0;
        }

        if (sp.predicted_position.x >0.2)
        {
            sp.predicted_position.x = 0.2;
            sp.velocity.x           = 0;
        }

    }

    
    // Brute force finding neighbor
    // Set h=0.02, with r=0.01, m = 1
    

    double h = 5 * particle_list[0].radius;
    for (Sphere &i : particle_list){
        i.C = 0.0;
        i.neighbors.clear();
        for (Sphere j: particle_list){
            Vector3D distij = (i.predicted_position - j.origin);
            if ( distij.norm() < h){
                Sphere* to_push = &j;
                //cout<<to_push<<endl;
                //i.neighbors.push_back(to_push);
                i.C += pow((pow(h,2) - pow((distij.norm()),2)),3) * 315 / (64 * PI * pow(h, 9));
                //May be the wrong W, poly6 used // checked and correct
            }
        }
        i.rho = pow(pow(h,2),3.0) * 315/(64*PI*pow(h,9.0));
        i.C = i.C / i.rho - 1;
    }

    //find Lambda
    for (Sphere &i : particle_list){
        i.lambda = 0.0;
        double temp = 0.0;
        Vector3D temp_Gradient;
        // if (find_neighbors(i).size() != i.neighbors.size()) {
        //     cout<<find_neighbors(i).size()<<" "<<i.neighbors.size()<<endl;
        // }
        i.rho    = 15/PI/pow(h,3);

        for (Sphere* j : find_neighbors(i)){
        //for (Sphere* j: i.neighbors) {
            if (j->origin == i.origin)continue; // may exists bug, want to skip i
            Vector3D dist = i.predicted_position - j->predicted_position;
            j->temp_Gradient =  +15/(PI*pow(h,6))*(3*(h-dist.norm()))/i.rho/dist.norm() * dist;
            temp_Gradient += j->temp_Gradient;
            temp += pow((j->temp_Gradient).norm(), 2);
        }
        i.C_Gradient = temp_Gradient;
        temp += pow((i.C_Gradient).norm(),2);
        if (i.C==0){
            i.lambda=0;
        }
        else {
            i.lambda = -i.C / (temp+0.000001);
        }
    }

    for (Sphere &i: particle_list) {
        i.delta_p = i.C_Gradient * i.lambda * 0.000001;

        //perform_Collision_Detection(i); // if collsion, change delta_p;
    }
//
//
    for (Sphere &i: particle_list) {
        //cout << "\ndelta_p2" << i.delta_p << endl;
        i.predicted_position += i.delta_p;
    }

    for (Sphere &sp : particle_list) {
        if (sp.predicted_position.y < 0){
            sp.predicted_position.y = 0;
//    		double rand_direction   = rand()/RAND_MAX*2*PI;
//    		s.predicted_position.x += s.predicted_position.y * cos(rand_direction);
//    		s.predicted_position.z += s.predicted_position.y * sin(rand_direction);
        }
        if (sp.predicted_position.x < -0.2){
            sp.predicted_position.x = -0.2;
        }
        if (sp.predicted_position.x > 0.2){
            sp.predicted_position.x = 0.2;
        }

        sp.velocity = (sp.predicted_position - sp.origin) / delta_t;
        sp.last_origin = sp.origin;
        //cout<<sp.origin<<endl;
        sp.origin = sp.predicted_position;
    }

//    build_spatial_map();
//    for (Sphere &sp : particle_list) {
//        self_collide(sp, simulation_steps);
//    }

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
    Sphere *pm = &particle_list[0];
    for (int i = 0; i < particle_list.size(); i++) {
        pm->origin = pm->start_position;
        pm->last_origin = pm->start_position;
        pm->velocity = Vector3D(0, 0, 0);
        pm++;
    }
}
