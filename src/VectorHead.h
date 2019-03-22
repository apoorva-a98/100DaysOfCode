//
//  VectorHead.h
//  VectorMotion
//
//  Created by Apoorva on 06/03/19.
//

#ifndef VectorHead_h
#define VectorHead_h

class PVector {
public:
    float x;
    float y;
    
    PVector(){
        //x = 200;
        //y = 200;
    }
    
    PVector(float x, float y){
        this->x = x;
        this->y = y;
    }
    
    void add(PVector v){
        x = x + v.x;
        y = y + v.y;
    }
    
    void sub(PVector v){
        x = x - v.x;
        y = y - v.y;
    }
    void mul(float m){
        x = x * m;
        y = y * m;
    }
    void div(float m){
        x = x / m;
        y = y / m;
    }
    
    float mag(){
        return sqrt((x*x)+(y*y));
    }
    
    void normalize(){
        float m = mag();
        if (mag() != 0){
            div(m);
        }
    }
    
    void set_magnitude(float m){
        normalize();
        mul(m);
    }
    
    void limit(float max) {
        if (mag()>max)
        {
            set_magnitude(max);
        }
    }
    
    float heading(){
       return atan2(y,x);
    }
    
    void translate(PVector v){
        x=v.x-x;
        y=v.y-y;
    }
    
};

class Food {
public:
    PVector food;
    
    void display() {
        ofSetColor(255, 0, 0);
        ofDrawCircle(food.x, food.y, 5, 5);
    }
    
    void reset() {
        food.x = ofRandom(50, 350);
        food.y = ofRandom(50, 350);
    }
    
    int get_r() {
        return food.x;
    }
    
    int get_y() {
        return food.y;
    }
    
    Food() {
        food.x = int(ofRandom(50, 350));
        food.y = int(ofRandom(50, 350));
    }
};

class VectorHead {
public:
    PVector location;
    PVector velocity;
    PVector acceleration;
    PVector desired;
    PVector steer;
    Food meal;
    float r;
    float maxforce;
    float maxspeed;
	int eatCount;

    VectorHead(float x, float y) {
        acceleration = PVector(0,0);
        velocity = PVector(0,0);
        location = PVector(200,200);
        r = 3.0;
        maxspeed = 2;
        maxforce = 0.1;
		eatCount = 0;
    }
    
    VectorHead() {
        acceleration = PVector(0,0);
        velocity = PVector(0,0);
        location = PVector(200,200);
        r = 3.0;
        maxspeed = 4;
        maxforce = 0.1;
		eatCount = 0;
    }
    
    void update() {
        velocity.add(acceleration);
        velocity.limit(maxspeed);
        location.add(velocity);
        acceleration.mul(0);
    }
    
    void applyForce(PVector force) {
            acceleration.add(force);
        }
        
    /*void seek(PVector target) {
        target.sub(location);
        desired= PVector(target.x,target.y);
        desired.normalize();
        desired.mul(maxspeed);
        desired.sub(velocity);
        
        steer= PVector(desired.x,desired.y);
        steer.limit(maxforce);
        applyForce(steer);
        }*/
    
    void arrive(Food &meal){ //arrive at food location
        //(meal.food).sub(location);
		desired = PVector(meal.food.x, meal.food.y);
		desired.sub(location);
        
        if(desired.mag() <= 5){
            meal.reset();
            eatCount++;
        }
       
        float d = desired.mag();
        desired.normalize();
        if (d < 100) {
            float m = ofMap(d,0,100,0,maxspeed);
            desired.mul(m);
        } else {
            desired.mul(maxspeed);
        }

        desired.sub(velocity);
        steer= PVector(desired.x,desired.y);
        steer.limit(maxforce);
        applyForce(steer);
    }
	
        
    void display() {
            float theta = velocity.heading() + PI/2;
       // cout<<theta<<endl;
            //fill(175);
            //stroke(0);
            ofPushMatrix();
            ofTranslate(location.x,location.y);
            ofRotateRad(theta);
            ofDrawTriangle(0,-r*2,-r, r*2,r, r*2);
            ofPopMatrix();
        ofDrawBitmapString("Eat Count: " + to_string(eatCount), 10, 30);

			
	}

};

#endif /* VectorHead_h */
