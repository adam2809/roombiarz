#include <Arduino.h>
#include "pinout.h"
#include "motors.h"

#define DEADZONE_MIN 250
#define DEADZONE_MAX 770

#define MAX_WHEELS_SPEED_DIFFERENCE 127

prox_sensor_led_pin_t all_led_pins[] = {
    PROX_SENSOR_LED_CENTER,
    PROX_SENSOR_LED_RIGHT,
    PROX_SENSOR_LED_LEFT
};

prox_sensor_pin_t all_prox_sensors[] = {
    PROX_SENSOR_CENTER,
    PROX_SENSOR_RIGHT,
    PROX_SENSOR_LEFT
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

	set_motor_speed(MOTOR_A,255);
	set_motor_speed(MOTOR_B,255);
}

int get_prox(prox_sensor_pin_t pin){
	float volts = analogRead(pin)*0.0048828125;
	int distance = 13*pow(volts, -1); 
    return distance <= MAX_PROX_VALUE ? distance : -1;
}

long last_move_millis = 0;
long move_interval_millis = 1000;
bool is_moving = false;

void go_forward_and_stop(){
	if (millis() - last_move_millis > move_interval_millis){
		last_move_millis = millis();
		if (is_moving){
			Serial.println("Stopping");
			stop();
			is_moving = false;
		}else{
			Serial.println("Moving forward");
			go_forward();
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
		rotate_left();
	}else if(y_joystick <= DEADZONE_MIN){
		// wheels_speed_difference=map(y_joystick,0,1024/2,MAX_WHEELS_SPEED_DIFFERENCE,0);
		rotate_right();
	}
}

void loop() {
	Serial.print("LEFT: ");Serial.print(get_prox(PROX_SENSOR_LEFT));Serial.print(" CENTER: ");Serial.print(get_prox(PROX_SENSOR_CENTER));Serial.print(" RIGHT: ");Serial.print(get_prox(PROX_SENSOR_RIGHT));Serial.println();
	bool is_wall_in_proximity = false;
	for(int i = 0; i < PROX_SENSOR_COUNT; i++){
		int prox = get_prox(all_prox_sensors[i]);
		if(prox < 20 && prox != -1){
			is_wall_in_proximity = true;
		}
	}
	if (is_wall_in_proximity){
		rotate_left();
	}else{
		go_forward();
	}
	
}