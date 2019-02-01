#include <nds.h>
#include <nds/registers_alt.h>
#include "Exit.h"
#include "nsmb.h"

const int EXIT = 2089 - 0x83;

u32 Exit_physics[] =
{
  0,
  0x8000,
  0x8000,
  0x8000,
  0x930006,
	0x80000400,
  (u32)&Exit_CollisionCallback
};

void Exit_setup(Exit* ex)
{
  ex->gotten = false;
  ex->exitTimer = 0;
  initActivePhysics(&ex->activephysics, ex, Exit_physics, 0);
  registerCollider(&ex->activephysics);

  u32 file = loadFileByExtId_3dModel(EXIT, 0);
  u8* tex = (u8*) NNS_G3dGetTex((u32*)getPtrToLoadedFile(EXIT));

  switch ((ex->spriteData >> 8) & 0xF) //Nybble 10
  {
    case 0: //Birabuto
    {
      getTextureParams(tex, 0, &ex->tex.texparam);
      getTexturePalBase(tex, 0, &ex->tex.palbase);
      break;
    }

    case 1: //Muda
    {
      getTextureParams(tex, 1, &ex->tex.texparam);
      getTexturePalBase(tex, 1, &ex->tex.palbase);
      break;
    }
    case 2: //Muda-2
    {
      getTextureParams(tex, 2, &ex->tex.texparam);
      getTexturePalBase(tex, 2, &ex->tex.palbase);
      break;
    }
    case 3: //Muda-3
    {
      getTextureParams(tex, 3, &ex->tex.texparam);
      getTexturePalBase(tex, 3, &ex->tex.palbase);
      break;
    }
    default:
      break;
  }

  ex->secretExit = false;
}

void Exit_execute(Exit* ex)
{
  MarioActor* mario = (MarioActor*)getPtrToPlayerActor();
  int* EntranceDestArea = (int*)0x208B09C;
  u32* GotSecretExit = (u32*)0x02085AC8;
  u32* freezeTimer = (u32*)0x020CA898;
  ex->position.z = 0x220000;

  if (ex->gotten == true)
  {
    *freezeTimer |= 8u;

    mario->direction = 0;
    ++ex->exitTimer;

    if (ex->exitTimer < 40)
      mario->xVelocity = 0x1000;

    if (ex->exitTimer == 50)
      Base__deleteIt(mario);

    if (ex->exitTimer == 180)
    {
      if (ex->secretExit == true)
      {
        *EntranceDestArea = 176;
        setEntranceIdForPlayer(0, 0);
        enterEntrance(mario, 0);
      }
      else
      {
        //u32* currentArea = (u32*)0x02085A94;
        exitLevel(1);
        //*EntranceDestArea = *currentArea + 3;
        //setEntranceIdForPlayer(0, 0);
        //enterEntrance(mario, 0);
      }
      ex->exitTimer = 0;
      ex->gotten = false;
    }
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

void Exit_draw(Exit* ex)
{
	G3_LoadMtx43(0x02085B20);

	// this+0x5C -> sprite pos (vec3)
	REG_MTX_TRANSLATE = ex->position.x + 0x10000;
	REG_MTX_TRANSLATE = ex->position.y;
	REG_MTX_TRANSLATE = ex->position.z;

	REG_MTX_SCALE = 0x10000;
	REG_MTX_SCALE = 0x10000;
	REG_MTX_SCALE = 0x10000;

	REG_MTX_CONTROL = 3;
	REG_MTX_IDENTITY = 0;
	REG_MTX_CONTROL = 2;

	REG_POLY_FORMAT = 0x001F3880;
	REG_TEXT_FORMAT = ex->tex.texparam;
	(*(vu32*) 0x40004AC) = ex->tex.palbase;

	REG_COLOR = 0x7FFF;

	REG_GFX_BEGIN = 1;

	texcoord2(0x200, 0);
	vec3(0x2000, 	0x2000, 	0);

	texcoord2(0, 0);
	vec3(0, 		0x2000, 	0);

	texcoord2(0, 0x200);
	vec3(0, 		0,			0);

	texcoord2(0x200, 0x200);
	vec3(0x2000,	0,			0);

	REG_GFX_END = 0;
}

void Exit_CollisionCallback(ActivePhysics* a, ActivePhysics* b)
{
  Exit* ex = (Exit*)a->owner;

  if (ex->gotten == false)
  {
    if ((ex->spriteData >> 28) & 0x1) //Nybble 5
      ex->secretExit = true;

    ex->gotten = true;
    UnregisterActivePhysics(&ex->activephysics);

    PlaySNDEffect(205, 0);
    PlayMusicFile(4, 0);
  }
}
