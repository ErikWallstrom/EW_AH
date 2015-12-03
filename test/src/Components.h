#ifndef COMPONENTS_H
#define COMPONENTS_H
	
	typedef struct Graphics_Component Graphics_Component;
	typedef struct SDL_Renderer SDL_Renderer;
	typedef struct SDL_Rect SDL_Rect;
	typedef struct
	{
		int key_down;
		int key_up;
		int left_click;
		int right_click;
		
	} Event_Component;

	Graphics_Component* gcomponent_create		(SDL_Renderer* renderer, const char* file, 
										  		 double x, double y, int width, int height, 
										  	 	 double scale, double rotation);
	void 				gcomponent_destroy		(Graphics_Component** gcomponent);
	int 				gcomponent_render		(Graphics_Component* gcomponent, SDL_Renderer* renderer);
	int 				gcomponent_addanimation	(Graphics_Component* gcomponent, int total_frames, 
											 	 SDL_Rect* frames, unsigned int delay);
	Event_Component*	ecomponent_create		(int key_down, int key_up, int left_click, int right_click);
	
#endif
