#define FOV_W 32
#define FOV_H 20

int fov_map[FOV_W][FOV_H];

// check if tile is out of range
int fov_tile_oor(int x, int y) {
	if (x - field_x < 0) return 1;
	if (y - field_y < 0) return 1;
	if (x - field_x >= FOV_W) return 1;
	if (y - field_y >= FOV_H) return 1;
	return 0;
}

int fov_map_oor(int x, int y) {
	if (x < 0) return 1;
	if (y < 0) return 1;
	if (x >= map_width) return 1;
	if (y >= map_height) return 1;
	return 0;
}

void fov_process() {
	int x;
	int y;
	int size;
	float x_off;
	float y_off;
	float angle;
	int blocks;
	for (x=0;x<FOV_W;x++) for (y=0;y<FOV_H;y++) fov_map[x][y] = 0;
	// nnw
	size = player_y - field_y;
	for (int a = 0; a <= size; a++) {
		angle = (float) a / (float) size;
		blocks = 0;
		x_off = (float) player_x;
		for (y = player_y; y >= player_y - size; y--) {
			x = (int) round(x_off);
			if (fov_map_oor(x, y)) {
				blocks++;
			}
			else if (map_data[player_level][x][y] == tile_rock) {
				blocks++;
			}
			if (fov_tile_oor(x, y)) continue;
			fov_map[x - field_x][y - field_y] = blocks;
			x_off -= angle;
		}
	}
	// nne
	size = player_y - field_y;
	for (int a = 0; a <= size; a++) {
		angle = (float) a / (float) size;
		blocks = 0;
		x_off = (float) player_x;
		for (y = player_y; y >= player_y - size; y--) {
			x = (int) round(x_off);
			if (fov_map_oor(x, y)) {
				blocks++;
			}
			else if (map_data[player_level][x][y] == tile_rock) {
				blocks++;
			}
			if (fov_tile_oor(x, y)) continue;
			fov_map[x - field_x][y - field_y] = blocks;
			x_off += angle;
		}
	}
	// nee
	size = player_x - field_x;
	for (int a = 0; a <= size; a++) {
		angle = (float) a / (float) size;
		blocks = 0;
		y_off = (float) player_y;
		for (x = player_x; x < player_x + size; x++) {
			y = (int) round(y_off);
			if (fov_map_oor(x, y)) {
				blocks++;
			}
			else if (map_data[player_level][x][y] == tile_rock) {
				blocks++;
			}
			if (fov_tile_oor(x, y)) continue;
			fov_map[x - field_x][y - field_y] = blocks;
			y_off -= angle;
		}
	}
	// see
	size = player_x - field_x;
	for (int a = 0; a <= size; a++) {
		angle = (float) a / (float) size;
		blocks = 0;
		y_off = (float) player_y;
		for (x = player_x; x < player_x + size; x++) {
			y = (int) round(y_off);
			if (fov_map_oor(x, y)) {
				blocks++;
			}
			else if (map_data[player_level][x][y] == tile_rock) {
				blocks++;
			}
			if (fov_tile_oor(x, y)) continue;
			fov_map[x - field_x][y - field_y] = blocks;
			y_off += angle;
		}
	}
	// sse
	size = player_y - field_y;
	for (int a = 0; a <= size; a++) {
		angle = (float) a / (float) size;
		blocks = 0;
		x_off = (float) player_x;
		for (y = player_y; y < player_y + size; y++) {
			x = (int) round(x_off);
			if (fov_map_oor(x, y)) {
				blocks++;
			}
			else if (map_data[player_level][x][y] == tile_rock) {
				blocks++;
			}
			if (fov_tile_oor(x, y)) continue;
			fov_map[x - field_x][y - field_y] = blocks;
			x_off += angle;
		}
	}
	// ssw
	size = player_y - field_y;
	for (int a = 0; a <= size; a++) {
		angle = (float) a / (float) size;
		blocks = 0;
		x_off = (float) player_x;
		for (y = player_y; y < player_y + size; y++) {
			x = (int) round(x_off);
			if (fov_map_oor(x, y)) {
				blocks++;
			}
			else if (map_data[player_level][x][y] == tile_rock) {
				blocks++;
			}
			if (fov_tile_oor(x, y)) continue;
			fov_map[x - field_x][y - field_y] = blocks;
			x_off -= angle;
		}
	}
	// sww
	size = player_x - field_x;
	for (int a = 0; a <= size; a++) {
		angle = (float) a / (float) size;
		blocks = 0;
		y_off = (float) player_y;
		for (x = player_x; x >= player_x - size; x--) {
			y = (int) round(y_off);
			if (fov_map_oor(x, y)) {
				blocks++;
			}
			else if (map_data[player_level][x][y] == tile_rock) {
				blocks++;
			}
			if (fov_tile_oor(x, y)) continue;
			fov_map[x - field_x][y - field_y] = blocks;
			y_off += angle;
		}
	}
	// nww
	size = player_x - field_x;
	for (int a = 0; a <= size; a++) {
		angle = (float) a / (float) size;
		blocks = 0;
		y_off = (float) player_y;
		for (x = player_x; x >= player_x - size; x--) {
			y = (int) round(y_off);
			if (fov_map_oor(x, y)) {
				blocks++;
			}
			else if (map_data[player_level][x][y] == tile_rock) {
				blocks++;
			}
			if (fov_tile_oor(x, y)) continue;
			fov_map[x - field_x][y - field_y] = blocks;
			y_off -= angle;
		}
	}
}
