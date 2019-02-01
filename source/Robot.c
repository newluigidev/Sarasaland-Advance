#include <nds.h>
#include <nds/registers_alt.h>
#include "nsmb.h"
#include "Robot.h"

const int ROBOT_MODEL = 2098 - 0x83;
const int ROBOT_ANIM = 2099 - 0x83;

u32 robot_physics[] =
{
  0,
  0,
  0x10000,
  0x10000,
  0x930004,
  0xFFFE,
  (u32)&EnemyCollisionCallback,
};

u32 robot_headspin_physics[] =
{
  0,
  0,
  0x10000,
  0x8000,
  0x830A04,
  0xFFFE,
  (u32)&EnemyCollisionCallback
};

void Robot_setup(Robot* rbt)
{
  loadFileByExtId_3dModel(ROBOT_MODEL, 0);
  loadFileByExtId_3dModel(ROBOT_ANIM, 0);

  initActivePhysics(&rbt->activephysics, rbt, robot_physics, 0);
  registerCollider(&rbt->activephysics);

  modelAnim3d_ctor(&rbt->Model);
  modelAnim3d_setup(&rbt->Model, getPtrToLoadedFile(ROBOT_MODEL), getPtrToLoadedFile(ROBOT_ANIM), 0, 0, 0);
  modelAnim3d_init(&rbt->Model, 0, 0, 4096, 0);

  rbt->scale.x = 0x1500; rbt->scale.y = 0x1500;
  rbt->position.x += 0x8000;
  rbt->direction = 1;

  rbt->initPos = rbt->position;
  rbt->stopTimer = 0;
  rbt->deathTimer = 0;
}

void Robot_draw(Robot* rbt)
{
  DrawAModel(&rbt->Model, &rbt->position, &rbt->rotation, &rbt->scale);
}

void Robot_execute(Robot* rbt)
{
  anim3d_update(&rbt->Model.anim);
  MarioActor* mario = (MarioActor*)getPtrToPlayerActor();

  AffectByGravity(rbt);

  if (rbt->direction == 0)
    rbt->velocity.x = 0x1000;
  else
    rbt->velocity.x = -0x1000;

  u32 xPosL = (rbt->position.x >> 12) / 16;
  u32 yPosL = ((-rbt->position.y) >> 12) / 16;

  u32 xPosR = ((rbt->position.x + 0x8000) >> 12) / 16;
  u32 yPosR = ((-rbt->position.y) >> 12) / 16;

  int tbL = getTileBehaviorAtPos2(xPosL*16, yPosL*16);
  int tbNL = (tbL & 0xF0) >> 4;

  int tbR = getTileBehaviorAtPos2(xPosR*16, yPosR*16);
  int tbNR = (tbR & 0xF0) >> 4;

  if (rbt->position.x == (rbt->initPos.x) + 0x20000 || rbt->position.x == (rbt->initPos.x) - 0x20000)
    rbt->stopTimer = 0;

  if (tbNL == 0xF || rbt->position.x == (rbt->initPos.x) - 0x60000)
  {
    if (rbt->stopTimer < 80)
    {
      UnregisterActivePhysics(&rbt->activephysics);

      rbt->headSpin = true;
      ++rbt->stopTimer;
      modelAnim3d_init(&rbt->Model, 1, 0, 4096, 0);
      rbt->velocity.x = 0;
    }

    if (rbt->stopTimer == 80)
    {
      registerCollider(&rbt->activephysics);

      rbt->headSpin = false;
      modelAnim3d_init(&rbt->Model, 0, 0, 4096, 0);
      rbt->direction = 0;
    }
  }

  else if (tbNR == 0xF || rbt->position.x == (rbt->initPos.x) + 0x60000)
  {
    if (rbt->stopTimer < 80)
    {
      UnregisterActivePhysics(&rbt->activephysics);

      rbt->headSpin = true;
      ++rbt->stopTimer;
      modelAnim3d_init(&rbt->Model, 1, 0, 4096, 0);
      rbt->velocity.x = 0;
    }

    if (rbt->stopTimer == 80)
    {
      registerCollider(&rbt->activephysics);

      rbt->headSpin = false;
      modelAnim3d_init(&rbt->Model, 0, 0, 4096, 0);
      rbt->direction = 1;
    }
  }
}

void Robot_Stomp(Robot* rbt)
{
  SpawnParticle(0x7A, &rbt->position);
  Base__deleteIt(rbt);
}

void Robot_Defeat(Robot* rbt)
{
  return;
}
