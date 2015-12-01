#ifndef COMPONENTS_H
#define COMPONENTS_H
	
	typedef struct Image_Component Image_Component;
	typedef struct Text_Component Text_Component;
	typedef struct SDL_Renderer SDL_Renderer;

	Image_Component* icomponent_create(
		SDL_Renderer* renderer, const char* file, 
		double x, double y, 
		int width, int height,
		double scale, double rotation					   
	);
	void 	icomponent_destroy	(Image_Component** icomponent);
	int 	icomponent_render(Image_Component* icomponent, SDL_Renderer* renderer);
	
#endif
