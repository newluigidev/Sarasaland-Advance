#include "nsmb.h"

bool stomped;
int explosionTimer;

void hook_02176914_ov_44()
{
  stomped = true;
}

void hook_02176474_ov_44()
{
  stomped = false;
  explosionTimer = 0;
}

void hook_02175D1C_ov_44(EnemyClassObject* bb)
{
  if (stomped == true)
  {
    ++explosionTimer;

    if (explosionTimer == 30 || explosionTimer == 90)
    {
      PlaySNDEffect(317, &bb->position);
      bb->velocity.y = 0x1500;
    }

    if (explosionTimer == 120)
      actorExplode(bb);

    if (explosionTimer == 125)
      Base__deleteIt(bb);
  }
}
