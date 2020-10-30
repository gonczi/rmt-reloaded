/*******************************************************************************
				mouse.cpp
*******************************************************************************/
#ifndef _MOUSE
	#define _MOUSE
// ez a blokk tartalmazza az alapvet� eg�r kezel� rutinokat
void HideMouse (void);            // eg�rkurzor elrejt�se
void InitMouse(void);             // eg�r kezel� inicializ�l�sa
void MoveMouse(int X,int Y);      // eg�rkurzor elmozd�t�sa
char MouseClick(void);            // gomb lenyom�s
void ShowMouse();                 // eg�rkurzor megjelen�t�se
unsigned int MouseX();            // eg�rkurzor koordin�t�i
unsigned int MouseY();

void HideMouse (void){
asm {
		MOV AX,2
		INT 33H
}};
void InitMouse(void){
asm {
		MOV AX,0
		INT 33H
}};
void MoveMouse(int X,int Y){
asm {
		MOV CX,X
		MOV DX,Y
		MOV AX,4
		INT 33H
}};
char MouseClick(void){
asm {
		MOV BX,0
		MOV AX,3
		INT 33H
		};
return(_BL);
};
void ShowMouse(){
asm {
		MOV AX,1
		INT 33H
}};
unsigned int MouseX(){
asm {
		MOV AX,3
		INT 33H
		};
return( _CX>>1 );
};
unsigned int MouseY(){
asm {
		MOV AX,3
		INT 33H
		};
return( _DX );
};
void mouse_x_limit(int left,int right)
{
	asm {
		MOV AX,7
		MOV CX,left
		MOV DX,right
		INT 33H
		};
};
void mouse_y_limit(int up,int down)
{
	asm {
		MOV AX,8
		MOV CX,up
		MOV DX,down
		INT 33H
		};
};
#endif // __mouse_h
