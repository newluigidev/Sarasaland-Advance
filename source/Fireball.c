#include <nds.h>
#include <nds/registers_alt.h>
#include "Fireball.h"
#include "nsmb.h"

const int FIREBALL_TEX = 1961 - 0x83;
int y;
int framecount;

u32 Fireball_physics[] =
{
  0x8000,
  0x8000,
  0xA000,
  0xA000,
  0x130A04,
  0x0000,
  (u32)&EnemyCollisionCallback,
};

void Fireball_setup(Fireball* fbl)
{
  initActivePhysics(&fbl->activephysics, fbl, Fireball_physics, 0);
  registerCollider(&fbl->activephysics);

  u32 file = loadFileByExtId_3dModel(FIREBALL_TEX, 0);
  u32 tex = NNS_G3dGetTex(file);

  getTextureParams(tex, 0, &fbl->tex.texparam);
	getTexturePalBase(tex, 0, &fbl->tex.palbase);

  y = 0;
  framecount = 0;

  fbl->position.x -= 0x8000;
  fbl->position.z = 0x220000;
}

void Fireball_execute(Fireball* fbl)
{
  if ((fbl->spriteData) & 0x1)
  {
    fbl->position.x -= 0x1000;
    fbl->position.y -= 0x1000;
  }

  else fbl->position.x -= 0x1000;

  u32 xPos = (((fbl->position.x) + 0x8000) >> 12) / 16;
  u32 yPos = (((-fbl->position.y) - 0x10000) >> 12) / 16;
  int tb = getTileBehaviorAtPos2(xPos*16, yPos*16);

  if ((!(tb >> 0x10 & 0x2)) && (tb))
  {
    SpawnParticle(0xAC, &fbl->position); SpawnParticle(0xAD, &fbl->position);
    PlaySNDEffect(293, 0);
    Base__deleteIt(fbl);
  }
}

inline void vec3(int x, int y, int z)
{
	REG_VERTEX16 = (y << 16) | (x & 0xFFFF);
	REG_VERTEX16 = (z & 0xFFFF);
}

inline void texcoord2(int x, int y)
{
	REG_TEXT_COORD = (y << 16) | (x & 0xFFFF);
}

void Fireball_draw(Fireball* fbl)
{
  if (framecount < 4)
    ++framecount;

  if (framecount == 4)
  {
    if (y == 0x300)
      y = 0;
    y += 0x100;
    framecount = 0;
  }

	G3_LoadMtx43(0x02085B20);

	// this+0x5C -> sprite pos (vec3)
	REG_MTX_TRANSLATE = fbl->position.x;
	REG_MTX_TRANSLATE = fbl->position.y;
	REG_MTX_TRANSLATE = fbl->position.z;

	REG_MTX_SCALE = 0x10000;
	REG_MTX_SCALE = 0x10000;
	REG_MTX_SCALE = 0x10000;

	REG_MTX_CONTROL = 3;
	REG_MTX_IDENTITY = 0;
	REG_MTX_CONTROL = 2;

	REG_POLY_FORMAT = 0x001F3880;
	REG_TEXT_FORMAT = fbl->tex.texparam;
	(*(vu32*) 0x40004AC) = fbl->tex.palbase;

	REG_COLOR = 0x7FFF;

	REG_GFX_BEGIN = 1;

	texcoord2(0x100, y);
	vec3(0x1000, 	0x1000, 	0);

	texcoord2(0, y);
	vec3(0, 		0x1000, 	0);

	texcoord2(0, y+0x100);
	vec3(0, 		0,			0);

	texcoord2(0x100, y+0x100);
	vec3(0x1000,	0,			0);

	REG_GFX_END = 0;
}
