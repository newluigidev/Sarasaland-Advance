#include <nds.h>
#include <nds/registers_alt.h>
#include "nsmb.h"
#include "BlooperThing.h"
#include "Projectile.h"

const int Blooper_MODEL = 1433 - 0x83;
const int Blooper_ANIM = 1422 - 0x83;

int hitsTaken;

u32 Blooper_physics[] =
{
  0,
  0,
  0x8000,
  0x16000,
  0x930004,
  0xFFFE,
  (u32)&Blooper_CollisionCallback
};

void Blooper_setup(Blooper* bf)
{
  initActivePhysics(&bf->activephysics, bf, Blooper_physics, 0);
  registerCollider(&bf->activephysics);

  loadFileByExtId_3dModel(Blooper_MODEL, 0);
  loadFileByExtId_3dModel(Blooper_ANIM, 0);

  modelAnim3d_ctor(&bf->Model);
  modelAnim3d_setup(&bf->Model, getPtrToLoadedFile(Blooper_MODEL), getPtrToLoadedFile(Blooper_ANIM), 0, 0, 0);
  modelAnim3d_init(&bf->Model, 0, 0, 2048, 0);

  /*model3d_ctor(&bf->Model);
  model3d_setup(&bf->Model, getPtrToLoadedFile(Blooper_MODEL), 0);
  model3d_init(&bf->Model);*/

  if ((bf->spriteData >> 8) & 0x1)
    bf->position.x += 0x8000;

  hitsTaken = 0;
}

void Blooper_draw(Blooper* bf)
{
  DrawAModel(&bf->Model, &bf->position, &bf->rotation, &bf->scale);
}

void Blooper_execute(Blooper* bf)
{
  anim3d_update(&bf->Model.anim);
  //createActor(82, 0, &bf->position, 0, 0, 0);
}

void Blooper_CollisionCallback(ActivePhysics* a, ActivePhysics* b)
{
  Blooper* bf = (Blooper*)a->owner;
  EnemyClassObject* enemy = (EnemyClassObject*)b->owner;

  if (enemy->ClassID == 0x6B)
  {
    ++hitsTaken;
    SpawnParticle(0x7A, &enemy->position);
    PlaySNDEffect(363, 0);
    Base__deleteIt(enemy);

    if (hitsTaken == 3)
    {
      createActor(82, 0, &bf->position, 0, 0, 0);
      SpawnParticle(0x7A, &bf->position);
      PlaySNDEffect(0x70, 0);
      get1up(1, 0);
      Base__deleteIt(bf);
    }
  }
}

void Blooper_Defeat(Blooper* bf)
{
  createActor(82, 0, &bf->position, 0, 0, 0);
  get1up(1, 0);
  SpawnParticle(0x7A, &bf->position);
  Base__deleteIt(bf);
}

void Blooper_Stomp(Blooper* bf)
{
  return;
}
