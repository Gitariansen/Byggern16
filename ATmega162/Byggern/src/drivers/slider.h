/*
 * IncFile1.h
 *
 * Created: 21.09.2016 09:31:14
 *  Author: elsala
 */ 


#ifndef SLIDER_H_
#define SLIDER_H_

typedef struct {
	int left;
	int right;
} slider_position_t;

void SLIDER_init();
int SLIDER_compare();
slider_position_t SLIDER_get_position();

#endif /* SLIDER_H_ */