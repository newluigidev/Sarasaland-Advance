#include "nsmb.h"
#include <nds/ndstypes.h>
#include <nds/arm9/sassert.h>

int thunderTimer = 0;
int sec[] = {6, 13, 9, 22, 16, 25, 31, 12, 5, 24};
int secIndex = 0;
int inwater = 0;

void hook_0211F840_ov_0A()
{
  u32* currentArea = (u32*)0x02085A94;

  if (*currentArea == 0x18)
  {
    PlaySNDEffect2(296, 0);
    if (secIndex == 9)
      secIndex = 0;

    if (thunderTimer < (sec[secIndex])*60)
      ++thunderTimer;

    if (thunderTimer == 5)
      setBrightness(1, 0);

    if (thunderTimer == (sec[secIndex])*60)
    {
      setBrightness(1, 16);
      PlaySNDEffect(93, 0);
      thunderTimer = 0;
      ++secIndex;
    }
  }
}
