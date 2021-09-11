#include <Arduino.h>
#include "pinout.h"

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

void loop() {
	digitalWrite(ENA_DRIVER_PIN, HIGH);

	Serial.println("Motor Forward");
	set_motor_forward(MOTOR_A);
	delay(2000);

	Serial.println("Motor stopped");	
	set_motor_stopped(MOTOR_A);
	delay(2000);

	Serial.println("Motor backward");	
	set_motor_backward(MOTOR_A);
	delay(2000);

}