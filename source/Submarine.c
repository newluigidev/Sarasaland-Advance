#include <nds.h>
#include <nds/registers_alt.h>
#include "nsmb.h"
#include "Submarine.h"

const int SUBMARINE_MODEL = 1576 - 0x83;
const int SUBMARINE_ANIM = 1577 - 0x83;

int SubHP;
bool isInvincible;

u32 Submarine_physics[] =
{
  0,
  0x12000,
  0x20000,
  0x10000,
  0x03F70001,
  0x0400,
  (u32)&Submarine_CollisionCallback
};

void Mario_WaterState(EnemyClassObject* mario)
{
  UpdatePlayerAnimation(mario);
  return;
}

void Submarine_setup(Submarine* sb)
{
  MarioActor* mario = (MarioActor*)getPtrToPlayerActor();

  if ((sb->spriteData >> 8) & 0x1)
    sb->state = 2;

  //else sb->state = 0;

  initActivePhysics(&sb->activephysics, sb, Submarine_physics, 0);
  registerCollider(&sb->activephysics);

  loadFileByExtId_3dModel(SUBMARINE_MODEL, 0);
  loadFileByExtId_3dModel(SUBMARINE_ANIM, 0);

  modelAnim3d_ctor(&sb->Model);
  modelAnim3d_setup(&sb->Model, getPtrToLoadedFile(SUBMARINE_MODEL), getPtrToLoadedFile(SUBMARINE_ANIM), 0, 0, 0);

  if (sb->state == 0)
    modelAnim3d_init(&sb->Model, 2, 0, 4096, 0);

  else if (sb->state == 2)
  {
    registerCollider(&mario->unk120);
    modelAnim3d_init(&sb->Model, 0, 0, 4096, 0);
  }

  sb->animTimer = 0;
  sb->holyshot = 20;
  SubHP = 1;
  sb->doblink = false;
  isInvincible = false;

  sb->scale.x = 0x7000; sb->scale.y = 0x7000; sb->scale.z = 0x7000;
  sb->rotation.y += 0x4000;
  sb->position.x += 0x9000;
  sb->position.z = 0x220000;
}

void Submarine_execute(Submarine* sb)
{
  nocashPrint1("%r0%\n", SubHP);
  MarioActor* mario = (MarioActor*)getPtrToPlayerActor();
  u32* freezeTimer = (u32*)0x020CA898;
  u32* ButtonsHeld = (u32*)0x02087652;
  u32* starTimer = (u32*)0x0208B350;

  if ((sb->spriteData >> 8) & 0x1)
    sb->state = 2;

  switch (sb->state)
  {
    case 0:
    {
      *freezeTimer |= 8u;
      break;
    }
    case 1: //Level enter state
    {
      mario->xPos = sb->position.x;
      mario->yPos = sb->position.y + 0x8000;
      //UnregisterActivePhysics(&mario->unk120);

      if (sb->animTimer < 40)
      {
        ++sb->animTimer;
        anim3d_update(&sb->Model.anim);
        break;
      }

      if (sb->animTimer == 40)
        sb->position.y -= 0x1000;

      break;
    }
    case 2:
    {
      if (sb->holyshot < 20)
        ++sb->holyshot;

      mario->direction = 0;

      mario->xPos = sb->position.x;
      mario->yPos = sb->position.y + 0x8000;

      mario->unk134 = 0;
      mario->unk138 = 0x12000;
      mario->unk13C = 0x20000;
      mario->unk140 = 0x10000;
      mario->unk144 = 0x03F70000;
      mario->unk148 = 0x0400;
      mario->unk14C = (u32)&Submarine_CollectCallback;

      //UnregisterActivePhysics(&mario->unk120);
      SetPlayerAnimation(mario, 0, 0, 0, 4096);
      mario->unk980 = (u32)&Mario_WaterState;

      anim3d_update(&sb->Model.anim);

      u32 xPos = (sb->position.x >> 12) / 16;
      u32 yPos = ((-sb->position.y) >> 12) / 16;

      u32 xPosTop = (sb->position.x >> 12) / 16;
      u32 yPosTop = (((-sb->position.y) - 0x20000) >> 12) / 16;

      u32 xPosLeft = (((sb->position.x) + 0x20000) >> 12) / 16;
      u32 yPosLeft = (((-sb->position.y) - 0x10000) >> 12) / 16;

      u32 xPosRight = (((sb->position.x) - 0x22000) >> 12) / 16;
      u32 yPosRight = (((-sb->position.y) - 0x10000) >> 12) / 16;

      int tb = getTileBehaviorAtPos2(xPos*16, yPos*16);
      int tbTop = getTileBehaviorAtPos2(xPosTop*16, yPosTop*16);
      int tbLeft = getTileBehaviorAtPos2(xPosLeft*16, yPosLeft*16);
      int tbRight = getTileBehaviorAtPos2(xPosRight*16, yPosRight*16);

      if (pressedKeys & RIGHT && (!((tbRight & 0x10000) || (tbRight & 0x100000))))
        sb->position.x -= 0x2000;
      if (pressedKeys & LEFT && (!((tbLeft & 0x10000) || (tbLeft & 0x100000))))
        sb->position.x += 0x2000;

      if (pressedKeys & UP && (!((tbTop & 0x10000) || (tbTop & 0x100000))))
        sb->position.y += 0x2000;
      if (pressedKeys & DOWN && (!((tb & 0x10000) || (tb & 0x100000))))
        sb->position.y -= 0x2000;

      if (*ButtonsHeld & Y && sb->holyshot == 20)
      {
        PlaySNDEffect(360, 0);
        SpawnParticle(0x79, &sb->position); SpawnParticle(0x7A, &sb->position);
        createActor(0x6B, 0x00000200, &sb->position, 0, 0, 0);
        sb->holyshot = 0;
      }

      if (sb->doblink == true)
      {
        UnregisterActivePhysics(&sb->activephysics);
        --sb->invincframes;
      }

      if (sb->invincframes == 0 && sb->regcol == true && sb->doblink == true)
      {
        registerCollider(&sb->activephysics);
        sb->doblink = false;
        sb->regcol = false;
      }
      break;
    }
    default:
      break;
  }
}

void Submarine_draw(Submarine* sb)
{
  //nocashPrint1("%r0%\n", sb->invincframes);
  if ((sb->invincframes % 5) != 0)
    return;

  DrawAModel(&sb->Model, &sb->position, &sb->rotation, &sb->scale);
}

void* Submarine_dtor(Submarine* sb)
{
  sb->vtable = (u32*)0x20C4F04;

  Vec3 dtor = {0, 0, 0};
  Vec2 dtor2 = {0, 0};

  sb->Unk4Vec2 = dtor2;
  sb->Unk3Vec2 = dtor2;
  sb->DeleteDist = dtor2;
  sb->DrawDist = dtor2;
  sb->ExistDist = dtor2;
  sb->unkv13 = dtor;
  sb->unkv12 = dtor;
  sb->unkv11 = dtor;

  UnregisterActivePhysics(&sb->activephysics);
  //UnregisterActivePhysics(&sb->collectphysics);

  return sb;
}

void* Submarine_dtorFree(Submarine* sb)
{
  Submarine_dtor(sb);
  freeToGameHeap(sb);
  return sb;
}

void Submarine_CollisionCallback(ActivePhysics* a, ActivePhysics* b)
{
  Submarine* sb = (Submarine*)a->owner;
  MarioActor* mario = (MarioActor*)getPtrToPlayerActor();
  EnemyClassObject* enemy = (EnemyClassObject*)b->owner;
  u32* playerID = (u32*)0x02085A50;

  switch (sb->state)
  {
    case 0:
    {
      sb->state = 1;

      if (*playerID == 1)
        PlaySNDEffect(323, 0);
      else
        PlaySNDEffect(71, 0);

      PlaySNDEffect(8, 0);
      break;
    }
    case 2:
    {
      if (!(enemy->ClassID == 0x15 || enemy->ClassID == 0x1F || enemy->ClassID == 0x6B || enemy->ClassID == 0x57) && !(mario->unk780 & 0x20))
      {
        if (SubHP == 0)
        {
          SpawnParticle(0x13, &sb->position); //This is absolute shit, don't question it.
          SpawnParticle(0x14, &sb->position);
          SpawnParticle(0x15, &sb->position);
          SpawnParticle(0x16, &sb->position);
          SpawnParticle(0x17, &sb->position);
          SpawnParticle(0x18, &sb->position);
          SpawnParticle(0x19, &sb->position);
          PlaySNDEffect(0x69, &sb->position);
          Base__deleteIt(sb);

          mario->DeathState = 0x21197FC;
        }
        else
        {
          SubHP = 0;
          sb->doblink = true;
          sb->invincframes = 120;
          sb->regcol = true;
          PlaySNDEffect(362, &sb->position);
          PlaySNDEffect(334, &sb->position);
        }
      }
      break;
    }
    default:
      break;
  }
}

void Submarine_CollectCallback(ActivePhysics* a, ActivePhysics* b)
{
  Submarine* sb = (Submarine*)a->owner; //actually Mario :>
  EnemyClassObject* enemy = (EnemyClassObject*)b->owner;
  MarioActor* mario = (MarioActor*)getPtrToPlayerActor();

  if (enemy->ClassID == 0x1F)
  {
    if ((enemy->spriteData & 0xF) == 3)
    {
      if (mario->marioPowerupState < 1)
        mario->marioPowerupState = 1;

      PlaySNDEffect(355, 0);
      SubHP = 1;
      SpawnParticle(62, &sb->position);
      Base__deleteIt(enemy);
      return;
    }
  }
}
