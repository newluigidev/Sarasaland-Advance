#include <nds.h>
#include <nds/registers_alt.h>
#include "nsmb.h"
#include "Torion.h"

const int TORION_MODEL = 1599 - 0x83;
const int TORION_ANIM = 1598 - 0x83;

u32 Torion_physics[] =
{
  0,
  0,
  0x8000,
  0x8000,
  0xB30004,
  0xFFFE,
  (u32)&EnemyCollisionCallback,
};

void Torion_setup(Torion* tn)
{
  initActivePhysics(&tn->activephysics, tn, Torion_physics, 0);
  registerCollider(&tn->activephysics);

  loadFileByExtId_3dModel(TORION_MODEL, 0);
  loadFileByExtId_3dModel(TORION_ANIM, 0);

  modelAnim3d_ctor(&tn->Model);
  modelAnim3d_setup(&tn->Model, getPtrToLoadedFile(TORION_MODEL), getPtrToLoadedFile(TORION_ANIM), 0, 0, 0);
  modelAnim3d_init(&tn->Model, 0, 0, 2000, 0);

  tn->rotation.y -= 0x3000;
  tn->position.y += 0x4000;
}

void Torion_draw(Torion* tn)
{
  DrawAModel(&tn->Model, &tn->position, &tn->rotation, &tn->scale);
}

void Torion_execute(Torion* tn)
{
  anim3d_update(&tn->Model.anim);

  tn->position.x -= 0x800;
}
