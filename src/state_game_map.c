

void state_game_map_frame() {
	SDL_RenderCopy(fvc_renderer, dirt_texture, NULL, NULL);
	SDL_RenderCopy(fvc_renderer, map_view_texture, NULL, &map_view_rect);
}
