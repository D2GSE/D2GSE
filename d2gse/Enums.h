#pragma once

#define COLOR_RED "\xFF""c1"
#define COLOR_GREEN "\xFF""c2"
#define COLOR_BLUE "\xFF""c3"
#define COLOR_GOLD "\xFF""c4"
#define COLOR_GRAY "\xFF""c5"
#define COLOR_BLACK "\xFF""c6"
#define COLOR_DARK_YELLOW "\xFF""c7"
#define COLOR_ORANGE "\xFF""c8"
#define COLOR_YELLOW "\xFF""c9"
#define COLOR_PURPLE "\xFF""c;"
#define COLOR_DARK_GREEN_1 "\xFF""c:"   // darkest
#define COLOR_DARK_GREEN_2 "\xFF""c<"

#define COLOR_COMMON "\xFF""c0"
#define COLOR_BOLD_WHITE_1 "\xFF""c."   // boldest
#define COLOR_BOLD_WHITE_2 "\xFF""c-"
#define COLOR_BOLD_WHITE_3 "\xFF""c+"
#define COLOR_BOLD_WHITE_4 "\xFF""c'"
#define COLOR_BOLD_WHITE_5 "\xFF""c\""

enum ItemQuality
{
    ITEM_QUALITY_LOW = 1,
    ITEM_QUALITY_NORMAL = 2,
    ITEM_QUALITY_SUPERIOR = 3,
    ITEM_QUALITY_MAGIC = 4,
    ITEM_QUALITY_SET = 5,
    ITEM_QUALITY_RARE = 6,
    ITEM_QUALITY_UNIQUE = 7,
    ITEM_QUALITY_CRAFT = 8,
    ITEM_QUALITY_TEMPERED = 9,
};

enum UnitType
{
    UNIT_TYPE_PLAYER = 0,
    UNIT_TYPE_NPC = 1,
    UNIT_TYPE_MONSTER = 1,
    UNIT_TYPE_OBJECT = 2,
    UNIT_TYPE_MISSILE = 3,
    UNIT_TYPE_ITEM = 4,
    UNIT_TYPE_TILE = 5
};
