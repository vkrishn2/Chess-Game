#include "stdlib.h"
#include "SDL/SDL.h"
#include "Board.h"
#include "math.h"
#include "GUI.h"
#include <string.h>

int Gui_Get_Color(void){
	GUI gui;
	SDL_Surface *screen = NULL;
	SDL_Surface *image;	//This pointer will reference our bitmap sprite
	SDL_Surface *temp;	//This pointer will temporarily reference our bitmap sprite

	SDL_Rect src;	//These rectangles will describe the source and destination regions of our blit
	SDL_Event event;	/* Event structure */
	int Running;
	int Color = -100;
	gui.exit = 0;
	//We must first initialize the SDL video component, and check for success
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	//When this program exits, SDL_Quit must be called
	atexit(SDL_Quit);
	
	//Set the video mode to fullscreen 640x480 with 16bit colour and resizable
	screen = SDL_SetVideoMode(1000, 720, 32, SDL_ANYFORMAT);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	
	//Load the bitmap into a temporary surface, and check for success
	temp = SDL_LoadBMP("Chess_Board_Side.bmp");
	if (temp == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return 1;
	}
	
	//Convert the surface to the appropriate display format
	image = SDL_DisplayFormat(temp);
	
	//Release the temporary surface
	SDL_FreeSurface(temp);
	
	//Construct the source rectangle for our blit
	src.x = 0;
	src.y = 0;
	src.w = image->w;	//Use image->w to display the entire width of the image
	src.h = image->h;	//Use image->h to display the entire height of the image
	
	//Blit the image to the backbuffer
	SDL_BlitSurface(image, &src, screen, &src);

	//Flip the backbuffer to the primary
	SDL_Flip(screen);
	
	//while loop for running events
	Running = 1;
	while(Running && SDL_WaitEvent(&event))
	{
		switch(event.type)
		{ /* Process the appropriate event type */
			case SDL_MOUSEBUTTONDOWN:
			{//	printf("Oh! Mouse button pressed!\nCo-ord are: \n");
			//	printf("Position is x=%d, y=%d.\n", event.button.x, event.button.y);
				if((event.button.x>720 && event.button.x<970) && (event.button.y>60 && event.button.y<220)){
					Color = 0;
					Running = 0;
				}
				else if((event.button.x>720 && event.button.x<970) && (event.button.y>260 && event.button.y<420)){
					Color = 1;
					Running = 0;
				}
				else{
					printf("Invalid Selection! Please select a color!\n");
					printf("(Please select either the white or black king)\n");
				}
				break;
			}
			case SDL_QUIT:
			{	printf("Quit event received!\n");
				Running = 0;
				break;
			}
			default: /* ignore any other events */
			{
				break;
			}
		} /* hctiws */
	} /* elihw */
	
	//Release the surface
	SDL_FreeSurface(image);
	
	return Color;
}

GUI Display(BOARD board, int AI, int Color)
{
	GUI gui;
	SDL_Surface *screen;	//This pointer will reference the backbuffer
	SDL_Surface *image;	//This pointer will reference our bitmap sprite
	SDL_Surface *temp;	//This pointer will temporarily reference our bitmap sprite
	SDL_Surface *Apawn, *Aqueen, *Aking, *Abishop, *Ahorse, *Arook;
	SDL_Surface *Ppawn, *Pqueen, *Pking, *Pbishop, *Phorse, *Prook;

	SDL_Rect src;	//These rectangles will describe the source and destination regions of our blit
	SDL_Rect Ap, Aq, Ak, Ab, Ah, Ar;
	SDL_Rect Pp, Pq, Pk, Pb, Ph, Pr;

	SDL_Event event;	/* Event structure */
	int Running, mouse_click; 

	gui.exit = 0;

	//We must first initialize the SDL video component, and check for success
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		gui.exit = 1;
	}
	
	//When this program exits, SDL_Quit must be called
	atexit(SDL_Quit);
	
	//Set the video mode to fullscreen 640x480 with 16bit colour and resizable
	screen = SDL_SetVideoMode(1000, 720, 32, SDL_ANYFORMAT);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		gui.exit = 1;
	}
	
	if(Color == 0){
		temp = SDL_LoadBMP("Chess_Board_White.bmp");

	}
	else if(Color == 1){
		temp = SDL_LoadBMP("Chess_Board_Black.bmp");
	}
	
	if (temp == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		gui.exit = 1;
	}

	//Convert the surface to the appropriate display format
	image = SDL_DisplayFormat(temp);
	

	//Release the temporary surface
	SDL_FreeSurface(temp);
	
	//Construct the source rectangle for our blit
	src.x = 0;
	src.y = 0;
	src.w = image->w;	//Use image->w to display the entire width of the image
	src.h = image->h;	//Use image->h to display the entire height of the image
	
	//Blit the image to the backbuffer
	SDL_BlitSurface(image, NULL, screen, &src);
	
	for(int x = 0; x < 8; x++) {
        	for(int y = 0; y < 8; y++) {
                	if(strcmp(board.squares[x][y].Type,"aP") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Bpawn.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else{
					temp = SDL_LoadBMP("Wpawn.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}        				
				Apawn = SDL_DisplayFormat(temp);
				SDL_FreeSurface(temp);
				Ap.x = x*80;
				Ap.y = y*80;
				Ap.w = Apawn->w;	//Use image->w to display the entire width of the image
				Ap.h = Apawn->h;
				SDL_BlitSurface(Apawn, NULL, screen, &Ap);
                	}
                	else if(strcmp(board.squares[x][y].Type,"pP") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Wpawn.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else{
					temp = SDL_LoadBMP("Bpawn.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Ppawn = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Pp.x = x*80;
				Pp.y = y*80;
				Pp.w = Ppawn->w;	//Use image->w to display the entire width of the image
				Pp.h = Ppawn->h;
				SDL_BlitSurface(Ppawn, NULL, screen, &Pp);
                	}
                	else if(strcmp(board.squares[x][y].Type,"aQ") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Bqueen.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else{
					temp = SDL_LoadBMP("Wqueen.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Aqueen = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Aq.x = x*80;
				Aq.y = y*80;
				Aq.w = Aqueen->w;	//Use image->w to display the entire width of the image
				Aq.h = Aqueen->h;
				SDL_BlitSurface(Aqueen, NULL, screen, &Aq);
                	}                	
                	else if(strcmp(board.squares[x][y].Type,"pQ") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Wqueen.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Bqueen.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Pqueen = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Pq.x = x*80;
				Pq.y = y*80;
				Pq.w = Pqueen->w;	//Use image->w to display the entire width of the image
				Pq.h = Pqueen->h;
				SDL_BlitSurface(Pqueen, NULL, screen, &Pq);
                	}
                	else if(strcmp(board.squares[x][y].Type,"aB") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Bbishop.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Wbishop.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Abishop = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Ab.x = x*80;
				Ab.y = y*80;
				Ab.w = Abishop->w;	//Use image->w to display the entire width of the image
				Ab.h = Abishop->h;
				SDL_BlitSurface(Abishop, NULL, screen, &Ab);
                	}
                	else if(strcmp(board.squares[x][y].Type,"pB") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Wbishop.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Bbishop.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Pbishop = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Pb.x = x*80;
				Pb.y = y*80;
				Pb.w = Pbishop->w;	//Use image->w to display the entire width of the image
				Pb.h = Pbishop->h;
				SDL_BlitSurface(Pbishop, NULL, screen, &Pb);
                	}
                	else if(strcmp(board.squares[x][y].Type,"aK") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Bking.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Wking.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Aking = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Ak.x = x*80;
				Ak.y = y*80;
				Ak.w = Aking->w;	//Use image->w to display the entire width of the image
				Ak.h = Aking->h;
				SDL_BlitSurface(Aking, NULL, screen, &Ak);
                	}
                	else if(strcmp(board.squares[x][y].Type,"pK") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Wking.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Bking.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Pking = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Pk.x = x*80;
				Pk.y = y*80;
				Pk.w = Pking->w;	//Use image->w to display the entire width of the image
				Pk.h = Pking->h;
				SDL_BlitSurface(Pking, NULL, screen, &Pk);
                	}
                	else if(strcmp(board.squares[x][y].Type,"aH") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Bhorse.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Whorse.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Ahorse = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Ah.x = x*80;
				Ah.y = y*80;
				Ah.w = Ahorse->w;	//Use image->w to display the entire width of the image
				Ah.h = Ahorse->h;
				SDL_BlitSurface(Ahorse, NULL, screen, &Ah);
                	}
                	else if(strcmp(board.squares[x][y].Type,"pH") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Whorse.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Bhorse.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}	            			
				Phorse = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Ph.x = x*80;
				Ph.y = y*80;
				Ph.w = Phorse->w;	//Use image->w to display the entire width of the image
				Ph.h = Phorse->h;
				SDL_BlitSurface(Phorse, NULL, screen, &Ph);
                	}
                	else if(strcmp(board.squares[x][y].Type,"aR") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Brook.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Wrook.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
            			Arook = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Ar.x = x*80;
				Ar.y = y*80;
				Ar.w = Arook->w;	//Use image->w to display the entire width of the image
				Ar.h = Arook->h;
				SDL_BlitSurface(Arook, NULL, screen, &Ar);
                	}
                	else if(strcmp(board.squares[x][y].Type,"pR") == 0){
				if(Color == 0){
					temp = SDL_LoadBMP("Wrook.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}
				else if (Color == 1){
					temp = SDL_LoadBMP("Brook.bmp");
					SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
				}	            			
				Prook = SDL_DisplayFormat(temp);
            			SDL_FreeSurface(temp);
				Pr.x = x*80;
				Pr.y = y*80;
				Pr.w = Prook->w;	//Use image->w to display the entire width of the image
				Pr.h = Prook->h;
				SDL_BlitSurface(Prook, NULL, screen, &Pr);
                	}        	                	                	                	                	                	
		}
	}

	SDL_UpdateRect(screen,0,0,0,0);

	//while loop for running events
	Running = 1;
	mouse_click = 0;
	if(AI == 0){
		printf("Running!\n");
		while(Running && SDL_WaitEvent(&event) && mouse_click != 2){
			switch(event.type)
			{ /* Process the appropriate event type */
				case SDL_MOUSEBUTTONDOWN:
				{	
					if(mouse_click == 0){
						printf("Oh! 1st Mouse button pressed!\nCo-ord are: \n");
						printf("Position is x=%d, y=%d.\n",event.button.x, event.button.y);
						gui.srcx = event.button.x;
						gui.srcy = event.button.y;
						gui.srcx /= 80;
						gui.srcy /= 80;
						mouse_click = 1;
						if((event.button.x>790 && event.button.x<940) && (event.button.y>140 && event.button.y<315)){
							gui.exit = 1;
							Running = 0;
						}


					}
					else if(mouse_click == 1){
						printf("Oh! 2nd Mouse button pressed!\nCo-ord are: \n");
						printf("Position is x=%d, y=%d.\n",event.button.x, event.button.y);
						gui.targetx = event.button.x;
						gui.targety = event.button.y;
						gui.targetx /= 80;
						gui.targety /= 80;
						mouse_click = 2;
						if((event.button.x>790 && event.button.x<940) && (event.button.y>140 && event.button.y<315)){
							gui.exit = 1;
							Running = 0;
						}
						Running = 0;

					}
					break;
				}
				case SDL_QUIT:
				{	printf("Quit event received!\n");
					Running = 0;
					gui.exit = 1;
					break;
				}
				default: /* ignore any other events */
					break;
			} /* hctiws */
		} /* elihw */		
	}

		
		//Flip the backbuffer to the primary
		if(AI == 0){
			SDL_Flip(screen);	
		}
		
		//Release the surface
		if(gui.exit == 1){
			SDL_FreeSurface(image);
		}
	
	//Return success!
	return gui;
}
