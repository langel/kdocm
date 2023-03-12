/*
	designed around Codehead's Bitmap Font Generator
*/


#define FONT_MAX_LEN 512

typedef struct {
	int size;
	int width;
	int height;
	SDL_Rect char_rect[FONT_MAX_LEN];
	SDL_Rect shit_rect;
	SDL_Texture * texture;
} font_struct;

font_struct fonts[4];

void font_set_color(font_struct f, SDL_Color color) {
	SDL_SetTextureColorMod(f.texture, color.r, color.g, color.b);
}



font_struct font_load(char *name, int size, SDL_Renderer * renderer) {
	font_struct f;
	f.size = size;
	char filename[64] = "assets/";
	strcat(filename, name);
	printf("loading : %s\n", filename);
	// load graphic
	char font_filename[32];
	strcpy(font_filename, filename);
	strcat(font_filename, ".bmp");
	SDL_Surface * image = SDL_LoadBMP(font_filename);
	f.shit_rect.x = 0;
	f.shit_rect.y = 0;
	f.shit_rect.w = image->w;
	f.shit_rect.h = image->h;
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0, 0)); 
	f.texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	// load data
	char data_filename[32];
	strcpy(data_filename, filename);
	strcat(data_filename, ".dat");
	FILE * data_file = fopen(data_filename, "r");
	if (data_file == NULL) {
		printf("failed access to : %s\n", data_filename);
	}
	unsigned char buffer[FONT_MAX_LEN];
	/* Read in 8-bit numbers into the buffer */
	size_t bytes_read = 0;
	bytes_read = fread(buffer, sizeof(unsigned char), FONT_MAX_LEN, data_file);
	//printf("bytes read : %zu\n", bytes_read);
	// Note: sizeof(unsigned char) is for emphasis
	int x = 0;
	int y = 0;
	f.width = buffer[8];
	f.height = buffer[12];
	int first_char = buffer[16];
	int header_length = 17;
	for (int i = first_char; i < bytes_read - header_length; i++) {
		int width = buffer[i + header_length];
//		width = size;
		if (x + f.width > 255) {
			x = 0;
			y += f.height;
		}
		//if (i % 8 == 0) printf("\n");
		//printf("%d\t", width);
		f.char_rect[i].x = x;
		f.char_rect[i].y = y;
		f.char_rect[i].w = width;
		f.char_rect[i].h = size;
		x += f.width;
	}
	fclose(data_file);
	//printf("\n\nx, y, 1st_char : %d, %d, %d\n", f.width, f.height, first_char);
	return f;
}

// target texture must be defined before calling
void font_render_text(char *text, font_struct f, SDL_Renderer * renderer, SDL_Rect rect) {
	int length = strlen(text);
	SDL_Rect char_buff = { 0, 0, f.width, f.height };
	char_buff = rect;
	for (int i = 0; i < length; i++) {
		int char_id = (int) text[i];
	//	printf(" %3d ", char_id);
		int width = f.char_rect[char_id].w;
		char_buff.w = width;
		SDL_RenderCopy(renderer, f.texture, &f.char_rect[char_id], &char_buff);
		char_buff.x += width;
	}
}


void font_init() {
	fonts[0] = font_load("font00_14x14", 14, fvc_renderer);
	fonts[1] = font_load("font01_25x24", 24, fvc_renderer);
	fonts[2] = font_load("font02_12x15", 12, fvc_renderer);
}


