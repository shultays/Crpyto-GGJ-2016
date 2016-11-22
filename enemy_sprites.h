
static const char spider_damaged_stand_up[] = {
    -8, -8, 0x80, 1,
    0,  -8, 0x82, 1,
    128
};
static const char spider_damaged_stand_down[] = {
    -8, -8, 0x80, 1|OAM_FLIP_V,
    0,  -8, 0x82, 1|OAM_FLIP_V,
    128
};
static const char spider_damaged_stand_right[] = {
    -8, -8, 0xA0, 1,
    0,  -8, 0xA2, 1,
    128
};
static const char spider_damaged_stand_left[] = {
    -8, -8, 0xA2, 1|OAM_FLIP_H,
    0,  -8, 0xA0, 1|OAM_FLIP_H,
    128
};

static const char spider_damaged_attack_up[] = {
    -8, -8, 0x84, 1,
    0,  -8, 0x86, 1,
    128
};
static const char spider_damaged_attack_down[] = {
    -8, -8, 0x84, 1|OAM_FLIP_V,
    0,  -8, 0x86, 1|OAM_FLIP_V,
    128
};
static const char spider_damaged_attack_right[] = {
    -8, -8, 0xA4, 1,
    0,  -8, 0xA6, 1,
    128
};
static const char spider_damaged_attack_left[] = {
    -8, -8, 0xA6, 1|OAM_FLIP_H,
    0,  -8, 0xA4, 1|OAM_FLIP_H,
    128
};

static const char spider_damaged_leg_0_up[] = {
    -8, -8, 0x88, 1,
    0,  -8, 0x8A, 1,
    128
};
static const char spider_damaged_leg_0_down[] = {
    -8, -8, 0x88, 1|OAM_FLIP_V,
    0,  -8, 0x8A, 1|OAM_FLIP_V,
    128
};
static const char spider_damaged_leg_0_right[] = {
    -8, -8, 0xA8, 1,
    0,  -8, 0xAA, 1,
    128
};
static const char spider_damaged_leg_0_left[] = {
    -8, -8, 0xAA, 1|OAM_FLIP_H,
    0,  -8, 0xA8, 1|OAM_FLIP_H,
    128
};

static const char spider_damaged_leg_1_up[] = {
    -8, -8, 0x8A, 1|OAM_FLIP_H,
    0,  -8, 0x88, 1|OAM_FLIP_H,
    128
};
static const char spider_damaged_leg_1_down[] = {
    -8, -8, 0x8A, 1|OAM_FLIP_H|OAM_FLIP_V,
    0,  -8, 0x88, 1|OAM_FLIP_H|OAM_FLIP_V,
    128
};
static const char spider_damaged_leg_1_right[] = {
    -8, -8, 0xA8, 1|OAM_FLIP_V,
    0,  -8, 0xAA, 1|OAM_FLIP_V,
    128
};
static const char spider_damaged_leg_1_left[] = {
    -8, -8, 0xAA, 1|OAM_FLIP_H|OAM_FLIP_V,
    0,  -8, 0xA8, 1|OAM_FLIP_H|OAM_FLIP_V,
    128
};

static const char spider_stand_up[] = {
    -8, -8, 0x80, 2,
    0,  -8, 0x82, 2,
    128
};
static const char spider_stand_down[] = {
    -8, -8, 0x80, 2|OAM_FLIP_V,
    0,  -8, 0x82, 2|OAM_FLIP_V,
    128
};
static const char spider_stand_right[] = {
    -8, -8, 0xA0, 2,
    0,  -8, 0xA2, 2,
    128
};
static const char spider_stand_left[] = {
    -8, -8, 0xA2, 2|OAM_FLIP_H,
    0,  -8, 0xA0, 2|OAM_FLIP_H,
    128
};

static const char spider_attack_up[] = {
    -8, -8, 0x84, 2,
    0,  -8, 0x86, 2,
    128
};
static const char spider_attack_down[] = {
    -8, -8, 0x84, 2|OAM_FLIP_V,
    0,  -8, 0x86, 2|OAM_FLIP_V,
    128
};
static const char spider_attack_right[] = {
    -8, -8, 0xA4, 2,
    0,  -8, 0xA6, 2,
    128
};
static const char spider_attack_left[] = {
    -8, -8, 0xA6, 2|OAM_FLIP_H,
    0,  -8, 0xA4, 2|OAM_FLIP_H,
    128
};

static const char spider_leg_0_up[] = {
    -8, -8, 0x88, 2,
    0,  -8, 0x8A, 2,
    128
};
static const char spider_leg_0_down[] = {
    -8, -8, 0x88, 2|OAM_FLIP_V,
    0,  -8, 0x8A, 2|OAM_FLIP_V,
    128
};
static const char spider_leg_0_right[] = {
    -8, -8, 0xA8, 2,
    0,  -8, 0xAA, 2,
    128
};
static const char spider_leg_0_left[] = {
    -8, -8, 0xAA, 2|OAM_FLIP_H,
    0,  -8, 0xA8, 2|OAM_FLIP_H,
    128
};

static const char spider_leg_1_up[] = {
    -8, -8, 0x8A, 2|OAM_FLIP_H,
    0,  -8, 0x88, 2|OAM_FLIP_H,
    128
};
static const char spider_leg_1_down[] = {
    -8, -8, 0x8A, 2|OAM_FLIP_H|OAM_FLIP_V,
    0,  -8, 0x88, 2|OAM_FLIP_H|OAM_FLIP_V,
    128
};
static const char spider_leg_1_right[] = {
    -8, -8, 0xA8, 2|OAM_FLIP_V,
    0,  -8, 0xAA, 2|OAM_FLIP_V,
    128
};
static const char spider_leg_1_left[] = {
    -8, -8, 0xAA, 2|OAM_FLIP_H|OAM_FLIP_V,
    0,  -8, 0xA8, 2|OAM_FLIP_H|OAM_FLIP_V,
    128
};

///////////////////


static const char bat_damaged_stand_up[] = {
    -8, -8, 0x90, 1,
    0,  -8, 0x92, 1,
    128
};
static const char bat_damaged_stand_down[] = {
    -8, -8, 0x90, 1|OAM_FLIP_V,
    0,  -8, 0x92, 1|OAM_FLIP_V,
    128
};
static const char bat_damaged_stand_right[] = {
    -8, -8, 0xB0, 1,
    0,  -8, 0xB2, 1,
    128
};
static const char bat_damaged_stand_left[] = {
    -8, -8, 0xB2, 1|OAM_FLIP_H,
    0,  -8, 0xB0, 1|OAM_FLIP_H,
    128
};

static const char bat_damaged_attack_up[] = {
    -8, -8, 0x94, 1,
    0,  -8, 0x96, 1,
    128
};
static const char bat_damaged_attack_down[] = {
    -8, -8, 0x94, 1|OAM_FLIP_V,
    0,  -8, 0x96, 1|OAM_FLIP_V,
    128
};
static const char bat_damaged_attack_right[] = {
    -8, -8, 0xB4, 1,
    0,  -8, 0xB6, 1,
    128
};
static const char bat_damaged_attack_left[] = {
    -8, -8, 0xB6, 1|OAM_FLIP_H,
    0,  -8, 0xB4, 1|OAM_FLIP_H,
    128
};

static const char bat_damaged_leg_0_up[] = {
    -8, -8, 0x98, 1,
    0,  -8, 0x9A, 1,
    128
};
static const char bat_damaged_leg_0_down[] = {
    -8, -8, 0x98, 1|OAM_FLIP_V,
    0,  -8, 0x9A, 1|OAM_FLIP_V,
    128
};
static const char bat_damaged_leg_0_right[] = {
    -8, -8, 0xB8, 1,
    0,  -8, 0xBA, 1,
    128
};
static const char bat_damaged_leg_0_left[] = {
    -8, -8, 0xBA, 1|OAM_FLIP_H,
    0,  -8, 0xB8, 1|OAM_FLIP_H,
    128
};

static const char bat_damaged_leg_1_up[] = {
    -8, -8, 0x9A, 1|OAM_FLIP_H,
    0,  -8, 0x98, 1|OAM_FLIP_H,
    128
};
static const char bat_damaged_leg_1_down[] = {
    -8, -8, 0x9A, 1|OAM_FLIP_H|OAM_FLIP_V,
    0,  -8, 0x98, 1|OAM_FLIP_H|OAM_FLIP_V,
    128
};
static const char bat_damaged_leg_1_right[] = {
    -8, -8, 0xB8, 1|OAM_FLIP_V,
    0,  -8, 0xBA, 1|OAM_FLIP_V,
    128
};
static const char bat_damaged_leg_1_left[] = {
    -8, -8, 0xBA, 1|OAM_FLIP_H|OAM_FLIP_V,
    0,  -8, 0xB8, 1|OAM_FLIP_H|OAM_FLIP_V,
    128
};

static const char bat_stand_up[] = {
    -8, -8, 0x90, 2,
    0,  -8, 0x92, 2,
    128
};
static const char bat_stand_down[] = {
    -8, -8, 0x90, 2|OAM_FLIP_V,
    0,  -8, 0x92, 2|OAM_FLIP_V,
    128
};
static const char bat_stand_right[] = {
    -8, -8, 0xB0, 2,
    0,  -8, 0xB2, 2,
    128
};
static const char bat_stand_left[] = {
    -8, -8, 0xB2, 2|OAM_FLIP_H,
    0,  -8, 0xB0, 2|OAM_FLIP_H,
    128
};

static const char bat_attack_up[] = {
    -8, -8, 0x94, 2,
    0,  -8, 0x96, 2,
    128
};
static const char bat_attack_down[] = {
    -8, -8, 0x94, 2|OAM_FLIP_V,
    0,  -8, 0x96, 2|OAM_FLIP_V,
    128
};
static const char bat_attack_right[] = {
    -8, -8, 0xB4, 2,
    0,  -8, 0xB6, 2,
    128
};
static const char bat_attack_left[] = {
    -8, -8, 0xB6, 2|OAM_FLIP_H,
    0,  -8, 0xB4, 2|OAM_FLIP_H,
    128
};

static const char bat_leg_0_up[] = {
    -8, -8, 0x98, 2,
    0,  -8, 0x9A, 2,
    128
};
static const char bat_leg_0_down[] = {
    -8, -8, 0x98, 2|OAM_FLIP_V,
    0,  -8, 0x9A, 2|OAM_FLIP_V,
    128
};
static const char bat_leg_0_right[] = {
    -8, -8, 0xB8, 2,
    0,  -8, 0xBA, 2,
    128
};
static const char bat_leg_0_left[] = {
    -8, -8, 0xBA, 2|OAM_FLIP_H,
    0,  -8, 0xB8, 2|OAM_FLIP_H,
    128
};

static const char bat_leg_1_up[] = {
    -8, -8, 0x9A, 2|OAM_FLIP_H,
    0,  -8, 0x98, 2|OAM_FLIP_H,
    128
};
static const char bat_leg_1_down[] = {
    -8, -8, 0x9A, 2|OAM_FLIP_H|OAM_FLIP_V,
    0,  -8, 0x98, 2|OAM_FLIP_H|OAM_FLIP_V,
    128
};
static const char bat_leg_1_right[] = {
    -8, -8, 0xB8, 2|OAM_FLIP_V,
    0,  -8, 0xBA, 2|OAM_FLIP_V,
    128
};
static const char bat_leg_1_left[] = {
    -8, -8, 0xBA, 2|OAM_FLIP_H|OAM_FLIP_V,
    0,  -8, 0xB8, 2|OAM_FLIP_H|OAM_FLIP_V,
    128
};

