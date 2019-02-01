#include "nsmb.h"
#include "enemy.h"

u32 explodeAP[] =
{
  0,
  0,
  0x20000,
  0x20000,
  0x930004,
  0xFFFE,
  (u32)&ShellCollisionCallback
};

void actorExplode(EnemyClassObject* i)
{
  initActivePhysics(&i->activephysics, i, explodeAP, 0);
  registerCollider(&i->activephysics);

  SpawnParticle(0x13, &i->position);
  SpawnParticle(0x14, &i->position);
  SpawnParticle(0x15, &i->position);
  SpawnParticle(0x16, &i->position);
  SpawnParticle(0x17, &i->position);
  SpawnParticle(0x18, &i->position);
  SpawnParticle(0x19, &i->position);

  PlaySNDEffect(0x69, &i->position);
}
