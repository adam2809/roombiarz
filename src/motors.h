#ifndef MOTORS_H
#define MOTORS_H

enum motor_t{
	MOTOR_A,
	MOTOR_B
};

void set_motor_forward(motor_t motor);
void set_motor_backward(motor_t motor);
void set_motor_stopped(motor_t motor);
void go_forward();
void go_backward();
void rotate_left();
void rotate_right();
void stop();
void set_motor_speed(motor_t motor,int speed);
void set_both_motor_speed(int speed);

#endif