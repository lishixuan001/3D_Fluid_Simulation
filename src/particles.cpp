#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <cstdio>
#include <ctime>


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
    //origin =Vector3D(-0.09,0.2,-0.09);// This is the origin of the middle sphere of the base layer
    origin =Vector3D(-0.12,0.2,0.12);
    num_length_points = 5;//5;
    num_width_points  = 10;//10;
    num_height_points = 5;//5;

    for (int i=0; i<num_height_points; i++) {
        for (int j=0; j<num_width_points; j++) {
            for (int k=0; k<num_length_points; k++) {
                Sphere sp = Sphere(origin+Vector3D(3*radius*i, 3*radius*j, 3*radius*k), radius, Vector3D(0.0,-1,0.0));
                sp.velocity = Vector3D(0,0,0);
                particle_list.emplace_back(sp);
            }
        }
    }
} 

particles::~particles() {
}
void particles::buildExtraGrid() {
    origin =Vector3D(-0.03,0.55,0.03);
    num_length_points = 3;//5;
    num_width_points  = 3;//10;
    num_height_points = 3;//5;
    
    for (int i=0; i<num_height_points; i++) {
        for (int j=0; j<num_width_points; j++) {
            for (int k=0; k<num_length_points; k++) {
                Sphere sp = Sphere(origin+Vector3D(3*radius*i, 3*radius*j, 3*radius*k), radius, Vector3D(0.0,-10.0,0.0));
                particle_list.emplace_back(sp);
            }
        }
    }
}

void particles::simulate(double frames_per_sec, double simulation_steps, vector<Vector3D> external_forces,
                         vector<CollisionObject *> *collision_objects, int concat, int x, int y, float intensity, int drop) {

    double delta_t = 1.0f / frames_per_sec / simulation_steps ;
    double box_x = 0.5;
    double box_z = 0.5;
    
    double x_NDC = (x - 256.0)/256.0 - 0.00390625;//tune
    double y_NDC = (200.0 - y)/200.0 + 0.17;//tune
    Vector3D mouse_pos = Vector3D(x_NDC,y_NDC,0.0);
    
    
    for (Sphere &sp : particle_list) {
        if (concat)
        {
            sp.velocity += delta_t * (mouse_pos-sp.origin)*intensity;//tune
        }
        
        
        
        for (const Vector3D &external_force : external_forces) {
            if (sp.origin.y>0){
                sp.velocity += delta_t * external_force;
                // only if over the board
            }
            else{
                if (abs(sp.velocity.x)>0){
                    sp.velocity.x = sp.velocity.x / abs(sp.velocity.x) * (abs(sp.velocity.x) + 0.2 * abs(sp.velocity.y))*0.99999;
                    // apply more velocity and friction
                }
                if (abs(sp.velocity.z)>0){
                    sp.velocity.z = sp.velocity.z / abs(sp.velocity.z) * (abs(sp.velocity.z) + 0.2 * abs(sp.velocity.y))*0.99999;
                    // apply more velocity and friction
                }
                sp.velocity.y = 0.0;
            }
        }
        sp.predicted_position   = sp.origin + delta_t * sp.velocity;
        if (sp.last_origin.y == 0 && sp.origin.y == 0) {
            sp.velocity.y = 0;
        }
    }
    
    build_spatial_map();
    h = 2 * 3 * particle_list[0].radius;
    double epsilon = pow(10,-4);//tune
    for (Sphere &i : particle_list){
       i.C = 0.0;
       i.neighbors.clear();
       i.neighbors = find_neighbors(i);
       
       for (Sphere *j: i.neighbors){
           Vector3D distij = (i.predicted_position - j->origin);
           double   r      = distij.norm();
           i.C += pow((pow(h,2.0) - pow(r,2.0)),3.0) * 315.0 / (64.0 * PI * pow(h, 9.0));
       }
       i.rho = pow(pow(h,2.0),3.0) * 315.0/(64.0*PI*pow(h,9.0));
       i.C = i.C / i.rho - 1;
     }
     for (int iter=0;iter<1;iter++){  //<simulation_steps
        //find Lambda
        for (Sphere &i : particle_list){
            i.lambda = 0.0;
            i.C_Gradient =0.0;
            double Sum_Gradient_Squared = 0.0;
            i.rho    = 15/PI/pow(h,3);
            for (Sphere* j : i.neighbors){
                if (j->origin == i.origin)continue; // if origin is the same, gradient will be zero.
                Vector3D dist = i.predicted_position - j->predicted_position;
                double   r    = dist.norm();
                j->temp_Gradient =  45.0/(PI*pow(h,6.0)*i.rho*r)*(pow((h-r),2)) * dist;
                i.C_Gradient -= j->temp_Gradient;
                Sum_Gradient_Squared += pow((j->temp_Gradient).norm(), 2);
            }
            Sum_Gradient_Squared += pow((i.C_Gradient).norm(),2);
            i.lambda = -i.C / (Sum_Gradient_Squared + epsilon);
      }

      for (Sphere &i: particle_list) {
            i.delta_p = Vector3D(0.0,0.0,0.0);
            for (Sphere* j: i.neighbors){
                if (j->origin == i.origin)continue; // if origin is the same, gradient will be zero.
                Vector3D dist = i.predicted_position - j->predicted_position;
                double   r    = dist.norm();
                // Equation(13) k=0.1, delQ = 0.1*h, n=4
                double S_corr = -0.1 * pow ( pow((h*h-r*r)/(h*h),3.0) ,4);//S_corr has to be tuned!
                i.delta_p += ((S_corr+i.lambda+j->lambda) * (-45.0/(PI*pow(h,6.0)*i.rho*r)*(pow((h-r),2)) * dist))*0.3;
            }
            i.delta_p/=i.rho;
            if (i.delta_p.y+i.predicted_position.y<0){
                i.delta_p.y   = -i.predicted_position.y;
            }
            if (i.delta_p.y+i.predicted_position.y>0.7){
                i.delta_p.y   = 0.7-i.predicted_position.y;
            }

            if (i.delta_p.x+i.predicted_position.x>box_x){
                double over   = i.delta_p.x+i.predicted_position.x-box_x;//positive
                i.delta_p.y  += (i.delta_p.x+i.predicted_position.x-box_x)*0.2;
                i.delta_p.x   = (box_x-i.predicted_position.x)+over*(-0.5);
            }
            if (i.delta_p.x+i.predicted_position.x<-box_x){
                double over   = i.delta_p.x+i.predicted_position.x+box_x;//negative
                i.delta_p.y  += abs(i.delta_p.x+i.predicted_position.x+box_x)*0.2;
                i.delta_p.x   = (-box_x-i.predicted_position.x)+over*(0.5);
            }
            if (i.delta_p.z+i.predicted_position.z>box_z){
                double over   = i.delta_p.z+i.predicted_position.z-box_z;//positive
                i.delta_p.y  += (i.delta_p.z+i.predicted_position.z-box_z)*0.2;
                i.delta_p.z   = (box_z-i.predicted_position.z)+over*(-0.5);
            }
            if (i.delta_p.z+i.predicted_position.z<-box_z){
                double over   = i.delta_p.z+i.predicted_position.z+box_z;//negative
                i.delta_p.y  += (abs(i.delta_p.z+i.predicted_position.z+box_z))*0.2;
                i.delta_p.z   = (-box_z-i.predicted_position.z)+over*(0.5);
            }
        }
        for (Sphere &i: particle_list) {
            i.predicted_position += i.delta_p;
        }
    }
    
    for (Sphere &i: particle_list) {
        // Now apply Vorticity Confinement
        Vector3D omega = Vector3D(0.0,0.0,0.0);
        for (Sphere* j:i.neighbors){
            Vector3D dist = i.predicted_position - j->predicted_position;
            double   r    = dist.norm();
            j->temp_Gradient =  45.0/(PI*pow(h,6.0)*i.rho*r)*(pow((h-r),2)) * dist;
            omega += cross((j->velocity-i.velocity) , j->temp_Gradient);
        }
        
        i.last_origin = i.origin;
        i.origin = i.predicted_position;
        i.velocity = (i.origin-i.last_origin)/delta_t;
        //Add viscosity
        Vector3D viscosity;
        for (Sphere* j : i.neighbors){
            if (j->origin == i.origin)continue; // if origin is the same, gradient will be zero.
            Vector3D dist =  i.predicted_position - j->predicted_position;
            double   r    =  dist.norm();
            viscosity    += (j->velocity-i.velocity) * pow((pow(h,2.0) - pow(r,2.0)),3.0) * 315.0 / (64.0 * PI * pow(h, 9.0));
        }
        i.velocity += 0.0000001 * viscosity;//tune
    }
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



vector<Sphere*> particles::find_neighbors(Sphere &sp) {
    vector<Sphere*> res;
    float pos = 10000*floor(sp.origin.x/h)+100*floor(sp.origin.y/h)+floor(sp.origin.z/h);
    for (int i = -1; i <= 1; i++) {
        for (int j =-1; j <= 1; j++) {
            for (int k=-1; k <= 1; k++) {
                float updated = pos+10000*i+100*j+k;
                if (map.find(updated) != map.end()) {
                    for (Sphere *sp2: *map[updated]) {
                        if (pow(sp.origin.x-sp2->origin.x, 2)+pow(sp.origin.y-sp2->origin.y, 2)+pow(sp.origin.z-sp2->origin.z, 2)<=h*h) {
                            res.push_back(sp2);
                        }
                    }
                }
            }
        }
    }
    return res;
}

void particles::build_spatial_map() {
    for (const auto &entry : map) {
        delete(entry.second);
    }
    map.clear();
    // TODO (Part 4.2): Build a spatial map out of all of the point masses.
    for (Sphere &sp : particle_list) {
        float pos = 10000*floor(sp.origin.x/h)+100*floor(sp.origin.y/h)+floor(sp.origin.z/h);
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

