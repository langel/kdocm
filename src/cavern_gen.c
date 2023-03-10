
#define cav_width 400
#define cav_height 175

#define cav_floor 0
#define cav_wall 1
#define cav_processed 3

typedef struct {
	SDL_Point point;
	SDL_Rect rect;
} cav_struct;

cav_struct cavern;
int cav_data[cav_width][cav_height];
int cav_temp[cav_width][cav_height];
float cav_wall_chance = 0.444f;
SDL_Point cav_min = { cav_width, cav_height };
SDL_Point cav_max = { 0, 0 };

void cav_noise_next() {
	for (int x = 0; x < cav_width; x++) {
		for (int y = 0; y < cav_height; y++) {
			float a = (float) rngn() / (float) 0xffffffff;
			int b = 0;
			if (a < cav_wall_chance) b = 1;
			cav_data[x][y] = (b) ? cav_wall : cav_floor;
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
			if (wall_count < 3 && is_wall) cav_temp[x][y] = cav_floor;
			if (wall_count > 4 && !is_wall) cav_temp[x][y] = cav_wall;
			if (x == 0 || x == cav_width - 1 || y == 0 || y == cav_height - 1) cav_temp[x][y] = cav_wall;
		}
	}
	memcpy(cav_data, cav_temp, sizeof(int) * cav_width * cav_height);
}

void cav_fill(int x, int y, int targ_c, int new_c) {
	if (cav_data[x][y] != targ_c) return;
	cav_data[x][y] = new_c;
	if (cav_min.x > x) cav_min.x = x;
	if (cav_max.x < x) cav_max.x = x;
	if (cav_min.y > y) cav_min.y = y;
	if (cav_max.y < y) cav_max.y = y;
	if (x < cav_width - 1) cav_fill(x+1, y, targ_c, new_c);
	if (x > 0) cav_fill(x-1, y, targ_c, new_c);
	if (y < cav_height - 1) cav_fill(x, y+1, targ_c, new_c);
	if (y > 0) cav_fill(x, y-1, targ_c, new_c);
}


void cav_generate(int targ_w, int targ_h) {
	cav_noise_next();
	for (int i = 0; i < 7; i++) cav_smooth();
	int cav_id = 0;
	cav_struct caverns[256];
	cav_struct cav_return;
	cav_min = (SDL_Point) { cav_width, cav_height };
	cav_max = (SDL_Point) { 0, 0 };
	for (int x = 0; x < cav_width; x++) {
		for (int y = 0; y < cav_height; y++) {
			if (cav_data[x][y] == cav_floor) {
				cav_fill(x, y, cav_floor, cav_processed);
				int width = cav_max.x - cav_min.x;
				int height = cav_max.y - cav_min.y;
				caverns[cav_id] = (cav_struct) {
					(SDL_Point) { x, y },
					(SDL_Rect) { cav_min.x, cav_min.y, width, height }
				};
				if (width <= targ_w && height <= targ_h) {
					if (width*height > cavern.point.x*cavern.point.y) {
						cavern = (cav_struct) {
							(SDL_Point) { x, y },
							(SDL_Rect) { cav_min.x, cav_min.y, width, height }
						};
					}
					
				}
				cav_id++;
			}
		}
	}
	cav_fill(cavern.point.x, cavern.point.y, cav_processed, cav_floor);
	printf("%d\n", cav_id);
	return;
}


