
#define cav_width 500
#define cav_height 500

#define cav_floor 1
#define cav_wall 2
#define cav_processed 3

typedef struct {
	SDL_Point point;
	SDL_Rect rect;
} cav_struct;

int cav_data[cav_width][cav_height];
int cav_temp[cav_width][cav_height];

void cav_noise_next() {
	for (int x = 0; x < cav_width; x++) {
		for (int y = 0; y < cav_height; y++) {
			cav_data[x][y] = (rngn() & 0x01) ? cav_floor : cav_wall;
		}
	}
}

void cav_smooth() {
	memcpy(cav_temp, cav_data, sizeof(int) * cav_width * cav_height);
	for (int x = 0; x < cav_width; x++) {
		for (int y = 0; y < cav_height; y++) {
			int wall_count = 0;
			// cavs above
			if (y > 0) {
				if (x > 0) wall_count += cav_data[x - 1][y - 1];
				wall_count += cav_data[x][y - 1];
				if (x < cav_width - 1) wall_count += cav_data[x + 1][y - 1];
			}
			// cavs next door
			if (x > 0) wall_count += cav_data[x - 1][y];
			if (x < cav_width - 1) wall_count += cav_data[x + 1][y];
			// cavs below
			if (y < cav_height - 1) {
				if (x > 0) wall_count += cav_data[x - 1][y + 1];
				wall_count += cav_data[x][y + 1];
				if (x < cav_width - 1) wall_count += cav_data[x + 1][y + 1];
			}
			// update cav value
			int is_wall = (cav_data[x][y] == cav_wall);
			if (wall_count < 3 && is_wall) cav_temp[x][y] = 0;
			if (wall_count > 4 && !is_wall) cav_temp[x][y] = 1;
			if (x == 0 || x == cav_width - 1 || y == 0 || y == cav_height - 1) cav_temp[x][y] = 1;
		}
	}
	memcpy(cav_data, cav_temp, sizeof(int) * cav_width * cav_height);
}

void cav_fill(int x, int y, SDL_Point *min, SDL_Point *max) {
	int cell = cav_data[x][y];
	if (cell != cav_floor) return;
	cav_data[x][y] = cav_processed;
	if (min->x > x) min->x = x;
	if (max->x < x) max->x = x;
	if (min->y > y) min->y = y;
	if (max->y < y) max->y = y;
	cav_fill(x+1, y, min, max);
	cav_fill(x-1, y, min, max);
	cav_fill(x, y+1, min, max);
	cav_fill(x, y-1, min, max);
}

cav_struct cav_find_next() {
	for (int x = 0; x < cav_width; x++) {
		for (int y = 0; y < cav_height; y++) {
			if (cav_data[x][y] == cav_floor) {
				SDL_Point min = { cav_width, cav_height };
				SDL_Point max = { 0, 0 };
				cav_fill(x, y, &min, &max);
				return (cav_struct) {
					(SDL_Point) { x, y },
					(SDL_Rect) { min.x, min.y, max.x - min.x, max.y - min.y }
				};
			}
		}
	}
	return (cav_struct) {0};
}

void cav_generate(int targ_x, int targ_y) {
	cav_noise_next();
	for (int i = 0; i < 7; i++) cav_smooth();
	int cav_id = 0;
	cav_struct caverns[256];
	cav_struct cav_obj;
	cav_find_loop:
	cav_obj = cav_find_next();
	if (cav_obj.rect.w != 0) {
		printf("%d %d %d %d\n", cav_obj.point.x, cav_obj.point.y, cav_obj.rect.w, cav_obj.rect.h);
		caverns[cav_id] = cav_obj;
		cav_id++;
		goto cav_find_loop;
	}
	printf("%d\n", cav_id);
	return;
}


