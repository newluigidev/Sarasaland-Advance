#include "nsmb.h"
#include "enemy.h"

int i = 0;

void hook_0200696C()
{
  i = 0;
}

void hook_0209EF98(EnemyClassObject* koopa)
{
  if (koopa->ClassID == 0x5F)
  {
    if ((koopa->spriteData >> 16) & 0x1) //Nybble 8
    {
      i++;

      u8 nybble = koopa->spriteData >> 0 & 0xF; //Nybble 12

      if (nybble == 1)
      {
        if (i == 120)
        {
          PlaySNDEffect(0x7E, &koopa->position);
          createActor(0x6B, 0x00000100, &koopa->position, 0, 0, 0);
          i = 0;
        }
      }
    }
  }
}
