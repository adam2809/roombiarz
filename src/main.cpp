#include <Arduino.h>
#include "pinout.h"
#include "motors.h"

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
void loop() {
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

	// for (int i=0;i<PROX_SENSOR_COUNT;i++){
	// 	int dist = get_prox(all_prox_sensors[i]);
	// 	Serial.print("Index: ");Serial.print(i);
	// 	Serial.print("\tValue: ");Serial.println(dist);
	// 	if(dist == -1){
	// 		digitalWrite(all_led_pins[i],LOW);
	// 	}else{
	// 		int led_brightness = map(dist,0,MAX_PROX_VALUE,255,50);
	// 		analogWrite(all_led_pins[i],led_brightness);
	// 	}
	// }
	Serial.print("LEFT: ");Serial.print(get_prox(PROX_SENSOR_LEFT));Serial.print(" CENTER: ");Serial.print(get_prox(PROX_SENSOR_CENTER));Serial.print(" RIGHT: ");Serial.print(get_prox(PROX_SENSOR_RIGHT));Serial.println();

}