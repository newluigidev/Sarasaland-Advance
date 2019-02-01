#include <nds.h>
#include <nds/registers_alt.h>
#include <math.h>
#include "Fly.h"
#include "nsmb.h"

const int FLY_MODEL = 2090 - 0x83;
const int FLY_ANIM = 2091 - 0x83;

u32 Fly_physics[] =
{
  0,
  0,
  0xF000,
  0xF000,
  0x930004,
  0xFFFE,
  (u32)&EnemyCollisionCallback
};

void Fly_setup(Fly* fl)
{
  loadFileByExtId_3dModel(FLY_MODEL, 0);
  loadFileByExtId_3dModel(FLY_ANIM, 0);

  initActivePhysics(&fl->activephysics, fl, Fly_physics, 0);
	registerCollider(&fl->activephysics);

  modelAnim3d_ctor(&fl->Model);
  modelAnim3d_setup(&fl->Model, getPtrToLoadedFile(FLY_MODEL), getPtrToLoadedFile(FLY_ANIM), 0, 0, 0);
  modelAnim3d_init(&fl->Model, 0, 0, 4096, 0);

  fl->scale.x = 0x2000; fl->scale.y = 0x2000;
  fl->position.y -= 0x8000; fl-> position.x += 0x10000;
  fl->jumpTimer = 0;
  fl->direction = 0;
}

void Fly_execute(Fly* fl)
{
  DeleteIfOutOfRange(fl, 0);
  anim3d_update(&fl->Model.anim);
  AffectByGravity(fl);
  sub_20A08A4(fl);

  ++fl->jumpTimer;

  u32 xPos = (fl->position.x >> 12) / 16;
  u32 yPos = ((-fl->position.y) >> 12) / 16;

  u32 xPosSideL = ((fl->position.x - 0x8000) >> 12) / 16;
  u32 yPosSideL = ((-fl->position.y - 0x8000) >> 12) / 16;

  u32 xPosSideR = ((fl->position.x + 0x8000) >> 12) / 16;
  u32 yPosSideR = ((-fl->position.y - 0x8000) >> 12) / 16;

  int tb = getTileBehaviorAtPos2(xPos*16, yPos*16);
  int tbSideL = getTileBehaviorAtPos2(xPosSideL*16, yPosSideL*16);
  int tbSideR = getTileBehaviorAtPos2(xPosSideR*16, yPosSideR*16);

  if ((!(tb >> 0x10 & 0x2)) && (tbSideL))
  {
      fl->velocity.x = 0;
      fl->direction = 1;
  }

  if ((!(tb >> 0x10 & 0x2)) && (tbSideR))
  {
    fl->velocity.x = 0;
    fl->direction = 0;
  }

  if ((!(tb >> 0x10 & 0x2)) && (tb))
  {
    fl->velocity.y = 0;
    fl->velocity.x = 0;

    if (fl->jumpTimer == 120)
    {
      PlaySNDEffect(0xA0, &fl->position);
      fl->velocity.y = 0x4000;

      if (fl->direction == 1)
        fl->velocity.x += 0x1000;
      else
        fl->velocity.x -= 0x1000;

      fl->jumpTimer = 0;
    }
  }
}

void Fly_Stomp(Fly* fl)
{
  SpawnParticle(0x7A, &fl->position);
  Base__deleteIt(fl);
}

void Fly_Defeat(Fly* fl)
{
  get1up(2, 0);
  SpawnParticle(0x7A, &fl->position);
  Base__deleteIt(fl);
}

void Fly_FireballCallback(Fly* fl) //I'm an idiot
{
  get1up(2, 0);
  createActor(66, 3, &fl->position, 0, 0, 0);
  PlaySNDEffect(0x70, &fl->position);
  SpawnParticle(0x7A, &fl->position);
  Base__deleteIt(fl);
}

void Fly_draw(Fly* fl)
{
  DrawAModel(&fl->Model, &fl->position, &fl->rotation, &fl->scale);
}
