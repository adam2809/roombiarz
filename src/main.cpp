#include <Arduino.h>
#include "pinout.h"
#include "motors.h"
#include "prox_sensor.cpp"

#define DEADZONE_MIN 250
#define DEADZONE_MAX 770

#define MAX_WHEELS_SPEED_DIFFERENCE 127

prox_sensor_led_pin_t all_led_pins[] = {
    PROX_SENSOR_LED_CENTER,
    PROX_SENSOR_LED_RIGHT,
    PROX_SENSOR_LED_LEFT
};
prox_sensor prox_sensor_center = prox_sensor(PROX_SENSOR_CENTER);
prox_sensor prox_sensor_right = prox_sensor(PROX_SENSOR_RIGHT);
prox_sensor prox_sensor_left = prox_sensor(PROX_SENSOR_LEFT);
prox_sensor all_prox_sensors[] = {
	prox_sensor_center,
	prox_sensor_right,
	prox_sensor_left
};

void setup_driver_pins(){
	pinMode(ENA_DRIVER_PIN, OUTPUT);
	pinMode(ENB_DRIVER_PIN, OUTPUT);
	pinMode(IN1_DRIVER_PIN, OUTPUT);
	pinMode(IN2_DRIVER_PIN, OUTPUT);
	pinMode(IN3_DRIVER_PIN, OUTPUT);
	pinMode(IN4_DRIVER_PIN, OUTPUT);
	
	digitalWrite(IN1_DRIVER_PIN, LOW);
	digitalWrite(IN2_DRIVER_PIN, LOW);
	digitalWrite(IN3_DRIVER_PIN, LOW);
	digitalWrite(IN4_DRIVER_PIN, LOW);

	digitalWrite(ENA_DRIVER_PIN, LOW);
	digitalWrite(ENB_DRIVER_PIN, LOW); 
}

void setup_led_pins(){
	for (prox_sensor_led_pin_t pin : all_led_pins){
		pinMode(pin, OUTPUT);
	}
}

void setup() {  
	Serial.begin(9600); 

	setup_led_pins();
	setup_driver_pins();

	set_both_motor_speed(255);
}


long last_move_millis = 0;
long move_interval_millis = 1000;
bool is_moving = false;

void go_forward_and_stop(){
	if (millis() - last_move_millis > move_interval_millis){
		last_move_millis = millis();
		if (is_moving){
			Serial.println("Stopping");
			rotate_left();
			is_moving = false;
		}else{
			Serial.println("Moving forward");
			rotate_right();
			is_moving = true;
		}
	}
}

void joystick_control(){
	int x_joystick = analogRead(X_AXIS);
	int y_joystick = analogRead(Y_AXIS);

	Serial.print("Y: ");Serial.print(y_joystick);Serial.print(" X: ");Serial.print(x_joystick);Serial.println();

	if(x_joystick < DEADZONE_MAX && x_joystick > DEADZONE_MIN){
		stop();
	}else if(x_joystick >= DEADZONE_MAX){
		go_backward();
		return;
	}else if(x_joystick <= DEADZONE_MIN){
		go_forward();
		return;
	}

	int wheels_speed_difference;
	if(y_joystick < DEADZONE_MAX && y_joystick > DEADZONE_MIN){
		stop();
	}else if(y_joystick >= DEADZONE_MAX){
		turn_left();
	}else if(y_joystick <= DEADZONE_MIN){
		// wheels_speed_difference=map(y_joystick,0,1024/2,MAX_WHEELS_SPEED_DIFFERENCE,0);
		turn_right();
	}
}
bool is_wall_in_any_sensor_proximity(){
	for(prox_sensor sensor : all_prox_sensors){
		if (sensor.is_wall_in_prox()){
			return true;
		}
	}
	return false;
}

enum wall_detected_t{
	NO_WALL,
	LEFT_WALL,
	RIGHT_WALL
};
wall_detected_t wall_detected = NO_WALL; 
void stick_to_wall_basic(){
	if(!is_wall_in_any_sensor_proximity()){
		switch (wall_detected){
		case NO_WALL:
			go_forward();
			break;
		case LEFT_WALL:
			turn_left();
			break;
		case RIGHT_WALL:
			turn_right();
			break;
		}
	}else{
		if (
			(prox_sensor_center.is_wall_in_prox() && ((!prox_sensor_right.is_wall_in_prox() && !prox_sensor_left.is_wall_in_prox()) || (prox_sensor_right.is_wall_in_prox() && prox_sensor_left.is_wall_in_prox()))) ||
			(!prox_sensor_center.is_wall_in_prox() && prox_sensor_right.is_wall_in_prox() && prox_sensor_left.is_wall_in_prox())
		){
			turn_left();
		}else if (prox_sensor_right.is_wall_in_prox() && prox_sensor_center.is_wall_in_prox()){
			turn_left();
			wall_detected = RIGHT_WALL;
		}else if (prox_sensor_left.is_wall_in_prox() && prox_sensor_center.is_wall_in_prox()){
			turn_right();
			wall_detected = LEFT_WALL;
		}else if (prox_sensor_right.is_wall_in_prox()){
			turn_right();
			wall_detected = RIGHT_WALL;
		}else if (prox_sensor_left.is_wall_in_prox()){
			turn_left();
			wall_detected = LEFT_WALL;
		}else{
			Serial.println("Logic has a hole!!!!!!!!!");
		}
	}
}

void find_wall(){

}

void loop() {
	Serial.print("LEFT: ");Serial.print(all_prox_sensors[2].get_prox_filtered());Serial.print(" CENTER: ");Serial.print(all_prox_sensors[0].get_prox_filtered());Serial.print(" RIGHT: ");Serial.print(all_prox_sensors[1].get_prox_filtered());
	// stick_to_wall_basic();
	go_forward_and_stop();

	switch (wall_detected){
	case NO_WALL:
		Serial.print("	NO_WALL");
		break;
	case LEFT_WALL:
		Serial.print("	LEFT_WALL");
		break;
	case RIGHT_WALL:
		Serial.print("	RIGHT_WALL");
		break;
	}
	Serial.println();
}