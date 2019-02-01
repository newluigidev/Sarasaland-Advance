#include <nds.h>
#include "enemy.h"

#ifndef _NSMB_H
#define _NSMB_H

#ifdef __cplusplus
extern "C"
{
#endif
	extern void* ptrToLevelActor;
	extern u16 setTileTable[280];

	//Use MarioActor* mario = (MarioActor*)getPtrToPlayerActor(); for MarioActor fields.

	void changeTile(void* scenePtr, int x, int y, int tile);

	u32 loadCompressedFile(u32 fileID, void* dest);
	void* findActorByType(short classId, int from);
	u32 getTileBehaviorAtPos2(u32 x, u32 y);
	void GivePointsOfSomeKind(void* SpriteAddr, u8 PointsIndex, s32 PosXOffset, s32 PosYOffset, u32 unk);

	void ChangeSceneIfNeeded();

	u16* G2_GetBG2CharPtr();
	void GX_DispOn();

	void loadLevel(int SceneID, bool IsMvsL, int World, int Level, int Area, int, int, int, int, int PowerupState, int, int, int, int, int, int, int);

void NNS_SndPlayerSetTempoRatio(u32* SNDPlayerPointer, int Tempo);

void actorExplode(EnemyClassObject* i);

//If the 10th argument is equal to 5, then that's the check for Hammer Bro on the same node as Mario.

        void* createActor(u32 ClassID, u32 SpriteData, void* Vec3Position, u32 unk1, u32 unk2, u32 unk3);
	// 0x00000000 is nybbles, last eight of a sprite.
// ActorID List (31):
// Nybble 12:
// 0: Mushroom/Fire Flower (if big)
// 1: Star
// 2: Coin
// 3: Mushroom
// 4: Coin
// 5: Mega Mushroom spawning out of block
// 6: Mushroom
// 7: 1-UP
// 8: Mushroom
// 9: Fire Flower
// A: Beanstalk spawning out of block
// B: Blue Shell
// C: Mushroom
// D: Mushroom
// E: Mushroom
// F: Mushroom
// 10: Mushroom
// 11: Mushroom
// 12: Beanstalk spawning out of block
// 13: Coin
// 14: Coin
// 15: Mushroom
// 16: Mushroom
// 17: Mushroom
// 18: Mushroom
// 19: Mini Mushroom

	//Printing
	void nocashPrint(const char* txt);
	void nocashPrint1(const char* txt, u32 r0);
	void nocashPrint2(const char* txt, u32 r0, u32 r1);
	void nocashPrint3(const char* txt, u32 r0, u32 r1, u32 r2);

	//Useful hook spots
	//hook_02103538_ov_0A: for hitting solid tiles
	//hook_020E36DC_ov_0A: for hitting tiles with a fireball
	//void hook_02120918_ov_0A(int, int isTakingDamage): use this and set isTakingDamage to 362 to damage Mario.

	//nds_printf
	//Colours (arg1):
	//u16 WHITE[2] = {0x0000, 0xD000};
	//u16 GREEN[2] = {0x0000, 0xE000};
	//u16 RED[2] = {0x0000, 0xF000};
	//Position (arg2):
	//u16** topScreenPtr = (u16**)0x020859EC;
	//u16** subScreenPtr = (u16**)0x020859E8;
	//String to print (arg3)

	//Functions that run all the time
	//mainLoop, 0x0211F844, 0x020FD1D4

	//Misc
	void OS_Panic();
	void waitForVblank();
  void get1up(int pointAmount, int player);
  void exitLevel(bool complete);
  void ActivateAnEvent(void* ActorPtr, int eventID, int disableTimerIf54, bool unk3, bool unk4, bool unk5);
  u32* getPtrToPlayerActor();
  void getStarTimer();
	void getCoin();
	void EnemyCollisionCallback(void* ActivePhysicsA, void* ActivePhysicsB);
	u32* getPtrToMarioOrLuigi();
	bool DamageMario();
	void getCoinsForPlayer();
	//int *world = (int*)(0x02088BFC);
	//int *level = (int*)(0x02085A9C);
	//u8* coins = (u8*)0x208B37C;
	//int *lives = (int*)0x208B364;
	int loseOneLife(int playerNum);
	void AddPointsToScore(int points);
	//u32* SaveAreaPointer(int slot);
	bool EraseSave(int, void*);
	bool loadSave(int saveID, void*);
	bool saveSave(int, void*);
	int JumpToSave(int saveID, void*);
	int DropTouchscreenPowerups();
	void setPlayerLooksToTarget(bool val);
	void setPlayerLookingAtPosition(Vec3* position);
	void PlayMusicFile(int ID, int unk);
	void LoadMusicFile(int ID, int unk);
	void setMusicTempoIfDifferent(int Tempo);
	//u16* ButtonsHeld = (u16*)0x02087650;
	//u16* ButtonsPressed = (u16*)0x02087652;
	void MarioSpin();
	void SpawnParticle(int ParticleID, void* Vec3Position);
	void* findActorByType(short ClassID, int FromBase);
	void setPowerupStateForPlayer(int PlayerNumber, int Powerup);
	void SetPlayerAnimation(void* Pointer, int AnimationID, int StartFrame, int unk, int UpdateSpeed);
	void UpdatePlayerAnimation(void* Player);
	void initActivePhysics(void* ActivePhysics, void* SpriteAddr, u32 Physics[], u32 unk);
	void UnregisterActivePhysics(void* ActivePhysics);
	void ShellCollisionCallback(void* a, void* b);
	void Base__deleteIt(void* ActorPtr);
	void causeSceneChange(int NextSceneID, int Param);
	int setMusicTempo(int Tempo);
	int moveVolumeForPlayer(int volume, int unkAlways30);
	int CheckIfStarCoinCollected(EnemyClassObject*);
	int CheckIfStarCoinCollectedInSave();
	int pauseMusic(int);
	void MarioActor_Throw();
	void explode(void*);
	void doExplosion(EnemyClassObject*, EnemyClassObject);
	void registerCollider(void* ActivePhysics);
	void SpawnPlayerFireball(u32, void* pos, u32);
	u32* getPtrToLoadedFile(u32 fileID);
	void AffectByGravity(void*);
	void EnemyActor_TileCollisions(void* collider, void* SpriteAddr, u32 array1[], u32 array2[], u32 array3[], u32);
	void EnemyCollisionCallback(void*, void*);
	void sub_20AA990(int, u16);
	void ShellReboundRelated(void*);
	int sub_20990D4(void*);
	void sub_20A08A4(void*);
	int CheckCollisionUnder();
	int sub_209C590(int, int, int, int);
	int sub_212C648();
	int sub_2120A04(void*);
	int OnlyEnemiesGetHurtCollisionCallback(void*, void*);
	char SetSecretExitFromSpriteData(void*);
	void setEntranceIdForPlayer(u8 id, u8 player);
	void enterEntrance(void* Player, int type);
	u16 sub_212C27C(void*, u8);
	void SpawnMiscParticles(int ParticleType, void* pos, int unk);
	void sub_20A08A4(void*);
	void DeleteIfOutOfRange(void* actorPtr, int unk);
	void sub_2099884(void*, int);
	//int RNG();
	int OS_GetTick();
	int setViewLighting(int ViewID);
	void DoesPlayerDamage(void*);
	void SpawnAndEndParticle(int Time, int ParticleID, void* Vec3Position, int unk, int unk2, int unk3, int unk4);
	int DoWavesInLiquid(void*, int);
	int MarioActor_DeathState(void*);
	int MarioActor_doFlash(void*);
	int DrawWorldMapTextBox(int, int, int);


	void GX_BeginLoadBGExtPltt(void);
	void GX_LoadBGExtPltt(const void *pSrc, u32 destSlotAddr, u32 szByte);
	void GX_EndLoadBGExtPltt(void);
	void GX_BeginLoadOBJExtPltt(void);
	void GX_LoadOBJExtPltt(const void *pSrc, u32 destSlotAddr, u32 szByte);
	void GX_EndLoadOBJExtPltt(void);
  void DC_FlushRangeOrAll(const void *startAddr, u32 nBytes);
  void MIi_CpuCopy16(const void *srcp, void *destp, u32 size);
	u8 MygetUnk1ForView(u32 viewID);
	u8 MygetUnk2ForView(u32 viewID);
	u8 MygetUnk3ForView(u32 viewID);


	//DMA
	void MI_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);

        //Allocation
	void* allocFromGameHeap(u32 len);
	void freeToGameHeap(void* ptr);
	void* allocFromCacheTable(int size);

	//File funcs

	typedef u8 FSFile[0x48];
	void FS_InitFile(FSFile *p_file);
	void FS_CloseFile(FSFile *p_file);
	bool FS_OpenFileFast(FSFile *p_file, u32 archivePtr, int file_id);
	bool FS_SeekFile(FSFile *p_file, s32 offset, int origin);
	s32 FS_ReadFile(FSFile *p_file, void *dst, s32 len);
	s32 FS_ReadFileAsync(FSFile *p_file, void *dst, s32 len);
	bool FS_WaitAsync(FSFile* p_file);

	//NSMB-specific file funcs
	typedef u32 ExtId;

	void* loadFileByExtId(ExtId id);
	int loadFileByExtId_Dest(ExtId id, void* dest);
	int loadFileByExtId_Dest_WithMax(ExtId id, void* dest, int max);
	int loadFileByName_Dest_WithMax(const char* name, void* dest, int max);
	int loadFileByExtId_3dModel(u32 FileID, bool IsCompressed);

	void* loadFileByExtId_LZ(ExtId id);
	int loadFileByExtId_LZ_Dest(ExtId id, void* dest); //Returns size

	//Threading funcs
	typedef u8 OSThread[0xC0];
	void OS_CreateThread(OSThread* thread, void (*func)(void*), void* arg, void* stack, u32 stackSize, u32 prio);
	void OS_WakeupThreadDirect(OSThread* thread);

	//Sound funcs
	void SND_LockChannel(u32 chBitMask, u32 flags);
	void SND_SetupChannelPsg(int chNo, int duty, int volume, int shift, int timer, int pan);
	void SND_SetupChannelPcm(int chNo, int format, const void* dataAddr, int loop, int loopStart, int dataLen, int volume, int shift, int timer, int pan);
	void SND_StartTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
	void SND_StopTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
        void PlaySNDEffect(int SoundID, void* Pos);
	void PlaySNDEffect2(int SoundID, void* Pos);
	void PlaySNDEffect3(int SoundID, void* Pos);

#ifdef __cplusplus
}
#endif
typedef struct MarioActor
{
	u32* vtable;
	u8 unk005;
	u8 unk006; //Settings
	u8 unk007;
	u8 unk008; //Zeros
	u8 unk009;
	u16 MoonPhysics;
	u16 ClassID; //
	u16 unk00E; //
	u32 unk010; //SOme Ptr
	u32 unk014; //settings
	u32 unk018;
	u32 unk01C; //POINTER to table or struct? Used in pipes??
	u32 unk020;
	u32 unk024;
	u32 unk028;
	u32 unk02C;
	u32 unk030;
	u32 unk034;
	u32 unk038;
	u32 unk03C;
	u32 unk040;
	u32 unk044;
	u32 unk048;
	u32 unk04C;
	u32 unk050;
	u32 unk054;
	u32 unk058;
	u32 unk05C;
	u32 xPos;
	u32 yPos;
	u32 zPos;
	u32 unk06C;
	u32 xPos0;
	u32 yPos0;
	u32 zPos0;
	u32 unk07C;
	s32 xAccel0;
	s32 yAccel0;
	u32 unk088;
	u16 unk08C;
	u16 unk08E; //PIPE and behavior RELATED
	u32 unk090;
	u32 unk094;
	u32 unk098;
	u32 unk09C;
	u16 RotX;
	u16 RotY;
	u16 RotZ;
	u16 unk0A6;
	u32 unk0A8; //PIPE RELATED
	u32 unk0AC;
	u32 unk0B0;
	u32 xVelocity; //0xB4
	u32 yVelocity; //0xB8
	u32 unk0BC;
	u32 unk0C0;
	u32 unk0C4;
	u32 unk0C8;
	u32 unk0CC;
	s32 xAccel; //0xD0
	s32 yAccel;	//0xD4
	u32 unk0D8;
	u32 unk0DC;
	u32 unk0E0;
	u32 unk0E4;
	u32 unk0E8;
	u32 unk0EC;
	u32 ScaleX;
	u32 ScaleY;
	u32 ScaleZ;
	u32 unk0FC;
	u32 unk100;
	u32 unk104;
	u32 unk108;
	u32 unk10C;
	u32 unk110;
	u32 unk114;
	u32 unk118;
	u16 unk11C;
	u16 PlayerNumber;
	u32 unk120;
	u32 unk124;
	u32 unk128;
	u32 unk12C;
	u32 unk130;
	u32 unk134;
	u32 unk138;
	u32 unk13C;
	u32 unk140;
	u32 unk144;
	u32 unk148;
	u32 unk14C;
	u32 unk150;
	u32 unk154;
	u32 unk158;
	u32 unk15C;
	u32 unk160;
	u32 unk164;
	u32 unk168;
	u32 unk16C;
	u32 unk170;
	u32 unk174;
	u32 unk178;
	u32 unk17C;
	u32 unk180;
	u32 unk184;
	u32 unk188;
	u32 unk18C;
	u32 unk190;
	u32 unk194;
	u32 unk198;
	u32 unk19C;
	u32 unk1A0;
	u32 unk1A4;
	u32 unk1A8;
	u32 unk1AC;
	u32 unk1B0;
	u32 unk1B4;
	u32 unk1B8;
	u32 unk1BC;
	u32 unk1C0;
	u32 unk1C4;
	u32 unk1C8;
	u32 unk1CC;
	u32 unk1D0;
	u32 unk1D4;
	u32 unk1D8;
	u32 unk1DC;
	u32 unk1E0;
	u32 unk1E4;
	u32 unk1E8;
	u32 unk1EC;
	u32 unk1F0;
	u32 unk1F4;
	u32 unk1F8;
	u32 unk1FC;
	u32 unk200;
	u32 unk204;
	u32 unk208;
	u32 unk20C;
	u32 unk210;
	u32 unk214;
	u32 unk218;
	u32 unk21C;
	u32 unk220;
	u32 unk224;
	u32 unk228;
	u32 unk22C;
	u32 unk230;
	u32 unk234;
	u32 unk238;
	u32 unk23C;
	u32 unk240;
	u32 unk244;
	u32 unk248;
	u8 unk24C;
	u8 isOnGround; //0x0 no ground 0x1: std ground 0x2: jump-through ground 0x10 sprite ground
	u8 unk24E;
	u8 unk24F;
	u32 unk250;
	u32 unk254;
	u32 unk258;
	u32 unk25C;
	u32 unk260;
	u32 unk264;
	u32 unk268;
	u32 unk26C;
	u32 unk270;
	u32 unk274;
	u32 unk278;
	u32 unk27C;
	u32 unk280;
	u32 unk284;
	u32 unk288;
	u32 unk28C;
	u32 unk290;
	u32 unk294;
	u32 unk298;
	u32 unk29C;
	u32 unk2A0;
	u32 unk2A4;
	u32 unk2A8;
	u32 unk2AC;
	u32 unk2B0;
	u32 unk2B4;
	u32 unk2B8;
	u8 unk2BC;
	u8 direction; // & 0x1 = direction (0->right; 1->left)
	u8 CurrentViewID2BE;
	u8 unk2BF;
	u32 unk2C0;
	u32 unk2C4;
	u32 unk2C8;
	u32 unk2CC;
	u32 unk2D0;
	u32 unk2D4;
	u32 unk2D8;
	u32 unk2DC;
	u32 unk2E0;
	u32 unk2E4;
	u32 unk2E8;
	u32 unk2EC;
	u32 unk2F0;
	u32 unk2F4;
	u32 unk2F8;
	u32 unk2FC;
	u32 unk300;
	u32 unk304;
	u32 unk308;
	u32 unk30C;
	u32 unk310;
	u32 unk314;
	u32 unk318;
	u32 unk31C;
	u32 unk320;
	u32 unk324;
	u32 unk328;
	u32 unk32C;
	u32 unk330;
	u32 unk334;
	u32 unk338;
	u32 unk33C;
	u32 unk340;
	u32 unk344;
	u32 unk348;
	u32 unk34C;
	u32 unk350;
	u32 unk354;
	u32 unk358;
	u32 unk35C;
	u32 unk360;
	u32 unk364;
	u32 unk368;
	u32 unk36C;
	u32 unk370;
	u32 unk374;
	u32 unk378;
	u32 unk37C;
	u32 unk380;
	u32 unk384;
	u32 unk388;
	u32 unk38C;
	u32 unk390;
	u32 unk394;
	u32 unk398;
	u32 unk39C;
	u32 unk3A0;
	u32 unk3A4;
	u32 unk3A8;
	u32 unk3AC;
	u32 unk3B0;
	u32 unk3B4;
	u32 unk3B8;
	u32 unk3BC;
	u32 unk3C0;
	u32 unk3C4;
	u32 unk3C8;
	u32 unk3CC;
	u32 unk3D0;
	u32 unk3D4;
	u32 unk3D8;
	u32 unk3DC;
	u32 unk3E0;
	u32 unk3E4;
	u32 unk3E8;
	u32 unk3EC;
	u32 unk3F0;
	u32 unk3F4;
	u32 unk3F8;
	u32 unk3FC;
	u32 unk400;
	u32 unk404;
	u32 unk408;
	u32 unk40C;
	u32 unk410;
	u32 unk414;
	u32 unk418;
	u32 unk41C;
	u32 unk420;
	u32 unk424;
	u32 unk428;
	u32 unk42C;
	u32 unk430;
	u32 unk434;
	u32 unk438;
	u32 unk43C;
	u32 unk440;
	u32 unk444;
	u32 unk448;
	u32 unk44C;
	u32 unk450;
	u32 unk454;
	u32 unk458;
	u32 unk45C;
	u32 unk460;
	u32 unk464;
	u32 unk468;
	u32 unk46C;
	u32 unk470;
	u32 unk474;
	u32 unk478;
	u32 unk47C;
	u32 unk480;
	u32 unk484;
	u32 unk488;
	u32 unk48C;
	u32 unk490;
	u32 unk494;
	u32 unk498;
	u32 unk49C;
	u32 unk4A0;
	u32 unk4A4;
	u32 unk4A8;
	u32 unk4AC;
	u32 unk4B0;
	u32 unk4B4;
	u32 unk4B8;
	u32 unk4BC;
	u32 unk4C0;
	u32 unk4C4;
	u32 unk4C8;
	u32 unk4CC;
	u32 unk4D0;
	u32 unk4D4;
	u32 unk4D8;
	u32 unk4DC;
	u32 unk4E0;
	u32 unk4E4;
	u32 unk4E8;
	u32 unk4EC;
	u32 unk4F0;
	u32 unk4F4;
	u32 unk4F8;
	u32 unk4FC;
	u32 unk500;
	u32 unk504;
	u32 unk508;
	u32 unk50C;
	u32 unk510;
	u32 unk514;
	u32 unk518;
	u32 unk51C;
	u32 unk520;
	u32 unk524;
	u32 unk528;
	u32 unk52C;
	u32 unk530;
	u32 unk534;
	u32 unk538;
	u32 unk53C;
	u32 unk540;
	u32 unk544;
	u32 unk548;
	u32 unk54C;
	u32 unk550;
	u32 unk554;
	u32 unk558;
	u32 unk55C;
	u32 unk560;
	u32 unk564;
	u32 unk568;
	u32 unk56C;
	u32 unk570;
	u32 unk574;
	u32 unk578;
	u32 unk57C;
	u32 unk580;
	u32 unk584;
	u32 unk588;
	u32 unk58C;
	u32 unk590;
	u32 unk594;
	u32 unk598;
	u32 unk59C;
	u32 unk5A0;
	u32 unk5A4;
	u32 unk5A8;
	u32 unk5AC;
	u32 unk5B0;
	u32 unk5B4;
	u32 unk5B8;
	u32 unk5BC;
	u32 unk5C0;
	u32 unk5C4;
	u32 unk5C8;
	u32 unk5CC;
	u32 unk5D0;
	u32 unk5D4;
	u32 unk5D8;
	u32 unk5DC;
	u32 unk5E0;
	u32 unk5E4;
	u32 unk5E8;
	u32 unk5EC;
	u32 unk5F0;
	u32 unk5F4;
	u32 unk5F8;
	u32 unk5FC;
	u32 unk600;
	u32 unk604;
	u32 unk608;
	u32 unk60C;
	u32 unk610;
	u32 unk614;
	u32 unk618;
	u32 unk61C;
	u32 unk620;
	u32 unk624;
	u32 unk628;
	u32 unk62C;
	u32 unk630;
	u32 unk634;
	u32 unk638;
	u32 unk63C;
	u32 unk640;
	u32 unk644;
	u32 unk648;
	u32 unk64C;
	u32 unk650;
	u32 unk654;
	u32 unk658;
	u32 unk65C;
	u32 unk660;
	u32 unk664;
	u32 unk668;
	u32 unk66C;
	u32 unk670;
	u32 unk674;
	u32 unk678;
	u32 unk67C;
	u32 unk680;
	u32 unk684;
	u32* HeldItem;
	u32 unk68C;
	u32 unk690;
	u32 unk694;
	u32 unk698;
	u32 unk69C;
	u32 unk6A0;
	u32 unk6A4;
	u32 unk6A8;
	u32 unk6AC;
	u32 unk6B0;
	u32 unk6B4;
	u32 unk6B8;
	u32 unk6BC;
	u32 unk6C0;
	u32 unk6C4;
	u32 unk6C8;
	u32 unk6CC;
	u32 unk6D0;
	u32 unk6D4;
	u32 unk6D8;
	u32 unk6DC;
	u32 unk6E0;
	u32 unk6E4;
	u32 unk6E8;
	u32 unk6EC;
	u32 unk6F0;
	u32 unk6F4;
	u32 unk6F8;
	u32 unk6FC;
	u32 unk700;
	u32 unk704;
	u32 unk708;
	u32 unk70C;
	u32 unk710;
	u32 unk714;
	u32 unk718;
	u32 unk71C;
	u32 unk720;
	u32 unk724;
	u32 unk728;
	u32 unk72C;
	u32 unk730;
	u32 unk734;
	u32 unk738;
	u32 unk73C;
	u32 unk740;
	u32 unk744;
	u32 unk748;
	u32 unk74C;
	u32 unk750;
	u32 unk754;
	u32 unk758;
	u32 unk75C;
	u32 unk760;
	u32 unk764;
	u32 unk768;
	u32 currentMarioAnim;
	u32 unk770;
	u32 unk774;
	u32 tripleJumpRelated778;
	u8 IsHoldingSomething;
	u8 unk77D;
	u8 IsMarioGroundPounding77E;
	u8 unk77F;
	u32 unk780;
	u32 unk784;
	u32 unk788;
	u32 unk78C;
	u32 unk790;
	u32 unk794;
	u32 unk798;
	u8 unk79C;
	u8 unk79C_1;
	u8 unk79C_2;
	u8 unk79C_3;
	u32 unk7A0;
	u32 unk7A4;
	u8 unk7A8;
	u8 unk7A9;
	u8 unk7AA;
	u8 marioPowerupState;
	u8 marioPowerupState2;
	u8 lastPowerupState;
	u8 unk7AE;
	u8 unk7AF;
	u32 unk7B0;
	u32 unk7B4;
	u32 unk7B8;
	u8 unk7BC;
	u8 unk7BD;
	u8 unk7BE;
	u8 tripleJumpRelated7BF;
	u32 unk7C0;
	u32 unk7C4;
	u32 unk7C8;
	u32 unk7CC;
	u32 unk7D0;
	u32 unk7D4;
	u32 unk7D8;
	u32 unk7DC;
	u32 unk7E0;
	u32 unk7E4;
	u32 unk7E8;
	u32 unk7EC;
	u32 unk7F0;
	u32 unk7F4;
	u32 unk7F8;
	u32 unk7FC;
	u32 unk800;
	u32 unk804;
	u32 unk808;
	u32 unk80C;
	u32 unk810;
	u32 unk814;
	u32 unk818;
	u32 unk81C;
	u32 unk820;
	u32 unk824;
	u32 unk828;
	u32 unk82C;
	u32 unk830;
	u32 unk834;
	u32 unk838;
	u32 unk83C;
	u32 unk840;
	u32 unk844;
	u32 unk848;
	u32 unk84C;
	u32 unk850;
	u32 unk854;
	u32 unk858;
	u32 unk85C;
	u32 unk860;
	u32 unk864;
	u32 unk868;
	u32 unk86C;
	u32 unk870;
	u32 unk874;
	u32 unk878;
	u32 unk87C;
	u32 unk880;
	u32 unk884;
	u32 unk888;
	u32 unk88C;
	u32 unk890;
	u32 unk894;
	u32 unk898;
	u32 unk89C;
	u32 unk8A0;
	u32 unk8A4;
	u32 unk8A8;
	u32 unk8AC;
	u32 unk8B0;
	u32 unk8B4;
	u32 unk8B8;
	u32 unk8BC;
	u32 unk8C0;
	u32 unk8C4;
	u32 unk8C8;
	u32 unk8CC;
	u32 unk8D0;
	u32 unk8D4;
	u32 unk8D8;
	u32 unk8DC;
	u32 unk8E0;
	u32 unk8E4;
	u32 unk8E8;
	u32 unk8EC;
	u32 unk8F0;
	u32 unk8F4;
	u32 unk8F8;
	u32 unk8FC;
	u32 unk900;
	u32 unk904;
	u32 unk908;
	u8  unk90C;
	u8  unk90D;
	u8  CurrentView90E;
	u8  unk90F;
	u32 unk910;
	u32 unk914;
	u32 unk918;
	u32 unk91C;
	u32 unk920;
	u32 unk924;
	u32 unk928;
	u32 unk92C;
	u32 unk930;
	u32 unk934;
	u32 unk938;
	u32 unk93C;
	u32 unk940;
	u32 unk944;
	u32 unk948;
	u32 unk94C;
	u32 unk950;
	u32 unk954;
	u32 unk958;
	u32 unk95C;
	u32 unk960;
	u32 unk964;
	u32 unk968;
	u32 unk96C;
	u32 unk970;
	u32 unk974;
	u32 unk978;
	u32 unk97C;
	u32 unk980;
	u32 unk984;
	u32 unk988;
	u32 unk98C;
	u32 DeathState;
	u32 unk994;
	u32 unk998;
	u32 unk99C;
	u32 unk9A0;
	u32 unk9A4;
	u32 unk9A8;
	u32 unk9AC;
	u32 unk9B0;
	u32 unk9B4;
	u32 unk9B8;
	u32 unk9BC;
	u32 unk9C0;
	u32 unk9C4;
	u32 unk9C8;
	u32 unk9CC;
	u32 unk9D0;
	u32 unk9D4;
	u32 unk9D8;
	u32 unk9DC;
	u32 unk9E0;
	u32 unk9E4;
	u32 unk9E8;
	u32 unk9EC;
	u32 unk9F0;
	u32 unk9F4;
	u32 unk9F8;
	u32 unk9FC;
	u32 unkA00;
	u32 unkA04;
	u32 unkA08;
	u32 unkA0C;
	u32 unkA10;
	u32 unkA14;
	u32 unkA18;
	u32 unkA1C;
	u32 unkA20;
	u32 unkA24;
	u32 unkA28;
	u32 unkA2C;
	u32 unkA30;
	u32 unkA34;
	u32 unkA38;
	u32 unkA3C;
	u32 unkA40;
	u32 unkA44;
	u32 unkA48;
	u32 unkA4C;
	u32 unkA50;
	u32 unkA54;
	u32 unkA58;
	u32 unkA5C;
	u32 unkA60;
	u32 unkA64;
	u32 unkA68;
	u32 unkA6C;
	u32 unkA70;
	u32 unkA74;
	u32 unkA78;
	u32 unkA7C;
	u32 unkA80;
	u32 unkA84;
	u32 unkA88;
	u32 unkA8C;
	u32 unkA90;
	u32 unkA94;
	u32 unkA98;
	u32 unkA9C;
	u32 unkAA0;
	u32 unkAA4;
	u32 unkAA8;
	u32 unkAAC;
	u32 unkAB0;
	u32 unkAB4;
	u32 unkAB8;
	u32 unkABC;
	u32 unkAC0;
	u32 unkAC4;
	u32 unkAC8;
	u32 unkACC;
	u32 unkAD0;
	u32 unkAD4;
	u32 unkAD8;
	u32 unkADC;
	u32 unkAE0;
	u32 unkAE4;
	u32 unkAE8;
	u32 unkAEC;
	u32 unkAF0;
	u32 unkAF4;
	u32 unkAF8;
	u32 unkAFC;
	u32 unkB00;
	u32 unkB04;
	u32 unkB08;
	u32 unkB0C;
	u32 unkB10;
	u32 unkB14;
	u32 unkB18;
	u32 unkB1C;
	u32 unkB20;
	u32 unkB24;
	u32 unkB28;
	u32 unkB2C;
	u32 unkB30;
	u32 unkB34;
	u32 unkB38;
	u32 unkB3C;
	u32 unkB40;
	u32 unkB44;
	u32 unkB48;
	u32 unkB4C;
	u32 unkB50;
	u32 unkB54;
	u32 unkB58;
	u32 unkB5C;
	u32 unkB60;
	u32 unkB64;
	u32 unkB68;
	u32 unkB6C;
	u32 unkB70;
	u32 unkB74;
	u32 unkB78;
	u32 unkB7C;
	u32 unkB80;
	u32 unkB84;
	u32 unkB88;
	u32 unkB8C;
	u32 unkB90;
	u32 unkB94;
	u32 unkB98;
	u8 unkB9C;
	u8 unkB9D;
	u8 movementRelated; //Set to 1 when idle, 2 when moving (walking/running, falling, crounching), 3 when landing
	u8 NotInPipeCannonB9F;
	char consecutiveJumps;
	u8 unkBA1;
	u8 unkBA2;
	u8 unkBA3;
	u16 unkBA4;
	u16 unkBA6;  //Amount of frames that a powerup/damage transformation takes. Game sets it to 0x2805, and negates until 0
	u32 unkBA8;  //Set to 0x20000 on level begin, last digit is set to 7 when powerup is gained, and 3rd last digit is set to 1 when damage is taken.
	u8 unkBAC;
	u8 unkBAD;
	u8 unkBAE;
	u8 CurrentModel;
	u32 unkBB0;
	u8 unkBB4;
	u8 unkBB5;
	u8 ModelTexture;
	u8 unkBB7;
	u32 unkBB8;
	u32 unkBBC;
	u32 unkBC0;
	u32 unkBC4;
	u32 unkBC8;
} MarioActor;




typedef struct SaveData
{
	u32 header;
	u32 field_04;
	u32 Completion;
	u32 lives;
	u32 coins;
	u32 field_14;
	u32 starCoinsInSave;
	u32 spentStarCoins;
	u32 currentWorld;
	u32 field_24;
	u32 currentWorldMapNode;
	u32 field_2C;
	u32 currentPowerup;
	u32 score;
	u32 currentBottomScreenBackground;
	u32 field_3C;
	u32 field_40;
	u32 field_44;
	u32 field_48;
	u32 field_4C;
	u32 field_50;
	u32 field_54;
	u32 field_58;
	u8 inventoryItem;
	u8 field_5D;
	u8 field_5E;
	u8 field_5F;
	u16 worlds[8];
	u8 starCoins[200];
	u8 levels[240];
	u8 unk[32];
} SaveData;

extern SaveData saveData;

struct View
{
	u16 x;
	u16 y;
	u16 width;
	u16 height;
	u8 id;
	u8 camID;
	u8 musicID;
	u8 unk1;
	u8 unk2;
	u8 unk3;
	u8 lightingID;
	u8 progressPathID;
};

typedef struct  // Size: 0x90
{
        u32 unk[0x24];
} Model3d;

typedef struct  // Size: 0x18
{
        u32 unk[0x6];
} Anim3d;

typedef struct  // Size: 0xA8
{
        Model3d model;  // 0x00
        Anim3d anim;    // 0x90
} ModelAnim3d;

bool DrawAModel(void* Model, void* Position, void* Rotation, void* Scale);

// Functions for Models without animation
void model3d_ctor(Model3d* model);
bool model3d_setup(Model3d* model, void* modelFile, u32 unk);
void model3d_init(Model3d* model);

// Functions for Models with character animation
// These functions call all above functions
void modelAnim3d_ctor(ModelAnim3d* model);
bool modelAnim3d_setup(ModelAnim3d* model, void* modelFile, void* animationFile, u32 unk1 , u32 unk2, u32 unk3);
void modelAnim3d_init(ModelAnim3d* model, u32 animationId, u32 unk1, u32 animationSpeed, u32 unk2);

void anim3d_update(Anim3d* animation);

#define KEYS_CR			(*(vu32*)0x04000130)
#define START_REG (*(vu32*)0x023FFC20)


#define A 		0x0001
#define B 		0x0002
#define SELECT 	0x0004
#define START 0x0008
#define LEFT 0x0010
#define RIGHT 0x0020
#define UP 0x0040
#define DOWN 0x0080
#define SRIGHT 0x0100
#define SLEFT 0x0200
#define X 0x0400
#define Y 0x0800
#define TOUCH 0x2000
#define HINGE 0x8000
#define pressedKeys (*(vu16*)0x020888E2)

#define controlOptionsA (*(bool*)0x02088f24)
#define controlOptionsB (*(bool*)0x02085ad4) //Both are mirrors of the same. 01 if B and A jump, 00 if X and A jump

//Custom key reading funcs.
void myScanKeys();
int myKeysHeld();
int myKeysDown();

#endif
