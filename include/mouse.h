#ifndef _MOUSE
	#define _MOUSE

// ez a blokk tartalmazza az alapvet� eg�r kezel� rutinokat

void HideMouse (void);            // eg�rkurzor elrejt�se
void InitMouse(void);             // eg�r kezel� inicializ�l�sa
// void MoveMouse(int X,int Y);      // eg�rkurzor elmozd�t�sa
char MouseClick(void);            // gomb lenyom�s
// void ShowMouse();                 // eg�rkurzor megjelen�t�se
unsigned int MouseX();            // eg�rkurzor koordin�t�i
unsigned int MouseY();

// void mouse_x_limit(int left,int right);
void mouse_y_limit(int up,int down);

// manage this from scancode thread:
extern int mouse_pos_x;
extern int mouse_pos_y;
extern char mouse_click;

#endif // __mouse_h
