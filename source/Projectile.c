#include <nds.h>
#include <nds/registers_alt.h>
#include "Projectile.h"
#include "nsmb.h"

const int BOMB_MODEL = 1331 - 0x83;

u32 SkeeterBomb_Physics[] =
{
  0,
  0,
  0x8000,
  0x8000,
  0x830A04,
  0xFFFE,
  (u32)&EnemyCollisionCallback,
};

u32 SubmarineBomb_Physics[] =
{
  0,
  0,
  0x8000,
  0x8000,
  0x930004,
  0xFFFE,
  (u32)&SubmarineBomb_CollisionCallback,
};

void Projectile_setup(Projectile* pj)
{
  u8 nybble10 = pj->spriteData >> 8 & 0xF;

  switch (nybble10)
  {
    case 1: //Setup Skeeter Bomb
    {
      loadFileByExtId_3dModel(BOMB_MODEL, 0);

      initActivePhysics(&pj->activephysics, pj, SkeeterBomb_Physics, 0);
      registerCollider(&pj->activephysics);

      model3d_ctor(&pj->Model);
      model3d_setup(&pj->Model, getPtrToLoadedFile(BOMB_MODEL), 0);
      model3d_init(&pj->Model);
      break;
    }
    case 2:
    {
      loadFileByExtId_3dModel(BOMB_MODEL, 0);

      initActivePhysics(&pj->activephysics, pj, SubmarineBomb_Physics, 0);
      registerCollider(&pj->activephysics);

      model3d_ctor(&pj->Model);
      model3d_setup(&pj->Model, getPtrToLoadedFile(BOMB_MODEL), 0);
      model3d_init(&pj->Model);

      pj->rotation.z = 0x4000;
      break;
    }
    default:
      return;
  }
}

void Projectile_execute(Projectile* pj)
{
  u8 nybble10 = pj->spriteData >> 8 & 0xF;

  //anim3d_update(&pj->Model.anim);

  switch (nybble10)
  {
    case 1: //Skeeter Bomb execution
    {
      pj->position.y -= 0x1000;

      u32 xPos = (pj->position.x >> 12) / 16;
      u32 yPos = ((-pj->position.y) >> 12) / 16;

      int tb = getTileBehaviorAtPos2(xPos*16, yPos*16);

      if ((!(tb >> 0x10 & 0x2)) && (tb))
      {
        SpawnParticle(0x79, &pj->position); SpawnParticle(0x7A, &pj->position);
        PlaySNDEffect(0x70, &pj->position);
        Base__deleteIt(pj);
      }
      break;
    }
    case 2:
    {
      pj->position.x += 0x2000;

      u32 xPos = (pj->position.x >> 12) / 16;
      u32 yPos = ((-pj->position.y) >> 12) / 16;

      int tb = getTileBehaviorAtPos2(xPos*16, yPos*16);

      if (tb & 0x100000)
      {
        if (tb & 1) //The next three IFs are lazy copypaste, but whatever.
        {
          createActor(31, 0xC0080103, &pj->position, 0, 0, 0);
          PlaySNDEffect(372, 0);
        }

        else if (tb & 2)
        {
          createActor(31, 0xC0080101, &pj->position, 0, 0, 0);
          PlaySNDEffect(372, 0);
        }

        else if (tb & 3)
        {
          createActor(31, 0xC0080127, &pj->position, 0, 0, 0);
          PlaySNDEffect(372, 0);
        }

        changeTile(ptrToLevelActor, pj->position.x>>12, -pj->position.y>>12, 0);
        createActor(0xF1, 0x600000, &pj->position, 0, 0, 0);
        SpawnParticle(0x79, &pj->position); SpawnParticle(0x7A, &pj->position);
        PlaySNDEffect(375, &pj->position);
        Base__deleteIt(pj);
      }

      else if (!(tb >> 0x10 & 0x2) && (tb))
      {
        SpawnParticle(0x79, &pj->position); SpawnParticle(0x7A, &pj->position);
        PlaySNDEffect(0x70, &pj->position);
        Base__deleteIt(pj);
      }
      break;
    }
    default:
      break;
  }
}

void Projectile_draw(Projectile* pj)
{
  DrawAModel(&pj->Model, &pj->position, &pj->rotation, &pj->scale);
}

void Projectile_FireballCallback(Projectile* pj)
{
  SpawnParticle(0x79, &pj->position); SpawnParticle(0x7A, &pj->position);
  PlaySNDEffect(0x70, &pj->position);
  Base__deleteIt(pj);
}

void SubmarineBomb_CollisionCallback(ActivePhysics* a, ActivePhysics* b)
{
  Projectile* pj = (Projectile*)a->owner;
  EnemyClassObject* enemy = (EnemyClassObject*)b->owner;

  if (!(enemy->ClassID == 0x15 || enemy->ClassID == 0x1F || enemy->ClassID == 22 || enemy->ClassID == 0x6B || enemy->ClassID == 0x44))
  {
    SpawnParticle(0x79, &pj->position); SpawnParticle(0x7A, &pj->position);
    PlaySNDEffect(0x70, &pj->position);
    Base__deleteIt(enemy);
    Base__deleteIt(pj);
  }
}
