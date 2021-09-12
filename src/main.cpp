#include <Arduino.h>
#include "pinout.h"
namespace prox_sensor_led_pin{
    enum pin_t{
        PROX_SENSOR_LED_CENTER = 8,
        PROX_SENSOR_LED_RIGHT = 9,
        PROX_SENSOR_LED_LEFT = 10
    };

    static const pin_t all[] = { 
        PROX_SENSOR_LED_CENTER,
        PROX_SENSOR_LED_RIGHT,
        PROX_SENSOR_LED_LEFT 
    };
}
enum motor_t{
	MOTOR_A,
	MOTOR_B
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

void setup() {  
	Serial.begin(9600); 

	setup_driver_pins();
}

void set_motor_forward(motor_t motor){
	if (motor == MOTOR_A){
		digitalWrite(IN1_DRIVER_PIN, LOW);
		digitalWrite(IN2_DRIVER_PIN, HIGH);
	}else{
		digitalWrite(IN3_DRIVER_PIN, LOW);
		digitalWrite(IN4_DRIVER_PIN, HIGH);
	}
}


void set_motor_backward(motor_t motor){
	if (motor == MOTOR_A){
		digitalWrite(IN1_DRIVER_PIN, HIGH);
		digitalWrite(IN2_DRIVER_PIN, LOW);
	}else{
		digitalWrite(IN3_DRIVER_PIN, HIGH);
		digitalWrite(IN4_DRIVER_PIN, LOW);
	}
}

void set_motor_stopped(motor_t motor){
	if (motor == MOTOR_A){
		digitalWrite(IN1_DRIVER_PIN, LOW);
		digitalWrite(IN2_DRIVER_PIN, LOW);
	}else{
		digitalWrite(IN3_DRIVER_PIN, LOW);
		digitalWrite(IN4_DRIVER_PIN, LOW);
	}
}

void set_motor_speed(motor_t motor,int speed){
	if (motor == MOTOR_A){
		analogWrite(ENA_DRIVER_PIN,speed);
	}else{
		analogWrite(ENB_DRIVER_PIN,speed);
	}
	
}

int get_prox(prox_sensor_pin_t pin){
	float volts = analogRead(pin)*0.0048828125;
	int distance = 13*pow(volts, -1); 
    return distance <= MAX_PROX_VALUE ? distance : -1;
}

void loop() {
	for (int i=0;i<PROX_SENSOR_COUNT;i++){
		int dist = get_prox(all_prox_sensors[i]);
		if(dist == -1){
			digitalWrite(all_led_pins[i],LOW);
		}else{
			int led_brightness = map(dist,0,MAX_PROX_VALUE,255,50);
			analogWrite(all_led_pins[i],led_brightness);
		}
	}
	Serial.println(get_prox(PROX_SENSOR_CENTER));
}