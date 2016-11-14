/*
 * controller.c
 *
 * Created: 14.11.2016 12:02:01
 *  Author: audunel
 */ 

float Kp, Ki, Kd;
float reference;
float prev_err;
float integral;

void CONTROLLER_init() {
	Kp = 1.0;
	Ki = 1.0;
	Kd = 0.0;
}

void CONTROLLER_set_reference(float r) {
	reference = r;
}