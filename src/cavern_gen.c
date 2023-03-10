
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

void cav_fill(int x, int y, SDL_Point *min, SDL_Point *max) {
	if (cav_data[x][y] != cav_floor) return;
	cav_data[x][y] = cav_processed;
	if (min->x > x) min->x = x;
	if (max->x < x) max->x = x;
	if (min->y > y) min->y = y;
	if (max->y < y) max->y = y;
	if (x < cav_width - 1) cav_fill(x+1, y, min, max);
	if (x > 0) cav_fill(x-1, y, min, max);
	if (y < cav_height - 1) cav_fill(x, y+1, min, max);
	if (y > 0) cav_fill(x, y-1, min, max);
}


void cav_mark(int x, int y, SDL_Point *min, SDL_Point *max) {
	if (cav_data[x][y] != cav_processed) return;
	cav_data[x][y] = cav_floor;
	if (min->x > x) min->x = x;
	if (max->x < x) max->x = x;
	if (min->y > y) min->y = y;
	if (max->y < y) max->y = y;
	if (x < cav_width - 1) cav_fill(x+1, y, min, max);
	if (x > 0) cav_fill(x-1, y, min, max);
	if (y < cav_height - 1) cav_fill(x, y+1, min, max);
	if (y > 0) cav_fill(x, y-1, min, max);
}

void cav_generate(int targ_w, int targ_h) {
	cav_noise_next();
	for (int i = 0; i < 7; i++) cav_smooth();
	int cav_id = 0;
	cav_struct caverns[256];
	cav_struct cav_return;
	SDL_Point min = { cav_width, cav_height };
	SDL_Point max = { 0, 0 };
	for (int x = 0; x < cav_width; x++) {
		for (int y = 0; y < cav_height; y++) {
			if (cav_data[x][y] == cav_floor) {
				min = (SDL_Point) { cav_width, cav_height };
				max = (SDL_Point) { 0, 0 };
				cav_fill(x, y, &min, &max);
				int width = max.x - min.x;
				int height = max.y - min.y;
				caverns[cav_id] = (cav_struct) {
					(SDL_Point) { x, y },
					(SDL_Rect) { min.x, min.y, width, height }
				};
				if (width <= targ_w && height <= targ_h) {
					if (width*height > cavern.point.x*cavern.point.y) {
						cavern = (cav_struct) {
							(SDL_Point) { x, y },
							(SDL_Rect) { min.x, min.y, width, height }
						};
					}
					
				}
				cav_id++;
			}
		}
	}
	cav_mark(cavern.point.x, cavern.point.y, &min, &max);
//	printf("%d\n", cav_id);
	return;
}


