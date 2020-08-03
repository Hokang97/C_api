#pragma once
#include <Windows.h>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <fstream>
using namespace std;

#define BTN_STATE_NORMAL	0x0000
#define BTN_STATE_HOVER		0x0001
#define BTN_STATE_CLICKED	0x0002
typedef struct CropRect
{
	DWORD x;
	DWORD y;
	DWORD width;
	DWORD height;
} CRECT;

#define TAG_START_BUTTON "tag_start_btn"
#define TAG_EXIT_BUTTON "tag_exit_btn"

#define TILE_SIZE 64
#define ORI_TILE_SIZE 128

#define TILE_NUM_X 10
#define TILE_NUM_Y 10

enum MoveType { NONE, UP, DOWN, LEFT, RIGHT };
