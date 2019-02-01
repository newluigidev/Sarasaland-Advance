#include <nds.h>
#include <nds/registers_alt.h>
#include "nsmb.h"
#include "Gao.h"

const int GAO_MODEL = 2102 - 0x83;
int flametimer;

u32 Gao_physics[] =
{
  0,
  0,
  0xF000,
  0xF000,
  0x930004,
  0xFFFE,
  (u32)&EnemyCollisionCallback
};

void Gao_setup(Gao* go)
{
  initActivePhysics(&go->activephysics, go, Gao_physics, 0);
  registerCollider(&go->activephysics);

  loadFileByExtId_3dModel(GAO_MODEL, 0);

  model3d_ctor(&go->Model);
  model3d_setup(&go->Model, getPtrToLoadedFile(GAO_MODEL), 0);
  model3d_init(&go->Model);

  go->scale.x = 0x1500; go->scale.y = 0x1500; go->scale.z = 0x1500;
  go->position.x += 0x8000;

  flametimer = 0;
}

void Gao_draw(Gao* go)
{
  DrawAModel(&go->Model, &go->position, &go->rotation, &go->scale);
}

void Gao_execute(Gao* go)
{
  Vec3 spawnPos;
  spawnPos.x = go->position.x - 0x1000;
  spawnPos.y = go->position.y + 0x2000;
  spawnPos.z = go->position.z;

  if (flametimer < 80)
    ++flametimer;

  if (flametimer == 80)
  {
    createActor(82, 0, &spawnPos, 0, 0, 0);
    PlaySNDEffect(360, 0);
    flametimer = 0;
  }
}

void Gao_Stomp(Gao* go)
{
  SpawnParticle(0x7A, &go->position);
  Base__deleteIt(go);
}
