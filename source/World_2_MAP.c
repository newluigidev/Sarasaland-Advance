#include "worldmap.h"

path w2_path_0[] =
{
	{1, 0, 1, 0},
	{255, 0, 0, 0}
};

path w2_path_1[] =
{
	{0, 0, 67, 0},
	{3, 3, 0, 0},
	{2, 1, 1, 0},
	{255, 0, 0, 0}
};

path w2_path_2[] =
{
	{1, 1, 67, 0},
	{4, 2, 1, 0},
	{255, 0, 0, 0}
};

path w2_path_3[] =
{
	{1, 3, 67, 0},
	{4, 4, 1, 0},
	{255, 0, 0, 0}
};

path w2_path_4[] =
{
	{2, 2, 66, 0},
	{3, 4, 67, 0},
	{5, 5, 1, 0},
	{255, 0, 0, 0}
};

path w2_path_5[] =
{
	{4, 5, 67, 0},
	{255, 0, 0, 0}
};

node w2_nodes[] =
{
	{ w2_path_0, 0, 0, 0, 0, 8, {0, 0, 0} },
	{ w2_path_1, 21, 0, 0, 1, 8, {0, 0, 0} },
	{ w2_path_2, 24, 0, 0, 2, 8, {0, 0, 0} },
	{ w2_path_3, 177, 0, 0, 17, 8, {0, 0, 0} },
	{ w2_path_4, 0, 0, 0, 20, 0, {0, 0, 0} },
	{ w2_path_5, 26, 0, 0, 3, 8, {0, 0, 0} }
};

visibleNode w2_visibleNodes[] =
{
	{ {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0, -219, 25, -14 },
	{ {3, 1, 4, 0}, {0, 0, 0, 0}, 2, 0, -139, 25, -32 },
	{ {2, 5, 0, 0}, {0, 0, 0, 0}, 5, 0, 38, 25, -64 },
	{ {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0, -72, 25, 93 },
	{ {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0, 100, 25, 50 },
	{ {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0, 176, 38, 42 }
};

pathBehavior w2_pathBehaviors[] =
{
	{0, 0, 0, 0},
	{1, 0, 0, 0},
	{2, 0, 0, 0},
	{3, 0, 0, 0},
	{4, 0, 0, 0},
	{5, 0, 0, 0}
};

mapObject w2_starCoinSigns[] =
{
	{ 0x00, {0x00, 0x00, 0x00}, 0, 0, 0 }
};

mapObject w2_towersCastles[] =
{
	{ 0xFF, {0xFF, 0xFF, 0xFF}, 0, 0, 0 }
};

mapObject w2_mushroomHouses[] =
{
	{ 3, {0, 0, 0}, -323584, 102400, 237568 },
	{ 0xFF, {0xFF, 0xFF, 0xFF}, 0, 0, 0 }
};

sprites w2_sprites =
{
	1, 0, 5, 0
};
