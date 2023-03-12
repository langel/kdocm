
SDL_Rect playfield_rect = { 0, 0, 320, 200 };


void state_game_play_frame() {
	ents_update(player_level, ents[player_level], playfield_rect);
	player_x = ents[player_level][0].xt;
	player_y = ents[player_level][0].yt;
	field_x = player_x - 16;
	field_y = player_y - 10;

	camera_rect.x = field_x * 10;
	camera_rect.y = field_y * 10;
	
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

	// FOV
	fvc_set_draw_color(4);
	fov_process(player_x, player_y, field_x, field_y);
	
	for (int x = 0; x < FOV_W; x++) {
		for (int y = 0; y < FOV_H; y++) {
			if (fov_map[x][y] > 2) {
				fvc_set_draw_color(((fov_map[x][y]+1) >> 1) + 2);
				fvc_set_draw_color(fov_map[x][y] + 1);
				SDL_Rect shadow = { x * 10, y * 10,	10, 10 };
				SDL_RenderFillRect(fvc_renderer, &shadow);
			}
		}
	}

	ents_render(ents[player_level], fvc_renderer);

	// hud
	fvc_set_draw_color(16);
	SDL_RenderFillRect(fvc_renderer, &(SDL_Rect) { 320, 0, 100, 200 });
	
	// player controls
	if (ents[player_level][0].state == ent_state_player_controlled) {
		ents[player_level][0].dir = 0xff;
		if (keys[SDL_SCANCODE_RIGHT]) ents[player_level][0].dir = 0;
		if (keys[SDL_SCANCODE_UP]) ents[player_level][0].dir = 1;
		if (keys[SDL_SCANCODE_LEFT]) ents[player_level][0].dir = 2;
		if (keys[SDL_SCANCODE_DOWN]) ents[player_level][0].dir = 3;
	}
	if (keys[SDL_SCANCODE_C] == 1) {
		printf("c pressed\n");
		if (ents[player_level][0].state == ent_state_player_controlled) {
			ents[player_level][0].state = ent_state_blocked;
		}
		else ents[player_level][0].state = ent_state_player_controlled;
	}


}
