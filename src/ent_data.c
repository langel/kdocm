

typedef struct {
	int type;
	int dir; // right, up, left, down
	int xt; // tile positions
	int yt;
	int state;
	int hp;
	int collisions;
} ent;

#define ENTS_COUNT 128
ent ents[map_levels][ENTS_COUNT];

#define ent_state_dead 0
#define ent_state_wandering 1
#define ent_state_blocked 2
#define ent_state_dormant 3
#define ent_state_pursuit 4
#define ent_state_flee 5
#define ent_state_player_controlled 6

#define ent_nan 0
#define ent_player 1
#define ent_ladder_up 2
#define ent_ladder_down 3
#define ent_ladder_up2 4
#define ent_ladder_down2 5
#define ent_herb 6
#define ent_key 7
#define ent_coin 8
#define ent_coins 9
#define ent_chest 10
#define ent_chest_emptied 11
#define ent_mimic 12
#define ent_cleaver 13
#define ent_mother_hen 14
#define ent_rat 15
#define ent_snake 16
#define ent_worm 17
#define ent_snerv 18
#define ent_homunculous 19
#define ent_gnome 20
#define ent_crab 21
#define ent_goat 22
#define ent_jackalope 23
#define ent_owlbear 24
#define ent_herb_gone 25
#define ent_tombstone 26

// number of types per level
int map_ent_type_count[map_levels] = {0};
// number of ents per level
int map_ents_count[map_levels] = {0};
// ent types per level
int map_ent_types[map_levels][16] = {0};

typedef struct {
	int ent_types_count;
	int ent_types[16];
} map_ents_data_struct;

typedef struct {
	char name[16];
	int state;
	int hp;
	int damage_base;
	int damage_rand;
	char verb[16];
	SDL_Rect sprite;
	int xp;
} ent_type;

ent_type ent_types[42] = {
	{ "nan", ent_state_dead, 0, 0, 0, "does not exist", 
		{ 0, 0, 0, 0 }, 0 },
	{ "player", ent_state_wandering,	42, 10, 10, "quacks", 
		{ 0, 0, 20, 40 }, 0 },
	{ "ladder up", ent_state_dormant, 
		0, 0, 0, "ascends",
		{ 80, 0, 20, 20 }, 13 },
	{ "ladder down", ent_state_dormant, 
		0, 0, 0, "descends",
		{ 100, 0, 20, 20 }, 13 },
	{ "ladder up 2", ent_state_dormant, 
		0, 0, 0, "accents",
		{ 80, 0, 20, 20 }, 13 },
	{ "ladder down 2", ent_state_dormant, 
		0, 0, 0, "decents",
		{ 100, 0, 20, 20 }, 13 },
	{ "herb", ent_state_dormant, 0, 0, 0, "heals", 
		{ 0, 60, 20, 20 }, 0 },
	{ "key", ent_state_dormant, 
		0, 0, 0, "unlocks",
		{ 0, 45, 10, 4 }, 0 },
	{ "coin",
		ent_state_dormant, 0, 0, 0, "plinks",
		{ 0, 52, 7, 3 }, 0 },
	{ "coins",
		ent_state_dormant, 0, 0, 0, "changles",
		{ 10, 51, 7, 7 }, 0 },
	{ "chest",
		ent_state_dormant, 0, 0, 0, "opens",
		{ 20, 40, 20, 20 }, 0 },
	{ "empty chest", ent_state_dead, 0, 0, 0, "sits",
		{ 40, 40, 20, 20 }, 0 },
	{ "mimic", ent_state_wandering, 
		43, 12, 12, "mawls",
		{ 60, 40, 20, 20 }, 120 },
	{ "cleaver", ent_state_dormant, 
		0, 0, 0, "cleaves",
		{ 80, 20, 20, 20 }, 1777 },
	{ "Mother Hen", ent_state_dormant, 
		0, 0, 0, "broods",
		{ 140, 0, 40, 40 }, 7777 },
	{ "rat", ent_state_wandering, 
		4, 2, 7, "snips",
		{ 0, 40, 8, 6 }, 22 },
	{ "snake", ent_state_wandering, 
		6, 2, 7, "sproingss",
		{ 10, 40, 10, 10 }, 33 },
	{ "worm", ent_state_wandering, 
		2, 1, 2, "wriggles",
		{ 80, 40, 20, 20 }, 11 },
	{ "snerv", ent_state_wandering, 
		11, 1, 7, "swerves",
		{ 80, 60, 20, 20 }, 27 },
	{ "homunculus", ent_state_wandering, 
		13, 3, 25, "rots",
		{ 40, 60, 20, 40 }, 39 },
	{ "gnome", ent_state_wandering, 
		25, 8, 10, "cunnings",
		{ 60, 60, 20, 40 }, 56 },
	{ "crab", ent_state_wandering, 
		5, 1, 5, "pincers",
		{ 80, 80, 20, 20 }, 23 },
	{ "goat", ent_state_wandering, 
		33, 5, 35, "gores",
		{ 100, 40, 40, 40 }, 73 },
	{ "jackalope", ent_state_wandering, 
		33, 8, 10, "gores",
		{ 140, 40, 20, 40 }, 56 },
	{ "owlbear", ent_state_wandering, 
		59, 14, 7, "claws",
		{ 160, 40, 20, 40 }, 777 },
	{ "herb gone", ent_state_dormant, 0, 0, 0, "filths", 
		{ 20, 60, 20, 20 }, 0 },
	{ "tombstone", ent_state_dormant, 0, 0, 0, "sits", 
		{ 100, 80, 20, 20 }, 0 },
};
