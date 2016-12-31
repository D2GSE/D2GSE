#pragma once

#include <Windows.h>

#pragma pack(push, 1)

struct Game;
struct Unit;

struct NetClient
{
    DWORD	clientID;					//+00
    BYTE	uk1[0x06];					//+04
    union {								//+0A
        WORD	flag;
        struct {
            WORD f1 : 1;
            WORD f2 : 1;
            WORD isHardCoreGame : 1;
        };
    };
    BYTE	uk2[0x168];					//+0C
    Unit* pUnit;                        //+174
    DWORD unk;                          //+178
    BYTE*	savefile;					//+17C
    DWORD	finalSize;					//+180
    DWORD	counter;					//+184
    DWORD	currentSize;				//+188
    DWORD	uk3[0x7];					//+18C
    Game*	ptGame;						//+1A8
    DWORD _3[0xBF];						//0x1AC
    NetClient* pClientPrev;			    //0x4A8
                                        //+1A8 is ptGame
                                        //+4A8 ptNextClient
                                        /*
                                        Kingpin: ptPclient
                                        +16C is either act or unit type
                                        +170 Active UniqueID for player
                                        +174 Active ptPlayer on Client
                                        +1a8 ptGame
                                        +1b4 Current or next ptRoom
                                        */
};

static_assert(sizeof(NetClient) == 0x4A8 + 4, "Check NetClient structure padding");

struct Act;
struct Level;
struct ActMisc
{
    DWORD _1[37];			//0x00
    DWORD dwStaffTombLevel; //0x94
    DWORD _2[245];			//0x98
    Act* pAct;				//0x46C
    DWORD _3[3];			//0x470
    Level* pLevelFirst;		//0x47C
};

struct Room2;
struct Level
{
    DWORD _1[4];			//0x00
    Room2* pRoom2First;		//0x10
    DWORD _2[2];			//0x14
    DWORD dwPosX;			//0x1C
    DWORD dwPosY;			//0x20
    DWORD dwSizeX;			//0x24
    DWORD dwSizeY;			//0x28
    DWORD _3[96];			//0x2C
    Level* pNextLevel;		//0x1AC
    DWORD _4;				//0x1B0
    ActMisc* pMisc;			//0x1B4
    DWORD _5[6];			//0x1BC
    DWORD dwLevelNo;		//0x1D0
    DWORD _6[3];			//0x1D4
    union {
        DWORD RoomCenterX[9];
        DWORD WarpX[9];
    };						//0x1E0
    union {
        DWORD RoomCenterY[9];
        DWORD WarpY[9];
    };						//0x204
    DWORD dwRoomEntries;	//0x228
};

struct Room;

struct Room2
{
    DWORD _1[2];			//0x00
    Room2** pRoom2Near;		//0x08
    DWORD _2[5];			//0x0C
    struct {
        DWORD dwRoomNumber; //0x00
        DWORD _1;			//0x04
        DWORD* pdwSubNumber;//0x08
    } *pType2Info;			//0x20
    Room2* pRoom2Next;		//0x24
    DWORD dwRoomFlags;		//0x28
    DWORD dwRoomsNear;		//0x2C
    Room* pRoom1;			//0x30
    DWORD dwPosX;			//0x34
    DWORD dwPosY;			//0x38
    DWORD dwSizeX;			//0x3C
    DWORD dwSizeY;			//0x40
    DWORD _3;				//0x44
    DWORD dwPresetType;		//0x48
    void* /*RoomTile**/ pRoomTiles;	//0x4C
    DWORD _4[2];			//0x50
    Level* pLevel;			//0x58
    void* /*PresetUnit**/ pPreset;	//0x5C
};

struct Room
{
    Room** pRoomsNear; 	//0x00
    DWORD _1[3];			//0x04
    Room2* pRoom2;			//0x10
    DWORD _2[3];			//0x14
    void* /*CollMap**/ Coll;			//0x20
    DWORD dwRoomsNear;		//0x24
    DWORD _3[9];			//0x28
    DWORD dwXStart;			//0x4C
    DWORD dwYStart;			//0x50
    DWORD dwXSize;			//0x54
    DWORD dwYSize;			//0x58
    DWORD _4[6];			//0x5C
    Unit* pUnitFirst;     	//0x74
    DWORD _5;				//0x78
    Room* pRoomNext;		//0x7C
};

struct Act
{
    DWORD _1[3];			//0x00
    DWORD dwMapSeed;		//0x0C
    Room* pRoom1;			//0x10
    DWORD dwAct;			//0x14
    DWORD _2[12];			//0x18
    ActMisc* pMisc;			//0x48
};

struct MonsterData					// sizeof(MonsterData)=0x60
{										//Offset from Code.
    BYTE	uk[0x16];					//+00
    union {
        WORD	flags;					//+16
        struct {
            WORD	fuk1 : 1;
            WORD	isSuperUnique : 1;
            WORD	isChampion : 1;
            WORD	isUnique : 1;
            WORD	fuk2 : 13;
        };
    };
    BYTE		uk1[0x0E];					//+18
    WORD		superUniqueID;				//+26
    void*	unknow1;					//+28
    BYTE		uk2[0x38];					//+28
};

struct ObjectData
{
    void* /*ObjectsBIN**/	ptObjectsBIN;
    BYTE		levelID;
};

struct Inventory
{                               		//Offset from Code.		Size: 30 à 40
    DWORD	tag;						//+00	= 0x01020304
    BYTE	uk1[0x04];					//+04	=? 0
    Unit*	ptChar;						//+08
    Unit*	ptItem;						//+0C
    BYTE	uk2[0x10];					//+10
    Unit*	inventory1;					//+20
    BYTE	uk3[0x04];					//+24
    DWORD	currentUsedSocket;			//+28 //Kingpin : a variable to know how many sockets that have added to item
    DWORD	Inventory2C;				//+2C //one value
    DWORD	Inventory30;				//+30
    void*	ptCorpse;					//+34
    BYTE	uk5[0x04];					//+38
    DWORD	nextCorpseId;				//+3C //max = 15
    BYTE	uk6[0x04];					//+40
};

struct ItemData//size=0x74
{										//Offset from Code.
    DWORD	quality;					//+00
    DWORD	seedLow;					//+04
    DWORD	seedHi;						//+08
    DWORD	playerID;					//+0C #10734 / #10735 (PCInventory->ptPlayer->0C)
    DWORD	seedStarting;				//+10
    DWORD	flags1;						//+14
    union {
        DWORD	flags2;					//+18
        struct {
            DWORD	fuk1 : 1;				//0x00000001
            DWORD	isIndentified : 1;	//0x00000002
            DWORD	fuk2 : 2;				//0x0000000C
            DWORD	isUnindentified : 1;	//0x00000010
            DWORD	fuk3 : 3;				//0x000000E0
            DWORD	isBroken : 1;			//0x00000100
            DWORD	fuk4 : 2;				//0x00000600
            DWORD	isSocketed : 1;		//0x00000800
            DWORD	fuk5 : 10;			//0x003FF000
            DWORD	isEtheral : 1;		//0x00400000
            DWORD	fuk6 : 3;				//0x03800000
            DWORD	isRuneword : 1;		//0x04000000
            DWORD	fuk7 : 1;				//0x08000000
            DWORD	isPersonalized : 1;	//0x10000000
            DWORD	fuk8 : 3;				//0xE0000000
        };
    };
    /*
    ITEMFLAG_NEWITEM               = 0x00000001,
    ITEMFLAG_TAGETING               = 0x00000004,
    ITEMFLAG_UNIDENTIFIED               = 0x00000010,
    ITEMFLAG_QUANTITY               = 0x00000020,
    ITEMFLAG_Durability               = 0x00000100,
    ITEMFLAG_UNKNOWN2               = 0x00000400,
    ITEMFLAG_SOCKETED               = 0x00000800,
    ITEMFLAG_NON_SELLABLE               = 0x00001000,
    ITEMFLAG_NEWITEM2               = 0x00002000,
    ITEMFLAG_UNKNOWN3               = 0x00004000,
    ITEMFLAG_CHECKSECPRICE               = 0x00010000,
    ITEMFLAG_CHECKGAMBLEPRICE          = 0x00020000,
    ITEMFLAG_UNKNOWN4               = 0x00080000,
    ITEMFLAG_INDESTRUCTIBLE(ETHERAL) = 0x00400000,
    ITEMFLAG_UNKNOWN5               = 0x00800000,
    ITEMFLAG_FROMPLAYER               = 0x01000000,
    ITEMFLAG_RUNEWORD               = 0x04000000
    */
    DWORD	guid1;						//+1C Global Unique ID 1  
    DWORD	guid2;						//+20 Global Unique ID 2  
    DWORD	guid3;						//+24 Global Unique ID 3  
    DWORD	uniqueID;					//+28
    BYTE	ilvl;						//+2C
    BYTE	uk1[0x03];					//+2D
    WORD	version;					//+30
    WORD	rarePrefix;					//+32
    WORD	rareSuffix;					//+34
    WORD	autoPref;					//+36
    WORD	prefix[3];					//+38
    WORD	suffix[3];					//+3E
    BYTE	equipLoc;					//+44
                                        /*	emplacement si équipé
                                        *	00 = noequip/inBelt
                                        *   01 = head
                                        *	02 = neck
                                        *	03 = tors
                                        *	04 = rarm
                                        *	05 = larm
                                        *	06 = lrin
                                        *	07 = rrin
                                        *	08 = belt
                                        *	09 = feet
                                        *	0A = glov
                                        *	0B = ralt
                                        *	0C = lalt
                                        */
    BYTE	page;						//+45
                                        /*	page dans laquel se trouve l'item
                                        *	FF = mouse/equip/onEarth
                                        *	00 = inventory
                                        *   01 = cube
                                        *	04 = stash
                                        */
    BYTE	uk4[0x01];					//+46
    BYTE	ItemData3;					//+47 //D2Common10854 D2Common10853
    BYTE	pEarLevel;					//+48
    BYTE	varGfx;						//+49
    char	IName[0x12];				//+4A //inscribed/ear name  
    Inventory*	ptInventory;			//+5C
    Unit*	ptPrevItem;					//+60
    Unit*	ptNextItem;					//+64
    BYTE	uk8[0x01];					//+68
    BYTE	ItemData2;					//+69
    BYTE	uk9[0x0A];					//+6A
};

struct PlayerData
{
    char		name[0x10];				//+00	Player Name  
    void*		ptQuest[3];				//+10	Quest Pointers for each difficulty  
    BYTE		uk1[0x18];				//+1C		//before : 0x14
    void*		ptArenaUnit;			//+34	ptArena for the Unit  
    BYTE		uk2[0x4];				//+38		//before : 0x7
    WORD		MPSourcePortalUniqueID;	//+3C	Source Portal Unique_ID  
    BYTE		uk3[0x2];				//+3E
    WORD		MPDestPortalUniqueID;	//+40	Destination Portal Unique_ID  
    BYTE		uk4[0x06];				//+42  
    BYTE		ptObjectUnID;			//+48	Object UniqueID for TownPortals       
    BYTE		uk5[0x53];				//+49  
    NetClient*	ptNetClient;			//+9C	ptClient  
};

struct Path //(8 dword)
{                              			//Offset from Code.		Size: 20
    WORD	uk1;						//+00
    WORD	mapx;						//+02
    WORD	uk2;						//+04
    WORD	mapy;						//+06
    DWORD	uk3;						//+08
    DWORD	x;							//+0C
    DWORD	y;							//+10
    DWORD	uk6;						//+14
    DWORD	uk7;						//+18
    Room*	ptRoom;						//+1C
};

struct D2Stat
{
    WORD	index;
    WORD	id;
    int		value;
};

struct Stats				//sizeof(Stats)=0x64
{
    DWORD	nUnitId;				//+00
    Unit*	ptUnit;					//+04
    DWORD	nUnitType;				//+08
    DWORD	nItemNum;				//+0C
    union
    {
        DWORD	flags;				//+10
        struct
        {
            DWORD fuk1 : 13;			//0x00001FFF
            DWORD isDisabled : 1;		//0x00002000
            DWORD fuk2 : 17;			//0x7FFFC000
            DWORD dontUseBaseValue : 1;//0x80000000
        };
    };
    DWORD	id;						//+14
    DWORD	uk18;					//+18
    BYTE	uk2[0x08];				//+1C
    D2Stat*	ptBaseStatsTable;		//+24
    WORD	nbBaseStats;			//+28
    WORD	sizeOfBaseStatsTable;	//+2A ??
    Stats*	ptStats;				//+2C
    BYTE	uk3[0x04];				//+30
    Stats*	ptItemStats;			//+34
    BYTE	uk4[0x04];				//+38
    Stats*	ptAffixStats;			//+3C
    Stats*	ptNextStats2;			//+40
    union
    {
        Unit*	ptChar;				//+44
        Unit*	ptItem;
    };
    D2Stat*	ptStatsTable;			//+48
    WORD	nbStats;				//+4C
    WORD	sizeOfStatsTable;		//+4E ??
    BYTE	uk5[0x8];				//+50
    BYTE*	unknow0;				//+58 (sizeof(*unknow0)=0x30 (calculated)
    DWORD	unknow1;				//+5C (=0)
    DWORD	unknow2;				//+60 (=0)
};

struct SkillData
{								//Offset from Code. (size = 0x3C or 0x40)
    void* /*SkillsBIN**/	ptSkillBin;		//+00
    SkillData*	ptNextSkill;	//+04
    DWORD	mode;           //+08
    DWORD	uk1[3];         //+0C
    DWORD	targetInfo;     //+18
    DWORD	targetType;     //+1c
    DWORD	targetUNID;     //+20
    DWORD	uk2;            //+24
    DWORD	slvl;           //+28
    DWORD	slvlBonus;      //+2c
    DWORD	uk3;            //+30
    int		state;          //+34 (-1 if index exist)
    DWORD	param1;			//+38 (nb current charge)
    DWORD	param2;			//+3C
};

struct Skills
{								//Offset from Code.
    DWORD		gameRelated;	//+00
    SkillData*	ptFirstSkill;	//+04
    SkillData*	ptLeftSkill;	//+08
    SkillData*	ptRightSkill;	//+0c
    SkillData*	ptCurrentSkill;	//+10
};

struct Unit
{										//Offset from Code.		Size: 0xF4+4
    DWORD		nUnitType;				//+00
    union {
        DWORD			nPlayerClass;
        DWORD			nTxtFileNo;
    };									//+04
    DWORD		nUnitId;				//+08
    DWORD		nItemNum;				//+0C
    DWORD		CurrentAnim;			//+10
    union {
        MonsterData*	ptMonsterData;
        ObjectData*		ptObjectData;
        ItemData*		ptItemData;
        PlayerData*		ptPlayerData;
    };									//+14
    BYTE		act;					//+18
    BYTE		uk12[3];				//+19
    void*		ptAct;					//+1C
    DWORD		SeedLow;				//+20
    DWORD		SeedHi;					//+24
    DWORD		SeedStarting;			//+28
    Path*		path;					//+2C
    BYTE		uk1[0x08];				//+30
    Path*		ptPos;					//+38
    DWORD		animSpeed;				//+3C
    BYTE		uk2[0x04];				//+40
    DWORD		curFrame;				//+44
    DWORD		remainingFrame;			//+48
    WORD		animSpeedW;				//+4C
    BYTE		actionFlag;				//+4E
    BYTE		uk3[0x1];				//+4F
    void*		ptAnimData;				//+50
    BYTE		uk4[0x08];				//+54
    Stats*		ptStats;				//+5C
    Inventory*	ptInventory;		    //+60
    BYTE		uk5[0x1C];				//+64
    Game*		ptGame;					//+80
    BYTE		uk6[0x24];				//+84
    Skills*		ptSkills;				//+A8
    void*		ptCombatData;			//+AC
    BYTE		uk7[0x08];				//+B0
    DWORD		itemCode;				//+B8 for an item being dropped by this unit
    BYTE		uk8[0x08];				//+BC
    DWORD		flags1;					//+C4
    union {
        DWORD		flags2;				//+C8	//flags
        struct {
            DWORD	ukf1 : 25;
            DWORD	isLod : 1;
        };
    };
    BYTE		uk9[0x04];				//+CC
    DWORD		clientId;				//+D0
    BYTE		uk10[0x0C];				//+D4
    Unit*		ptFirstMonster;			//+E0
    Unit*		Unit1;					//+E4
    Unit*		Unit2;					//+E8
    BYTE		uk11[0x08];				//+EC
    union {
        void* /*CBPlayerData**/	ptCBPlayerData;
        void* /*CBItemData**/		ptCBItemData;
        void*			ptCBData;
    };									//+F4
};

static_assert(sizeof(Unit) == 0xF4 + 4, "Check Unit structure padding");

struct Game								// sizeof 0x1DE8
{
    DWORD                   _00[6];				// +00
                                                //+00 is some sort of table - probably pGameTbl, passed from D2Client or D2Server...
                                                //+04 is some sort of seed - seed from the D2Client Game Marshal iirc
                                                //+08 to +14 is some stuff inited by the module(D2Client, D2Server) Marshalling the Game(s)
                                                //+10 appears to be D2GameStrc* pNext
    LPCRITICAL_SECTION      pSyncLock;          // +18 
    void* /*D2PoolManagerStrc**/      pMemPool;           // +1C
    int						nClientRelated;		// +20
    DWORD					dwUnk;				// +24
    WORD					wGameNumber;		// +28
    char                    szGameName[14];     // +2A 
    char                    szGameServerIp[16];	// +38
    char                    szAccountName[16];	// +48
    char                    szRealmName[18];	// +58    
    BYTE                    nGameType;          // +6A
    WORD                    _6B;	            // +6B
    BYTE                    nDifficulty;        // +6D 
    WORD                    wUnk2;              // +6E  - Cube puts 4 here
    BOOL                    bLOD;               // +70
    DWORD                   nGameMode;          // +74 0 at start-> ladder, normal etc...
    WORD                    nItemFormat;        // +78  
    WORD                    _7A;				// +7A
    DWORD                   pInitSeed[2];       // +7C - LoSeed set when GameSeed is created, HiSeed set when ObjectRegion is created
    BOOL                    bInitSeed;          // +84
    NetClient*              pClient;            // +88 
    int                     nClientCount;       // +8C
    int                     nPlayerCount;       // +90
    int                     nMonsterCount;      // +94
    int                     nObjectCount;       // +98
    int                     nMissileCount;      // +9C
    int                     nItemCount;         // +A0
    int                     nWarpTileCount;     // +A4
    int                     nCurrentFrame;      // +A8 
    DWORD                   dwCycleLastSecond;  // +AC
    DWORD                   dwCycleCount;       // +B0
    DWORD                   dwTickCount;        // +B4
    void* /*D2EventControlStrc**/     pEventControl;      // +B8
    Act*                    pAct[5];            // +BC
    DWORD                   pGameSeed[2];          // +D0
    void* /*D2InactiveControlStrc**/  pInactive[5];		// +D8
    DWORD                   dwMonSeed;          // +EC
    void* /*D2MonRegStrc**/           pMonRegion[1024];   // +F0
    void* /*D2ObjectControlStrc**/    pObjectControl;     // +10F0
    void* /*D2QuestControlStrc**/     pQuestControl;      // +10F4
    void* /*D2UnitNodeStrc**/         pNodeList[10];      // +10F8
    union
    {
        Unit*             pUnitList[5][128];  // +1120
        struct
        {
            Unit*                   pPlayerList[128];   // +1120
            Unit*                   pMonsterList[128];  // +1320
            Unit*                   pObjectList[128];   // +1520
            Unit*                   pItemList[128];     // +1720
            Unit*                   pMissileList[128];  // +1920
        };
    };
    Unit*                   pWarpTileList;      // +1B20
    DWORD                   fUniqueSpawn[128];  // +1B24 
    void* /*D2NPCDataStrc**/          pVendorControl;     // +1D24
    void* /*D2ArenaStrc**/            pArenaControl;      // +1D28
    void* /*D2PartyStrc**/            pPartyControl;      // +1D2C
    BYTE                    fBossSpawn[64];     // +1D30
    DWORD                   nPathCount[17];		// +1D70
    DWORD                   nPathCountTotal;    // +1DB4
    BOOL					bUpdateStatsTick;	// +1DB8 - this is mainly for the D2GS
    DWORD					dwStatsTick;		// +1DBC
    DWORD					dwLastUpdateTick;	// +1DC0
    DWORD					dwThreadPriority;	// +1DC4 - this is mainly for the D2GS
    DWORD                   dwUpdateTick;		// +1DC8
    DWORD                   dwUnknown;			// +1DCC - this is always zero, its for D2GS anyways
    DWORD					dwServerGame;		// +1DD0
    Game*				    pPrev;				// +1DD4
    Game*				    pNext;				// +1DD8	
    DWORD					dwException;		// +1DDC - has for exceptions 1 = NULL deref, 2 = 0xC0000001 deref, 3 = Assert with blank Msg, 4 = Alloc 1.7Gb of Mem(lol)
    DWORD					_1DE0[2];			// +1DE0 - these are unused, atleast in D2Game, haven't check D2Server, but v1.00 ain't reliable
};

static_assert(sizeof(Game) == 0x1DE0 + 8, "Check Game structure padding");

#pragma pack(pop)
