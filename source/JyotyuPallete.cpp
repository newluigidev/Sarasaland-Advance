#include "nsmb.h"

void hook_020A3480_ov_00()
	{
		int JyotyuPal = MygetUnk3ForView(((*(getPtrToPlayerActor()+0xAF)>>16)&0xFF));
                if (JyotyuPal > 3) JyotyuPal = 3;

		u8* ptr = (u8*) allocFromGameHeap(1066);

			switch (JyotyuPal)
				{
					case 0: //Normal
						{
							loadFileByExtId_LZ_Dest(408-0x83, ptr);
							break;
						}
					case 1: //Underground
						{
							loadFileByExtId_LZ_Dest(406-0x83, ptr);
							break;
						}
					case 2: //Lava
						{
							loadFileByExtId_LZ_Dest(409-0x83, ptr);
							break;
						}
					case 3: //Snow/Ghost
						{
							loadFileByExtId_LZ_Dest(410-0x83, ptr);
							break;
						}
					default:
						{
							break;
						}
					//You can add more if you want
				}

		DC_FlushRangeOrAll(ptr, 0x400);
		GX_BeginLoadOBJExtPltt();
		GX_LoadOBJExtPltt(ptr, 0x0, 0x400);
		GX_EndLoadOBJExtPltt();

		DC_FlushRangeOrAll(ptr, 0x400);
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt(ptr, 0x4000, 0x400);
		GX_EndLoadBGExtPltt();

		freeToGameHeap(ptr);

		return;
	}
