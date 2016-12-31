#pragma once

#include <Windows.h>

struct Game;

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

void SendMsgToClient(DWORD dwClientId, const char* format, ...);
void _SendMsgToClient(DWORD dwClientId, const char* format, va_list arguments);
void SendMsgToGame(Game* pGame, int dwLevel, const char* format, ...);
