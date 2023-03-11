
SDL_Rect playfield_rect = { 0, 0, 320, 200 };


void state_game_play_frame() {
	ents_update(player_level, ents[player_level], playfield_rect);

	camera_rect.x = (ents[player_level][0].xt - 16) * 10;
	camera_rect.y = (ents[player_level][0].yt - 10) * 10;
	
	// dirt floor
	int dirtx = camera_rect.x % SCREEN_W;
	int dirty = camera_rect.y % SCREEN_H;
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
		&(SDL_Rect) { dirtx - SCREEN_W, dirty - SCREEN_H, SCREEN_W, SCREEN_H });
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
		&(SDL_Rect) { dirtx, dirty, SCREEN_W, SCREEN_H });
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
		&(SDL_Rect) { dirtx - SCREEN_W, dirty, SCREEN_W, SCREEN_H });
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, 
		&(SDL_Rect) { dirtx, dirty - SCREEN_H, SCREEN_W, SCREEN_H });

	// handle out of bounds camera positions
	int map_px_w = map_width * 10;
	int map_px_h = map_height * 10;
	SDL_Rect oob_cam = { 0, 0, camera_rect.w, camera_rect.h };
	SDL_Rect oob_field = { 0, 0, playfield_rect.w, playfield_rect.h };
	if (camera_rect.x < 0) {
		oob_cam.x = 0;
		oob_field.x = abs(camera_rect.x);
		oob_field.w = playfield_rect.w - oob_cam.x;
	}
	else if (camera_rect.x + camera_rect.w > map_px_w) {
		oob_cam.x = camera_rect.x;
		oob_cam.w = map_px_w - camera_rect.x;
		oob_field.w = oob_cam.w;
	}
	else {
		oob_cam.x = camera_rect.x;
	}
	if (camera_rect.y < 0) {
		oob_cam.y = 0;
		oob_field.y = abs(camera_rect.y);
		oob_field.h = playfield_rect.h - oob_cam.y;
	}
	else if (camera_rect.y + camera_rect.h > map_px_h) {
		oob_cam.y = camera_rect.y;
		oob_cam.h = map_px_h - camera_rect.y;
		oob_field.h = oob_cam.h;
	}
	else {
		oob_cam.y = camera_rect.y;
	}
	
	// background refresh
	SDL_RenderCopy(fvc_renderer, map_texture, &oob_cam, &oob_field);
	ents_render(ents[player_level], fvc_renderer);

	SDL_RenderFillRect(fvc_renderer, &(SDL_Rect) { 320, 0, 100, 200 });

/*
	// king duck
	int frame = (frame_counter >> 2) % 4;
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { frame * 20, 0, 20, 40 },
		&(SDL_Rect) { 100, 120, 20, 40 });

	// ladder
	SDL_RenderCopy(fvc_renderer, spriteshit, 
		&(SDL_Rect) { 80, 0, 20, 20 },
		&(SDL_Rect) { 80, 80, 20, 20 });
		*/

}
