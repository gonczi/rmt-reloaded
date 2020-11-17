#include "mouse.h"

int mouse_pos_x = 0;
int mouse_pos_y = 0;
char mouse_click = 0;

void HideMouse (void){
};

void InitMouse(void){
};

// void MoveMouse(int X,int Y){
// };

char MouseClick(void){
	return mouse_click;
};

// void ShowMouse(){
// };

unsigned int MouseX(){
	return mouse_pos_x;
};

unsigned int MouseY(){
	return mouse_pos_y;
};

// void mouse_x_limit(int left,int right)
// {	
// };

void mouse_y_limit(int up,int down)
{
};

