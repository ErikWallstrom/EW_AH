#ifndef GRAHPICS_COMPONENT_H
#define GRAHPICS_COMPONENT_H

	#define COMPONENT_GRAPHICS 0
	
	typedef struct Graphics_Component Graphics_Component;
	typedef struct SDL_Renderer SDL_Renderer;
	typedef struct SDL_Rect SDL_Rect;

	Graphics_Component* gcomponent_create(SDL_Renderer* renderer, const char* file, 
										  double x, double y, int width, int height, 
										  double scale, double rotation);
	void 	gcomponent_destroy			 (Graphics_Component** gcomponent);
	int  	gcomponent_render			 (Graphics_Component* gcomponent, 
										  SDL_Renderer* renderer);
	int 	gcomponent_createanimations	 (Graphics_Component* gcomponent, int total_frames, 
										  SDL_Rect* frames, const char* animation_name, 
										  unsigned int delay);
	int		gcomponent_selectanimation	 (Graphics_Component* gcomponent, const char* name);
	
	double 	gcomponent_getx				 (Graphics_Component* gcomponent);
	double 	gcomponent_gety				 (Graphics_Component* gcomponent);
	double 	gcomponent_getscale			 (Graphics_Component* gcomponent);
	double 	gcomponent_getrotation		 (Graphics_Component* gcomponent);
	
	int 	gcomponent_setx				 (Graphics_Component* gcomponent, double x);
	int 	gcomponent_sety				 (Graphics_Component* gcomponent, double y);
	int 	gcomponent_setscale			 (Graphics_Component* gcomponent, double rotation);
	int 	gcomponent_setrotation		 (Graphics_Component* gcomponent, double rotation);

#endif