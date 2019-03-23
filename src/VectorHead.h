//
//  VectorHead.h
//  VectorMotion
//
//  Created by Apoorva on 06/03/19.
//

#ifndef VectorHead_h
#define VectorHead_h

class Vector {
public:
    float x;
    float y;
    
    Vector(){
        //x = 200;
        //y = 200;
    }
    
    Vector(float x, float y){
        this->x = x;
        this->y = y;
    }
    
    void add(Vector v){
        x = x + v.x;
        y = y + v.y;
    }
    
    void sub(Vector v){
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
    
    void translate(Vector v){
        x=v.x-x;
        y=v.y-y;
    }
    
};

class Food {
public:
    Vector food;
    
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
    Vector location;
    Vector velocity;
    Vector acceleration;
    Vector desired;
    Vector steer;
    Food meal;
    float r;
    float maxforce;
    float maxspeed;
	int eatCount;
	int energy;
	int deathCount;

    VectorHead(float x, float y) {
        acceleration = Vector(0,0);
        velocity = Vector(0,0);
        location = Vector(200,200);
        r = 3.0;
        maxspeed = 2;
        maxforce = 0.1;
		eatCount = 0;
		energy = 1000;
		deathCount = 0;
    }
    
    VectorHead() {
        acceleration = Vector(0,0);
        velocity = Vector(0,0);
        location = Vector(200,200);
        r = 3.0;
        maxspeed = 4;
        maxforce = 0.1;
		eatCount = 0;
		energy = 1000;
		deathCount = 0;
    }
    
	void reset() {
		int x = ofRandom(50, 350);
		int y = ofRandom(50, 350);
		location = Vector(x, y);
	}

    void update() {
        velocity.add(acceleration);
        velocity.limit(maxspeed);
        location.add(velocity);
        acceleration.mul(0);
    }
    
    void applyForce(Vector force) {
            acceleration.add(force);
        }
        
    /*void seek(Vector target) {
        target.sub(location);
        desired= Vector(target.x,target.y);
        desired.normalize();
        desired.mul(maxspeed);
        desired.sub(velocity);
        
        steer= Vector(desired.x,desired.y);
        steer.limit(maxforce);
        applyForce(steer);
        }*/
    
    void arrive(Food &meal){ //arrive at food location
        //(meal.food).sub(location);
		desired = Vector(meal.food.x, meal.food.y);
		desired.sub(location);
        
        if(desired.mag() <= 5){
			energy = energy + 50;
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
        steer= Vector(desired.x,desired.y);
        steer.limit(maxforce);
        applyForce(steer);
    }
	
	void checkEnergy() {
		if (energy <= 0) {
			reset();
			energy = 1000;
			deathCount = deathCount + 1;
		}
	}
        
    void display() {
            float theta = velocity.heading() + PI/2;
       // cout<<theta<<endl;
            //fill(175);
            //stroke(0);
			ofSetColor(int((energy / 10)*255), int((energy/10)*255), 50);
			checkEnergy();
            ofPushMatrix();
            ofTranslate(location.x,location.y);
            ofRotateRad(theta);
            ofDrawTriangle(0,-r*2,-r, r*2,r, r*2);
            ofPopMatrix();

			ofSetColor(100, 100, 100);
			ofDrawBitmapString("Eat Count: " + to_string(eatCount), 10, 30);
			ofDrawBitmapString("Death Count: " + to_string(deathCount), 10, 50);			
			ofDrawBitmapString("Energy: " , 10, 70);
			ofDrawRectangle(70, 60, energy/10 , 10);
	}

};

#endif /* VectorHead_h */
