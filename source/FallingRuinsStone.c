#include <nds.h>
#include <nds/registers_alt.h>
#include "FallingRuinsStone.h"
#include "nsmb.h"

u32 Stone_Physics[] =
{
  0,
  0,
  0x16000,
  0x8000,
  0x830A04,
  0xFFFE,
  (u32)&EnemyCollisionCallback,
};

const int STONE_MODEL = 2092 - 0x83;

void Stone_setup(Stone* stn)
{
  initActivePhysics(&stn->activephysics, stn, Stone_Physics, 0);
  registerCollider(&stn->activephysics);

  loadFileByExtId_3dModel(STONE_MODEL, 0);

  model3d_ctor(&stn->Model);
  model3d_setup(&stn->Model, getPtrToLoadedFile(STONE_MODEL), 0);
  model3d_init(&stn->Model);

  stn->scale.x = 0x1000;
  stn->stoneFall = false;
}

void Stone_execute(Stone* stn)
{
  EnemyClassObject* mario = (EnemyClassObject*)getPtrToPlayerActor();

  Vec3 pos;
  pos.x = stn->position.x - 0x12000;
  pos.y = stn->position.y;
  pos.z = stn->position.z;

  int xoffs = stn->position.x - mario->position.x;
  u32 xPos = (stn->position.x >> 12) / 16;
  u32 yPos = ((-stn->position.y) >> 12) / 16;
  int tb = getTileBehaviorAtPos2(xPos*16, yPos*16);

  if (xoffs <= 0x20000 || xoffs <= -0x62000 && (mario->position.y < stn->position.y))
    stn->stoneFall = true;

  else if (mario->position.y > stn->position.y)
    stn->stoneFall = false;

  if (stn->stoneFall == true)
  {
    stn->velocity.y -= 0x200; stn->position.y += stn->velocity.y;
  }

  if ((!(tb >> 0x10 & 0x2)) && (tb))
  {
    SpawnParticle(0x3A, &pos); //createActor(0xF1, 0x01000030, &stn->position, 0, 0, 0);
    PlaySNDEffect(375, &stn->position);
    stn->stoneFall = false;
    Base__deleteIt(stn);
  }
}

void Stone_draw(Stone* stn)
{
	DrawAModel(&stn->Model, &stn->position, &stn->rotation, &stn->scale);
}
