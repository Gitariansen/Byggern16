/*
 * controller.h
 *
 * Created: 14.11.2016 12:01:50
 *  Author: audunel
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

void CONTROLLER_set_reference(float ref);
float CONTROLLER_actuate(float y);

#endif /* CONTROLLER_H_ */