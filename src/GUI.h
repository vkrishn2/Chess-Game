#ifndef GUI_H
#define GUI_H

typedef struct gui{
	int srcx;
	int srcy;
	int targetx;
	int targety;
	int exit;
}GUI;

GUI Display(BOARD board, int AI, int Color);

int Gui_Get_Color(void);

#endif
