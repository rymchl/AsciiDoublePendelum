#include <stdio.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <math.h>
#include "screen.h"

double t, th1, th2, dth1, dth2, ddth1, ddth2;
int  m1x, m1y, m2x, m2y, px, py;

double pi = 3.14159265358979323846;
float g = 9.81;
float L1 = 21;
float L2 = 20;
float m1 = 10;
float m2 = 13;
float th0;

void draw_m(){


	screen[py][px] = 'O';
	
	screen[py + m1y][px + m1x] = '@';

	if(!(px + m2x < 0 || px + m2x > width || py + m2y < 0 || py + m2y >= height)){
		screen[py + m2y][px + m2x] = '@';
	}
}

void set_m_pos(){

	m1x = int(L1 * cos(pi/2 - th1));
	m1y = int(L1 * sin(pi/2 - th1));

	m2x = m1x +  int(L2 * cos(pi/2 - th2));
	m2y = m1y + int(L2 * sin(pi/2 - th2));
	
}


int main(int argc, char** argv){
	
	init_screen();

    if(argc == 5){
        L1 = atoi(argv[1]);
        L2 = atoi(argv[2]);
        m1 = atoi(argv[3]);
        m1 = atoi(argv[4]);
    }

    px = int(width/2);
    py = int(height/4);
    th1 = pi/2;
    th2 = pi/2;
	double dt = 0.1;
	double damp = 1;
	while(1){
		set_m_pos();
		clear_screen();
		draw_line(px, py+1, px+m1x, py+m1y-1);
		draw_line(px+m1x, py+m1y+1, px+m2x, py+m2y-1);
		draw_m();
		print_screen();
		
		
		double a, b, c, d;

		a = -g*(2*m1 + m2)*sin(th1);
		b = m2*g*sin(th1-2*th2);
		c = 2*sin(th1-th2)*m2*(dth2*dth2*L2+dth1*dth1*L1*cos(th1-th2));
		d = L1*(2*m1+m2-m2*cos(2*th1-2*th2));

		if(d!=0) ddth1 = damp*(a-b-c)/d;

		a = 2*sin(th1-th2);
		b = dth2*dth2*L1*(m1+m2) + g*(m1+m2)*cos(th1);
		c = dth2*dth2*L2*m2*cos(th1-th1);
		d = L2*(2*m1+m2-m2*cos(2*th1-2*th2));

		if(d!=0) ddth2 = damp*a*(b+c)/d;

		dth1 += dt*ddth1;
		dth2 += dt*ddth2;

		th1 += dth1;	
		th2 += dth2;
	
		usleep(100000);
	}
	
	return 0;
}
