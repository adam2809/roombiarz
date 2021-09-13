#include "Arduino.h"
#include "pinout.h"
#include "motors.h"

void set_motor_forward(motor_t motor){
	if (motor == MOTOR_A){
		digitalWrite(IN1_DRIVER_PIN, HIGH);
		digitalWrite(IN2_DRIVER_PIN, LOW);
	}else{
		digitalWrite(IN3_DRIVER_PIN, HIGH);
		digitalWrite(IN4_DRIVER_PIN, LOW);
	}
}


void set_motor_backward(motor_t motor){
	if (motor == MOTOR_A){
		digitalWrite(IN1_DRIVER_PIN, LOW);
		digitalWrite(IN2_DRIVER_PIN, HIGH);
	}else{
		digitalWrite(IN3_DRIVER_PIN, LOW);
		digitalWrite(IN4_DRIVER_PIN, HIGH);
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

void go_forward(){
	set_motor_forward(MOTOR_A);
	set_motor_forward(MOTOR_B);
}

void stop(){
	set_motor_stopped(MOTOR_A);
	set_motor_stopped(MOTOR_B);
}

void set_motor_speed(motor_t motor,int speed){
	if (motor == MOTOR_A){
		analogWrite(ENA_DRIVER_PIN,speed);
	}else{
		analogWrite(ENB_DRIVER_PIN,speed);
	}
}