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
    origin =Vector3D(-0.09,0.2,-0.09);
    num_length_points = 3;
    num_width_points  = 1;
    num_height_points = 3;
    bounce_rate = 0.8;
    x_bounce = 0.35;
    z_bounce = 0.35;
    y_bounce = 0;

    for (int i=0; i<num_height_points; i++) {
        for (int j=0; j<num_width_points; j++) {
            for (int k=0; k<num_length_points; k++) {
                Sphere sp = Sphere(origin+Vector3D(3*radius*i, 3*radius*j, 3*radius*k), radius, friction, Vector3D(0.0,-1,0.0));
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

    double delta_t = 1.0f / 90.0 / 30.0 ;
    double box_x = 0.35;
    double box_z = 0.35;
    
    //timing
    std::clock_t start;
    double duration;
    
    start = std::clock();
    
    //
    
    for (Sphere &sp : particle_list) {
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
        //cout<<sp.origin<<"     "<<sp.velocity<<endl;
    }
    
    build_spatial_map();


    // Brute force finding neighbor and find C
    // Set h=0.02, with r=0.01, m = 1
    double h = 2 * 3 * particle_list[0].radius;
    double epsilon = pow(10,-3);
    for (Sphere &i : particle_list){
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
    }
//    for (Sphere &i : particle_list){
//        i.C = 0.0;
//        i.neighbors.clear();
//        i.neighbors = find_neighbors(i);
//        
//        for (Sphere *j: i.neighbors){
//            Vector3D distij = (i.predicted_position - j->origin);
//            double   r      = distij.norm();
//            i.C += pow((pow(h,2.0) - pow(r,2.0)),3.0) * 315.0 / (64.0 * PI * pow(h, 9.0));
//        }
//        i.rho = pow(pow(h,2.0),3.0) * 315.0/(64.0*PI*pow(h,9.0));
//        i.C = i.C / i.rho - 1;
//    }
//    
    
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
    //std::cout<<"printf: "<< duration <<'\n';
    

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
                
                // Equation(13) k=0.1, delQ = 0.1*h, n=4
                double S_corr = -0.1 * pow ( pow((h*h-r*r)/(h*h),3.0) ,4);
                //cout<<S_corr<<endl;
                //cout<<i.lambda<< "  ?  "<<j->lambda<<endl;
                //S_corr has to be tuned!
                
                i.delta_p += ((S_corr+i.lambda+j->lambda) * (-45.0/(PI*pow(h,6.0)*i.rho*r)*(pow((h-r),2)) * dist))*0.5;
            }
            i.delta_p/=i.rho;
            //cout<<i.origin<<"  \nC: "<<i.C<<" \n lambda:  "<<i.lambda<<"\ndelta p!! "<<i.delta_p<<"  \nv: "<<i.velocity<<endl<<endl;
            //cout<<i.velocity<<endl;
            if (i.delta_p.y+i.predicted_position.y<0){
                //double change = i.delta_p.norm();
                i.delta_p.y   = -i.predicted_position.y;
            }
            if (i.delta_p.y+i.predicted_position.y>0.5){
                //double change = i.delta_p.norm();
                i.delta_p.y   = 0.5-i.predicted_position.y;
            }
            if (i.delta_p.x+i.predicted_position.x>box_x){
                i.delta_p.y  += (i.delta_p.x+i.predicted_position.x-box_x)*0.2;
                i.delta_p.x   = box_x-i.predicted_position.x;
            }
            if (i.delta_p.x+i.predicted_position.x<-box_x){
                i.delta_p.y  += abs(i.delta_p.x+i.predicted_position.x+box_x)*0.2;
                i.delta_p.x   = -box_x-i.predicted_position.x;
            }
            if (i.delta_p.z+i.predicted_position.z>box_z){
                i.delta_p.y  += (i.delta_p.z+i.predicted_position.z-box_z)*0.2;
                i.delta_p.z   = box_z-i.predicted_position.z;
            }
            if (i.delta_p.z+i.predicted_position.z<-box_z){
                i.delta_p.y  += (abs(i.delta_p.z+i.predicted_position.z+box_z))*0.2;
                i.delta_p.z   = -box_z-i.predicted_position.z;
            }
            //perform_Collision_Detection(i); // if collsion, change delta_p;
        }
        //cout<<endl<<endl;
        for (Sphere &i: particle_list) {
            i.predicted_position += i.delta_p;
        }
    }
    //cout<<endl<<endl;
    
    for (Sphere &i: particle_list) {
        // Now apply Vorticity Confinement and Viscosity!!! So excited!!
        Vector3D omega = Vector3D(0.0,0.0,0.0);
        for (Sphere* j:i.neighbors){
            Vector3D dist = i.predicted_position - j->predicted_position;
            double   r    = dist.norm();
            j->temp_Gradient =  -45.0/(PI*pow(h,6.0)*i.rho*r)*(pow((h-r),2)) * dist;
            omega += cross((j->velocity-i.velocity) , j->temp_Gradient);
        }
        // to be continued.... Sleep now
        
        
        i.last_origin = i.origin;
        i.origin = i.predicted_position;
        i.velocity = (i.origin-i.last_origin)/delta_t;
        //cout<<i.origin<<" "<<i.last_origin<<" "<<i.velocity<<endl;
    }
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
    //std::cout<<"printf: end "<< duration <<'\n';


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

vector<Sphere*> particles::find_neighbors(Sphere &sp) {
    vector<Sphere*> res;
    float pos = 21600*floor(sp.origin.x/6/radius)+100*floor(sp.origin.y/6/radius)+floor(sp.origin.z/6/radius);
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
    cout<<res.size()<<endl;
    return res;
}

void particles::build_spatial_map() {
    for (const auto &entry : map) {
        delete(entry.second);
    }
    map.clear();
    // TODO (Part 4.2): Build a spatial map out of all of the point masses.
    for (Sphere &sp : particle_list) {
        float pos = 21600*floor(sp.origin.x/6/radius)+100*floor(sp.origin.y/6/radius)+floor(sp.origin.z/6/radius);
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
}

