#include <nds.h>
#include <nds/registers_alt.h>
#include "Bombball.h"
#include "nsmb.h"

/*repl_0210085C_ov_0A: @Fireball throw stuff
repl_0210518C_ov_0A:*/

int bombballCount = 0;

u32 bombball_physics[] =
{
  0,
  0x80,
  0x70,
  0x80,
  0x930004,
  0xFFFE,
  (u32)&Bombball_CollisionCallback
};

const int BOMBBALL_MODEL = 2088 - 0x83;

void Bombball_setup(Bombball* bl)
{
  bl->bombballState = 0;
  bl->setDirection = false;

  MarioActor* mario = (MarioActor*)getPtrToPlayerActor();

  if (mario->direction == 0)
  {
    bl->position.x += 0x8000; bl->position.y += 0x4000;
  }
  else
  {
    bl->position.x -= 0x12000; bl->position.y += 0x4000;
  }


  //u32* bb = (u32*)findActorByType(bl->ClassID, 0);

  /**(bb + 0x438) &= 0xFD8FFFFF;
  *(bb + 0x444) &= 0xFFCFFFFF;
  *(bb + 0x450) &= 0xFD8FFFFF;*/

  u32 file = loadFileByExtId_3dModel(BOMBBALL_MODEL, 0);
  u32 tex = NNS_G3dGetTex(file);

  //EnemyActor_TileCollisions(&bl->collider, bl, bb + 0x444, bb + 0x438, bb + 0x450, 0);

  initActivePhysics(&bl->activephysics, bl, bombball_physics, 0);
  registerCollider(&bl->activephysics);

  getTextureParams(tex, 0, &bl->tex.texparam);
	getTexturePalBase(tex, 0, &bl->tex.palbase);

  mario->unk980 = 0x2115AAC;
}

void Bombball_CollisionCallback(ActivePhysics* a, ActivePhysics* b)
{
  Bombball* bl = (Bombball*)a->owner;
  EnemyClassObject* enemy = (EnemyClassObject*)b->owner;

  if (enemy->ClassID == 0x15)
    return;

  SpawnParticle(0x79, &bl->position); SpawnParticle(0x7A, &bl->position);
  PlaySNDEffect(0x70, &bl->position);

  Base__deleteIt(bl);
  OnlyEnemiesGetHurtCollisionCallback(b, b);
}

void Bombball_execute(Bombball* bl)
{
  ++bl->deleteTimer;

  nocashPrint1("%r0%\n", bombballCount);

  MarioActor* mario = (MarioActor*)getPtrToPlayerActor();

  if (bl->setDirection == false)
  {
    bl->direction = mario->direction; bl->setDirection = true;
  }

  u32 xPos = (bl->position.x + 0x4000 >> 12) / 16;
  u32 yPos = ((-bl->position.y) >> 12) / 16;

  u32 xPosSideL = ((bl->position.x) >> 12) / 16;
  u32 yPosSideL = ((-bl->position.y - 0x4000) >> 12) / 16;

  u32 xPosSideR = ((bl->position.x + 0x8000) >> 12) / 16;
  u32 yPosSideR = ((-bl->position.y - 0x4000) >> 12) / 16;

  u32 xPosTop = ((bl->position.x + 0x4000) >> 12) / 16;
  u32 yPosTop = ((-(bl->position.y + 0x8000)) >> 12) / 16;

  int tbBottom = getTileBehaviorAtPos2(xPos*16, yPos*16);
  int tbSideL = getTileBehaviorAtPos2(xPosSideL*16, yPosSideL*16);
  int tbSideR = getTileBehaviorAtPos2(xPosSideR*16, yPosSideR*16);
  int tbTop = getTileBehaviorAtPos2(xPosTop*16, yPosTop*16);

  //If the bombball reaches solid ground tiles, set state to 1.
  if ((!(tbBottom >> 0x10 & 0x2)) && (tbBottom))
    bl->bombballState = 1;

  if ((!(tbSideR >> 0x10 & 0x2)) && (tbSideR))
    bl->bombballState = 2;

  if ((!(tbTop >> 0x10 & 0x2)) && (tbTop))
    bl->bombballState = 3;

  if ((!(tbSideL >> 0x10 & 0x2)) && (tbSideL))
    bl->bombballState = 4;

  switch (bl->bombballState)
  {
    case 0:
    {
      if (bl->direction == 0)
      {
        bl->position.x += 0x2000; bl->position.y -= 0x2000;
        break;
      }
      else
      {
        bl->position.x -= 0x2000; bl->position.y -= 0x2000;
      }
      break;
    }
    case 1: //Ground collision
    {
      if (bl->direction == 0)
      {
        bl->position.x += 0x2000; bl->position.y += 0x2000;
        break;
      }
      else
      {
        bl->position.x -= 0x2000; bl->position.y += 0x2000;
      }
      break;
    }
    case 2: //Wall collision right
    {
      bl->position.x -= 0x2000; bl->position.y += 0x2000;
      break;
    }
    case 3: //Ceiling collision
    {
      if (bl->direction == 0)
      {
        bl->position.x += 0x2000; bl->position.y -= 0x2000;
        break;
      }
      else
      {
        bl->position.x -= 0x2000; bl->position.y -= 0x2000;
      }
      break;
    }
    case 4: //Wall collision left
    {
      bl->position.x += 0x2000; bl->position.y += 0x2000;
      break;
    }
    default:
      Base__deleteIt(bl);
  }

  if (bl->deleteTimer == 60*5)
  {
    bl->deleteTimer = 0;

    SpawnParticle(0x79, &bl->position); SpawnParticle(0x7A, &bl->position);
    PlaySNDEffect(0x70, &bl->position);
    Base__deleteIt(bl);
  }

  int xoffs = bl->position.x - mario->xPos;
  int yoffs = bl->position.y - mario->yPos;

  // From NerDS code. Thanks skawo :)
  if (xoffs > 0x100000 || xoffs < -0x100000 || yoffs > 0x100000 || yoffs < -0x100000)
      Base__deleteIt(bl);
}

inline void vec3(int x, int y, int z)
{
	REG_VERTEX16 = (y << 16) | (x & 0xFFFF);
	REG_VERTEX16 = (z & 0xFFFF);
}

inline void texcoord2(int x, int y)
{
	REG_TEXT_COORD = (y << 16) | (x & 0xFFFF);
}

void Bombball_draw(Bombball* bl)
{
	G3_LoadMtx43(0x02085B20);

	// this+0x5C -> sprite pos (vec3)
	REG_MTX_TRANSLATE = bl->position.x;
	REG_MTX_TRANSLATE = bl->position.y;
	REG_MTX_TRANSLATE = bl->position.z;

	REG_MTX_SCALE = 0x10000;
	REG_MTX_SCALE = 0x10000;
	REG_MTX_SCALE = 0x10000;

	REG_MTX_CONTROL = 3;
	REG_MTX_IDENTITY = 0;
	REG_MTX_CONTROL = 2;

	REG_POLY_FORMAT = 0x001F3880;
	REG_TEXT_FORMAT = bl->tex.texparam;
	(*(vu32*) 0x40004AC) = bl->tex.palbase;

	REG_COLOR = 0x7FFF;

	REG_GFX_BEGIN = 1;

	texcoord2(0x80, 0);
	vec3(0x800, 	0x800, 	0);

	texcoord2(0, 0);
	vec3(0, 		0x800, 	0);

	texcoord2(0, 0x80);
	vec3(0, 		0,			0);

	texcoord2(0x80, 0x80);
	vec3(0x800,	0,			0);

	REG_GFX_END = 0;
}

void Bombball_delete(Bombball* bl)
{
  --bombballCount;
  base_onDelete(bl);
}

void MarioState_Cutscenes(EnemyClassObject* Mario)
{
  UpdatePlayerAnimation(Mario);
  return;
}

void repl_02101188_ov_0A(EnemyClassObject* mario) //Throw bombballs, replaces MarioActor_ThrowFireball();
{
  MarioActor* mA = (MarioActor*)getPtrToPlayerActor();
  if (bombballCount < 1)
  {
    ++bombballCount;

    //mA->unk980 = (u32)&MarioState_Cutscenes;
    SetPlayerAnimation(mario, 18, 0, 0, 4096);
    UpdatePlayerAnimation(mario);
    PlaySNDEffect(360, &mario->position);

    createActor(0x7E, 0, &mario->position, 0, 0, 0);
  }
  //SetPlayerAnimation(mario, 18, 0, 0, 4096);
}
