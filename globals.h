#pragma bssseg(push,"ZEROPAGE")
#pragma dataseg(push,"ZEROPAGE")

static unsigned char i, j;

static unsigned char player_dir[2];

static unsigned char player_attack_tick[2];

static unsigned char player_x[2];
static unsigned char player_y[2];

static unsigned char enemies_x[8];
static unsigned char enemies_y[8];


static unsigned char enemies_enemy[8];


#pragma bssseg(push,"BSS")
#pragma dataseg(push,"BSS")

static unsigned char spr;
static unsigned char frame;
static unsigned char dx;
static unsigned char dy;

static unsigned char enemy_spawn_points_x[8];
static unsigned char enemy_spawn_points_y[8];

static unsigned char scr_x;
static unsigned char scr_y;

static char to_scroll_x;
static char to_scroll_y;

static unsigned char player_hp[2];

static unsigned char to_scroll_x_neg;
static unsigned char to_scroll_y_neg;

static unsigned char enemies_health[8];

static unsigned char enemies_dir[8];
static unsigned char enemy_leg[8];
static unsigned char enemy_push_timer[8];
static unsigned char enemy_push_dir[8];

static unsigned char enemies_type[8];

static unsigned char player_carry[2];
static unsigned char player_carry_dir[2];

static unsigned char player_god_mode[2];

static unsigned char item_type[4];
static unsigned char item_x[4];
static unsigned char item_y[4];
static unsigned char item_placed[4];


static unsigned char difficulty;

static unsigned char enemy_speed;

static unsigned char next_level;

static unsigned char enemy_damage_modifier;

static unsigned char spawn_hp;