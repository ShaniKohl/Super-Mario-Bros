#include "windows.h"
#include "toolbox.h"
#include <cvirte.h>		
#include <userint.h>
#include "Super Mario Bros.h"

static int panelHandle, panelHandle2;

//variables for keyboard monitoring
int Callback_Data;	
int Posting_Handle; 
int Keys_Down[256]={0}; 

int mario_r_bitmap, mario_l_bitmap, marios_bitmap, marioj_bitmap, goombaw_bitmap, mariod_bitmap, game_over_bitmap;

int counter, collision=0;

double mario_x= 100.0, mario_y= 300.0, h, goomba_x=400.0, goomba_y=300.0;
int direction = 0;
int mario_counter =0, goomba_counter=0;

Rect temp_rect;

//Receives information from windows regarding key presses
int CVICALLBACK Key_DownFunc(int panel, int message, unsigned int* wParam, unsigned int* lParam, void* callbackData)
{
	unsigned int Key = *wParam;
	Keys_Down[Key] = 1;
	return 0;
}

//Receives information from windows regarding key releases
int CVICALLBACK Key_UpFunc(int panel, int message, unsigned int* wParam, unsigned int* lParam, void* callbackData)
{
	unsigned int Key = *wParam;
	Keys_Down[Key] = 0;
	return 0;
}

//asking windows to send keyboard press and release events to our software 
//Specifing 'Key_DownFunc' and 'Key_UpFunc' as the functions to call
void Connect_To_Windows_Events(void)
{
	InstallWinMsgCallback(panelHandle,WM_KEYDOWN,Key_DownFunc,VAL_MODE_IN_QUEUE,&Callback_Data,&Posting_Handle);
	InstallWinMsgCallback(panelHandle,WM_KEYUP,Key_UpFunc,VAL_MODE_IN_QUEUE,&Callback_Data,&Posting_Handle);
}

void initialize()
{
	Connect_To_Windows_Events();
	
	GetBitmapFromFile ("Mario_Right.png", &mario_r_bitmap);
	GetBitmapFromFile ("Mario_Left.png", &mario_l_bitmap);
	GetBitmapFromFile ("marios.png", &marios_bitmap);
	GetBitmapFromFile ("Mario_Jump.png", &marioj_bitmap);
	GetBitmapFromFile ("Goomba_walk.png", &goombaw_bitmap);
	GetBitmapFromFile ("Mario_dead.png", &mariod_bitmap);
	GetBitmapFromFile ("game over.png", &game_over_bitmap);
}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Super Mario Bros.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle2 = LoadPanel (0, "Super Mario Bros.uir", PANEL_2)) < 0)
		return -1;
	initialize();
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	
return 0;
}

void update()
{
	if (Keys_Down[39] == 1 || Keys_Down[37] == 1 || Keys_Down[32] == 1)
		SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
	
	mario_x = mario_x +(Keys_Down[39] - Keys_Down[37])*5;
	direction = (Keys_Down[39] - Keys_Down[37]);
	
	goomba_x = goomba_x -2;

	Rect marioRect = {mario_x, mario_y, 50, 50}; 
    Rect goombaRect = {goomba_x, goomba_y, 30, 30}; 
   
 	if (RectIntersection(marioRect, goombaRect, & temp_rect))
 	{
        direction =4;
    }
	
	if(Keys_Down[32] == 1)
		direction = 2;
		
	if (Keys_Down[38] == 1)
		direction = 3;
		
	if (direction == 0)
		mario_counter = 0;
	else 
		if (counter%2 == 0)
			mario_counter = (mario_counter+1)%3;
	
	goomba_x++;
	
	if (counter%5 == 0)
		goomba_counter = (goomba_counter+1)%2;
	counter ++;
}

void draw()
{
	CanvasStartBatchDraw (panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	switch(direction)
	{
		case -1:
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, mario_l_bitmap, MakeRect(0, mario_counter*32, 32, 32), MakeRect(mario_y, mario_x, 50, 50));
				break;
		case 0:
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, marios_bitmap, MakeRect(0, 0, 31, 16), MakeRect(mario_y, mario_x, 50, 25));
				break;
		case 1:
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, mario_r_bitmap, MakeRect(0,mario_counter*32, 32, 32), MakeRect(mario_y, mario_x, 50, 50));
				break;
		case 2:
			if (mario_y >= 300)
			{
				h = mario_y - Keys_Down[32]*70;
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, marioj_bitmap, MakeRect(0, 0, 32, 16), MakeRect(h, mario_x, 50, 25));
			}
			else
			{
				h = mario_y + Keys_Down[32]*70;
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, marioj_bitmap, MakeRect(0, 0, 31, 16), MakeRect(h, mario_x, 50, 25));
			}
		break;
		case 3:
			if (mario_y >= 300)
			{
				h = mario_y - Keys_Down[38]*70;
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, marioj_bitmap, MakeRect(0, 0, 32, 16), MakeRect(h, mario_x, 50, 25));
			}
			else
			{
				h = mario_y + Keys_Down[38]*70;
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, marioj_bitmap, MakeRect(0, 0, 31, 16), MakeRect(h, mario_x, 50, 25));
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, marioj_bitmap, MakeRect(0, 0, 31, 16), MakeRect(h, mario_x, 50, 25));
			}
		break;
		case 4:
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0); 
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, mariod_bitmap, MakeRect(0, 0, 32, 32), MakeRect(mario_y, mario_x, 25, 25));
				Keys_Down[32] = 0;
				Keys_Down[37] = 0;
				Keys_Down[38] = 0;
				Keys_Down[39] = 0;
				DisplayPanel (panelHandle2);
		break;
	}
	
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, goombaw_bitmap, MakeRect(0,goomba_counter*195, 195, 195), MakeRect(320, goomba_x, 30, 30));
	
	CanvasEndBatchDraw (panelHandle, PANEL_CANVAS);
}

int CVICALLBACK ExitFunc (int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK CanvasFunc (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	draw();
	return 0;
}

int CVICALLBACK TimerFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			update();
			draw();
			
			break;
	}
	return 0;
}

int CVICALLBACK ExitFunc2 (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (panelHandle2);
			break;
	}
	return 0;
}

int CVICALLBACK StartNew (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			HidePanel (panelHandle2);
			counter = 0;
			mario_x = 100.0;
			direction =-1;
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			update();
			draw();
			break;
	}
	return 0;
}
