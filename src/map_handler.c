// 0 is empty  16 (no color)
// 1 is rock   3
// 2 is water  11
// 3 is lava   6
// 3 is dirt   4

// each tile type has 4 colors associated


void map_handler_generate_all() {
	// clear all map data with rocks
	for (int a = 0; a < map_levels; a++) {
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				map_data[a][x][y] = tile_rock;
			}
		}
	}
	for (int a = 0; a < map_levels; a++) {
		// CAVERN CAVITY
		int targ_w = level_rules[a].map_max_size[0] * 2;
		if (targ_w > map_width) targ_w = map_width - 2;
		int targ_h = level_rules[a].map_max_size[1] * 2;
		if (targ_h > map_height) targ_h = map_height - 2;
		cav_generate(targ_w, targ_h);
		
		int basex = (map_width - cavwin.rect.w) >> 1;
		int basey = (map_height - cavwin.rect.h) >> 1;

		for (int x = 0; x < cavwin.rect.w; x++) {
			for (int y = 0; y < cavwin.rect.h; y++) {
				if (cav_data[x + cavwin.rect.x][y + cavwin.rect.y] == cav_floor) {
					map_data[a][x + basex][y + basey] = tile_empty;
				}
			}
		}
		// ROOMS PLOT
		map_level_rules * level = &level_rules[a];
		for (int r = 0; r < level->room_count; r++) {
			SDL_Rect room;
			room.w = rngn() % level->room_max_size[0] + map_room_min_x;
			room.h = rngn() % level->room_max_size[1] + map_room_min_y;
			room.x = (map_width - level->map_max_size[0]) / 2 + (rngn() % (level->map_max_size[0] - room.w - 4)); 
			room.y = (map_height - level->map_max_size[1]) / 2 + (rngn() % (level->map_max_size[1] - room.h - 4)); 
			for (int x = room.x; x < room.x + room.w; x++) {
				for (int y = room.y; y < room.y + room.h; y++) {
					map_data[a][x][y] = tile_empty;
				}
			}
			// cache room center position
			room_centers[r][0] = room.x + room.w / 2;
			room_centers[r][1] = room.y + room.h / 2;
		}
		// DEBRIS PLOT
		// add rock debris
		for (int i = 0; i < level->debris_rock_count; i++) {
			map_data[a][rngn() % map_width][rngn() % map_height] = tile_rock;
		}
		// add water debris
		for (int i = 0; i < level->debris_water_count; i++) {
			map_data[a][rngn() % map_width][rngn() % map_height] = tile_water;
		}
		// add lava debris
		for (int i = 0; i < level->debris_lava_count; i++) {
			map_data[a][rngn() % map_width][rngn() % map_height] = tile_lava;
		}
		// add dirt debris
		for (int i = 0; i < level->debris_dirt_count; i++) {
			map_data[a][rngn() % map_width][rngn() % map_height] = tile_dirt;
		}
		// LADDERS PLOT
		int mx, my;
		// up ladder
		mx = room_centers[0][0];
		my = room_centers[0][1];
		for (int i = mx - 1; i < mx + 2; i++) {
			for (int j = my - 1; j < my + 2; j++) {
				map_data[a][i][j] = 0;
			}
		}
		ent_load_type(a, 0, ent_player);
		ents[a][0].xt = room_centers[0][0] + 1;
		ents[a][0].yt = room_centers[0][1];
		if (a == 9) {
			ent_load_type(a, 2, ent_ladder_up2);
		}
		else {
			ent_load_type(a, 2, ent_ladder_up);
		}
		ents[a][2].xt = room_centers[0][0];
		ents[a][2].yt = room_centers[0][1];
		// down ladder
		int last_room = level_rules[a].room_count - 1;
		mx = room_centers[last_room][0];
		my = room_centers[last_room][1];
		for (int i = mx - 1; i < mx + 2; i++) {
			for (int j = my - 1; j < my + 2; j++) {
				map_data[a][i][j] = 0;
			}
		}
		if (a == 6) {
			ent_load_type(a, 3, ent_ladder_down2);
			ents[a][3].xt = room_centers[last_room-2][0];
			ents[a][3].yt = room_centers[last_room-2][1];
		}
		if (a != 8 && a != 11) {
			ent_load_type(a, 1, ent_ladder_down);
			ents[a][1].xt = room_centers[last_room][0];
			ents[a][1].yt = room_centers[last_room][1];
		}
		if (a == 8) {
			ent_load_type(a, 1, ent_mother_hen);
			ents[a][1].xt = room_centers[last_room][0];
			ents[a][1].yt = room_centers[last_room][1];
		}
		if (a == 11) {
			ent_load_type(a, 1, ent_cleaver);
			ents[a][1].xt = room_centers[last_room][0];
			ents[a][1].yt = room_centers[last_room][1];
		}
		// CORRIDORS PLOT
		for (int i = 1; i < level->room_count; i++) {
			// corridor cut outs between cavities
			int target = rngn() % (i);
			// current room
			int crx = room_centers[i][0];
			int cry = room_centers[i][1];
			// target room
			int trx = room_centers[target][0];
			int try = room_centers[target][1];
			// carve corriders
			if (crx >= trx) for (int x = trx; x <= crx; x++) {
				map_data[a][x][cry] = tile_empty;		
			}
			else for (int x =  crx; x <= trx; x++) {
				map_data[a][x][cry] = tile_empty;
			}
			if (cry >= try) for (int y = try; y <= cry; y++) {
				map_data[a][trx][y] = tile_empty;
			}
			else for (int y =  cry; y <= try; y++) {
				map_data[a][trx][y] = tile_empty;
			}
		}

	}
}
