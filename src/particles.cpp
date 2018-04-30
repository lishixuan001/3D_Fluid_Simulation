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
    this->num_width_points = 5;//num_width_points;
    this->num_height_points = 5;//num_height_points;
    this->num_length_points = 5;//num_length_points;
    this->radius = radius;
    this->friction = friction;
    this->origin = Vector3D(0, 0, 0);
    this->bounce_rate = 0.8;
    this->x_bounce = 0.35;
    this->z_bounce = 0.35;
    this->y_bounce = 0;
//  buildGrid();
}

void particles::buildGrid() {
    origin =Vector3D(-0.06,0.2,-0.06);
    num_length_points = 5;
    num_width_points  = 5;
    num_height_points = 5;
    bounce_rate = 0.8;
    x_bounce = 0.35;
    z_bounce = 0.35;
    y_bounce = 0;

    for (int i=0; i<num_height_points; i++) {
        for (int j=0; j<num_width_points; j++) {
            for (int k=0; k<num_length_points; k++) {
                Sphere sp = Sphere(origin+Vector3D(3*radius*i, 3*radius*j, 3*radius*k), radius, friction);
                sp.velocity = Vector3D(0,0,0);
                particle_list.emplace_back(sp);
                //cout<<sp.origin<<endl;
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
        sp.predicted_position   = sp.origin + delta_t * sp.velocity;
        if (sp.last_origin.y == 0 && sp.origin.y == 0) {
            sp.velocity.y = 0;
        }

    }


    // Brute force finding neighbor and find C
    // Set h=0.02, with r=0.01, m = 1
    double h = 2 * 3 * particle_list[0].radius;
    double epsilon = pow(10,-10);
    for (Sphere &i : particle_list){
        //cout<<i.origin<<endl;
        i.C = 0.0;
        i.neighbors.clear();
        for (Sphere &j: particle_list){
            Vector3D distij = (i.predicted_position - j.origin);
            double   r      = distij.norm();
            if ( r < h){
                Sphere* to_push = &j;
                i.neighbors.push_back(&j);
                i.C += pow((pow(h,2.0) - pow(r,2.0)),3.0) * 315.0 / (64.0 * PI * pow(h, 9.0));
            }
        }
        i.rho = pow(pow(h,2.0),3.0) * 315.0/(64.0*PI*pow(h,9.0));
        i.C = i.C / i.rho - 1;
        //cout<<i.C<<"~~!"<<endl;
    }
    //cout<<endl;
    

    for (int iter=0;iter<1;iter++){  //<simulation_steps
        //find Lambda
        for (Sphere &i : particle_list){
            i.lambda = 0.0;
            i.C_Gradient =0.0;
            double Sum_Gradient_Squared = 0.0;
            i.rho    = 15/PI/pow(h,3);
            for (Sphere* j : i.neighbors){
                //cout<<i.origin<<" and j: "<<j->origin<<endl;
                if (j->origin == i.origin)continue; // if origin is the same, gradient will be zero.
                Vector3D dist = i.predicted_position - j->predicted_position;
                double   r    = dist.norm();
                j->temp_Gradient =  -45.0/(PI*pow(h,6.0)*i.rho*r)*(pow((h-r),2)) * dist;
                i.C_Gradient -= j->temp_Gradient;
                Sum_Gradient_Squared += pow((j->temp_Gradient).norm(), 2);
            }
            Sum_Gradient_Squared += pow((i.C_Gradient).norm(),2);
            i.lambda = -i.C / (Sum_Gradient_Squared + epsilon);

            //cout<<i.origin<<" "<<i.lambda<<" t: "<<i.C_Gradient<<endl;
        }

        for (Sphere &i: particle_list) {
            //i.delta_p = i.C_Gradient * i.lambda;
            i.delta_p = Vector3D(0.0,0.0,0.0);
            for (Sphere* j: i.neighbors){
                if (j->origin == i.origin)continue; // if origin is the same, gradient will be zero.
                Vector3D dist = i.predicted_position - j->predicted_position;
                double   r    = dist.norm();
                i.delta_p += (i.lambda+j->lambda) * (-45.0/(PI*pow(h,6.0)*i.rho*r)*(pow((h-r),2)) * dist);
            }
            i.delta_p/=i.rho;
            //cout<<"delta p!! "<<i.delta_p<<endl;
            if (i.delta_p.y+i.predicted_position.y<0){
                //double change = i.delta_p.norm();
                i.delta_p.y   = -i.predicted_position.y; //thus final y is 0
            }
            if (i.delta_p.y+i.predicted_position.y>0.5){
                //double change = i.delta_p.norm();
                i.delta_p.y   = 0.5-i.predicted_position.y; //thus final y is 0
            }
            if (i.delta_p.x+i.predicted_position.x>0.1){
                i.delta_p.x   = 0.1-i.predicted_position.x; //thus final y is 0
            }
            if (i.delta_p.x+i.predicted_position.x<-0.1){
                i.delta_p.x   = -0.1-i.predicted_position.x; //thus final y is 0
            }
            if (i.delta_p.z+i.predicted_position.z>0.1){
                i.delta_p.z   = 0.1-i.predicted_position.z; //thus final y is 0
            }
            if (i.delta_p.z+i.predicted_position.z<-0.1){
                i.delta_p.z   = -0.1-i.predicted_position.z; //thus final y is 0
            }
            //perform_Collision_Detection(i); // if collsion, change delta_p;
        }
        for (Sphere &i: particle_list) {
            i.predicted_position += i.delta_p*0.02;
        }
    }
    //cout<<endl<<endl;
    
    for (Sphere &sp: particle_list) {
        sp.last_origin = sp.origin;
        sp.origin = sp.predicted_position;
        sp.velocity = (sp.origin-sp.last_origin)/delta_t;
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

