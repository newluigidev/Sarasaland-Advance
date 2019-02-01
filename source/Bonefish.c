#include <nds.h>
#include <nds/registers_alt.h>
#include "nsmb.h"
#include "Bonefish.h"

const int BONEFISH_MODEL = 2096 - 0x83;
const int BONEFISH_ANIM = 2097 - 0x83;

u32 fishbone_physics[] =
{
  0,
  0,
  0x8000,
  0x16000,
  0x930004,
  0xFFFE,
  (u32)&EnemyCollisionCallback
};

void Bonefish_setup(Bonefish* bf)
{
  initActivePhysics(&bf->activephysics, bf, fishbone_physics, 0);
  registerCollider(&bf->activephysics);

  loadFileByExtId_3dModel(BONEFISH_MODEL, 0);
  loadFileByExtId_3dModel(BONEFISH_ANIM, 0);

  modelAnim3d_ctor(&bf->Model);
  modelAnim3d_setup(&bf->Model, getPtrToLoadedFile(BONEFISH_MODEL), getPtrToLoadedFile(BONEFISH_ANIM), 0, 0, 0);
  modelAnim3d_init(&bf->Model, 0, 0, 8000, 0);

  /*model3d_ctor(&bf->Model);
  model3d_setup(&bf->Model, getPtrToLoadedFile(BONEFISH_MODEL), 0);
  model3d_init(&bf->Model);*/

  if ((bf->spriteData >> 8) & 0x1)
    bf->position.x += 0x8000;

  bf->jumpHeight = (bf->spriteData >> 16 & 0xF) * 0x10000;

  bf->doSplash = false;
  bf->chompTimer = 0;
}

void Bonefish_draw(Bonefish* bf)
{
  DrawAModel(&bf->Model, &bf->position, &bf->rotation, &bf->scale);
}

void Bonefish_execute(Bonefish* bf)
{
  //nocashPrint1("%r0%\n", bf->jumpHeight);

  anim3d_update(&bf->Model.anim);
  EnemyClassObject* water = (EnemyClassObject*)findActorByType(0x116, 0);
  EnemyClassObject* poisonwater = (EnemyClassObject*)findActorByType(0x119, 0);

  AffectByGravity(bf);

  //nocashPrint1("%r0%\n", bf->doSplash);

  if ((bf->position.y == poisonwater->position.y) || (bf->position.y == water->position.y))
  {
    if (bf->doSplash == true)
    {
      if ((bf->spriteData & 0xF) != 1)
      {
        SpawnParticle(0xA3, &bf->position);
        SpawnParticle(0xA4, &bf->position);
        DoWavesInLiquid(bf->position.x, 1);
        PlaySNDEffect(356, &bf->position);
      }
      bf->doSplash = false;
    }

    if (bf->freezeTimer < 60)
    {
      bf->chompTimer = 0;
      bf->velocity.y = 0;
      ++bf->freezeTimer;
    }

    if (((bf->position.y - poisonwater->position.y) < (bf->jumpHeight) && bf->freezeTimer == 60)
        || ((bf->position.y - water->position.y) < (bf->jumpHeight) && bf->freezeTimer == 60))
    {
      modelAnim3d_init(&bf->Model, 1, 0, 8000, 0);
      if ((bf->spriteData & 0xF) != 1)
      {
        SpawnParticle(0xA3, &bf->position);
        SpawnParticle(0xA4, &bf->position);
        DoWavesInLiquid(bf->position.x, 1);
        PlaySNDEffect(356, &bf->position);
      }
      bf->freezeTimer = 0;
      bf->velocity.y = 0x2000;
    }
  }

  if (((bf->position.y - poisonwater->position.y) >= (bf->jumpHeight) - 0x20000)
      || ((bf->position.y - water->position.y) >= (bf->jumpHeight) - 0x20000))
  {
    bf->chompTimer = 0;
    modelAnim3d_init(&bf->Model, 0, 0, 8000, 0);
    bf->velocity.y -= 0x100;
    bf->doSplash = true;
  }
}

void Bonefish_Defeat(Bonefish* bf)
{
  get1up(1, 0);
  SpawnParticle(0x7A, &bf->position);
  Base__deleteIt(bf);
}

void Bonefish_Stomp(Bonefish* bf)
{
  SpawnParticle(0x7A, &bf->position);
  Base__deleteIt(bf);
}
