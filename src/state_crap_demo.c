
void state_crap_demo_frame() {
	static int xpos = 0;
	static int ypos = 0;
	xpos++;
	if (xpos % 120 == 0) ypos++;
	// dirt floor
	int dirtx = xpos % SCREEN_W;
	int dirty = ypos % SCREEN_H;
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
		&(SDL_Rect) { dirtx - SCREEN_W, dirty - SCREEN_H, SCREEN_W, SCREEN_H });
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
		&(SDL_Rect) { dirtx, dirty, SCREEN_W, SCREEN_H });
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
		&(SDL_Rect) { dirtx - SCREEN_W, dirty, SCREEN_W, SCREEN_H });
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
		&(SDL_Rect) { dirtx, dirty - SCREEN_H, SCREEN_W, SCREEN_H });
	// color bars
	for (int i = 0; i < 16; i++) {
		fvc_set_draw_color(i);
		SDL_RenderFillRect(fvc_renderer, 
			&(SDL_Rect) { (xpos + (20 * i)) % SCREEN_W, 10, 15, 100 });
	}
	// king duck
	int frame = (xpos >> 2) % 4;
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { frame * 20, 0, 20, 40 },
		&(SDL_Rect) { 100, 120, 20, 40 });

}
