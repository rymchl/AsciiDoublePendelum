#include <sys/ioctl.h>
#include <iostream>
#include <vector>
#include <unistd.h>
std::vector< std::string > screen;
struct winsize size;
double width,height;

void init_screen(){

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    height = size.ws_row;
    width = size.ws_col;
    
    for(int y = 0; y < height; y++){
        screen.push_back("");
        for(int x = 0; x < width; x++){
            screen[y] += ' ';
        }
    }
}

void print_screen(){
    for(int i = 0; i < (int)screen.size(); i++){
        std::cout << screen[i] << "\n";
    }
}
void clear_screen(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            screen[i][j] = ' ';
        }
    }
}

void draw_line(int x1,int y1,int x2,int y2){

	if(x1 < 0 || x2 < 0 || x1 >= width || x2 >= width){
		printf("C1\n");
		return;
	}
	if(y1 < 0 || y2 < 0 || y1 >= height || y2 >= height){
		printf("C2\n");
		return;
	}

	int xs, ys, xe, ye;

	//vertical
	if(x1 == x2){
		//same point
		if(y1 == y2){
			printf("C3\n");
			return;
		}

		ys = y1;
		ye = y2;
		if(y2 < y1)	ys = y2, ye = y1;
		while(ys <= ye){
			screen[ys][x1] = '.';	
			ys++;
		}	
		return;
	}

	//horizontal

	if(y1 == y2){
		xs = x1;
		xe = x2;
		if(x1 > x2) xe = x1, xs = x2;
		while(xs <= xe){
			screen[y1][xs] = '.';
			xs++;
		}
		return;
	}

	//diagonal
	

	if(y1 > y2){
		ys = y2, ye = y1;
		xs = x2, xe = x1;

	}
	else{
		xs = x1, xe = x2;
		ys = y1, ye = y2;
	}

	double m = double(ye-ys)/(xe-xs);

	//ye > ys & ye lower than ys

	int itr = 1;
	if(m < 0) itr = -1;
	int x = xs, y = ys;
	//shallow
	if(-1 < m && m < 1){
		m = (1/abs(m));
		while(y < ye){
			for(double i = 0; i < m; i++){
				if(y > ye) return;
				screen[y][x] = '.';
				x += itr;
			}
			y++;
		}
		return;
	}
	//steep
	while(x < xe){
		for(double i = 0; i < m; i++){
			printf("m=%f\n",m);
			if(y > ye) return;
			screen[y][x] = '.';
			y++;
		}
		x += itr;
	}
	return;
}

