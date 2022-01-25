#pragma once

#include "Entity.h"
#include "myMath.h"
#include <vector>
#include <list>
#include "UM-Memory.h"
#include <map>

//game structs
//[Base + g_BN_Steam] + oEntityRealm] + oClientEntitiesList] + oClientEntitiesValues]
//client entities = read()
#define oItemClass 0x50
#define oItemProfile 0x40
#define oItemID 0x50
#define oIDLength 0x10		//int
#define oItemIDString 0x14	//string

//EFT.Player Class
#define oPlayerProfile 0x4B8 //EFT.Profile

//PlayerProfile Class
#define oPlayerInfo 0x28	//info gclass1409

//PlayerInfo Class
#define oNickname 0x10
#define oPlayerSide 0x58


struct EFTOffsets
{
	static constexpr uint64_t oGOM = 0x17F8D28;

	uint64_t gameObjectManager = 0x0;
	uint64_t gameWorld = 0x0;
	uint64_t localGameWorld = 0x0;
	uint64_t fpsCamera = 0x0;
	uint64_t OpticCamera = 0x0;
	uint64_t lootList = 0x0;

	struct
	{
		static constexpr uint64_t lootList = 0x60; //UPDATED 1/24/2022
		static constexpr uint64_t registeredPlayers = 0x80; //UPDATED 1/20/2022
		static constexpr uint64_t m_LocalPlayerID = 0x38;				//0x30;
	} localGameWorld_offsets;

	struct
	{
		static constexpr uint64_t length = 0x10; //good
		static constexpr uint64_t stringBase = 0x14; //good
	} unicodeString;

	struct
	{
		static constexpr uint64_t information = 0x28; //updated
		static constexpr uint64_t id = 0x10; //updated
		static constexpr uint64_t position = 0x640; //updated //Vector3
	} profile;

	struct
	{
		static constexpr uint64_t playerName = 0x10; //updated	//String
		static constexpr uint64_t playerSide = 0x58; //updated	//EFT.PlayerSide
		static constexpr uint64_t registrationDate = 0x5c; //updated //int32
		static constexpr uint64_t settings = 0x38; //updated //int32
	} information;	//	\uE647

	struct
	{
		static constexpr uint64_t role = 0x10; //updated	//enum WildSpawnType
	} settings;	//	\uE647


	struct
	{
		static constexpr uint64_t angles_0 = 0x1D0;
		static constexpr uint64_t angles_1 = 0x1D8;
		static constexpr uint64_t position = 0x1E0;
	} movementContext;

	struct
	{
		static constexpr uint64_t m_pPlayerProfile = 0x4B8;	//idk
		static constexpr uint64_t movementContext = 0x38;	//idk
		static constexpr uint64_t proceduralWeaponAnimation = 0x70; //updayed 1/11/2022
		static constexpr uint64_t playerBody = 0xa8; //updated 1/11/2022
		static constexpr uint64_t m_pHealthController = 0x4f0; //updated 1/11/2022
		static constexpr uint64_t profile = 0x4B8; //updayed 1/11/2022

	} Player;
};

namespace EFTStructs
{
	struct BaseObject
	{
		uint64_t previousObjectLink; //0x0000
		uint64_t nextObjectLink; //0x0008
		uint64_t object; //0x0010
	};

	struct GameObjectManager
	{
		uint64_t lastTaggedObject; //0x0000
		uint64_t taggedObjects; //0x0008
		uint64_t lastCamera; //0x0010
		uint64_t cameraObjects; //0x0018
		uint64_t lastActiveObject; //0x0020
		uint64_t activeObjects; //0x0028
	}; //Size: 0x0010

	class ListInternal
	{
	public:
		char pad_0x0000[0x20]; //0x0000
		uintptr_t* firstEntry; //0x0020 
	}; //Size=0x0028

	class List
	{
	public:
		char pad_0x0000[0x10]; //0x0000
		ListInternal* listBase; //0x0010 
		__int32 itemCount; //0x0018 
	}; //Size=0x001C
}

struct EFTPlayer
{
	uintptr_t	 instance;
	FVector		 headPos;
	FVector		 position;
	std::string	 name;
	std::string  type;
};

struct EFTExtract
{
	uintptr_t	 instance;
	std::string  name;
	FVector		 location;
};

struct EFTLoot
{
	uintptr_t	instance;
	std::string id;
	std::string name;
	Vector3		origin;
};

enum BodyParts : uint64_t
{
	Head = 0x20,
	Thorax = 0x28,
	Stomach = 0x30,
	LeftArm = 0x38,
	RightArm = 0x40,
	LeftLeg = 0x48,
	RightLeg = 0x50,
	value_max
};

enum EPlayerSide : int
{
	// Token: 0x04005C75 RID: 23669
	Usec = 1,
	// Token: 0x04005C76 RID: 23670
	Bear,
	// Token: 0x04005C77 RID: 23671
	Savage = 4
};

enum WildSpawnType : int
{
	marksman = 1,
	assault = 2,
	bossTest = 4,
	bossBully = 8,
	followerTest = 16,
	followerBully = 32,
	bossKilla = 64,
	bossKojaniy = 128,
	followerKojaniy = 256,
	pmcBot = 512,
	cursedAssault = 1024,
	bossGluhar = 2048,
	followerGluharAssault = 4096,
	followerGluharSecurity = 8192,
	followerGluharScout = 16384,
	followerGluharSnipe = 32768,
	followerSanitar = 65536,
	bossSanitar = 131072,
	test = 262144,
	assaultGroup = 524288,
	sectantWarrior = 1048576,
	sectantPriest = 2097152,
	bossTagilla = 4194304,
	followerTagilla = 8388608
};

class EFTData
{
public:
	static EFTData* Instance();

	bool InitOffsets();

	FVector GetPosition(uint64_t transform);

	bool Read();
	bool loopThroughList();
	bool UpdatePlayerList();

	EFTPlayer localPlayer;
	std::vector<EFTPlayer> players;
	std::vector<EFTExtract> extracts;
	std::vector<EFTLoot> loots;
	std::map<std::string, std::vector<EFTLoot>> lootDict;

    std::map<std::string, std::string> ItemIdDict;
	bool setupItemIdDict();

	int          playercount;

	FVector getPlayerPos(uintptr_t playerProfile);
	bool setupPlayer(uint64_t playerAddress);

	bool IsAiming(uint64_t instance);

	uint64_t get_mpcamera(uint64_t instance);
	bool open_extract(uint64_t extract);

	EFTOffsets offsets;

	bool IsPlayer(uint64_t instance);
private:
	uint64_t matrix_list_base = 0;
	uint64_t dependency_index_table_base = 0;

	uint64_t GetObjectFromList(uint64_t list, uint64_t lastObject, const char* objectName);
	uint64_t getbone_matrix(uint64_t instance);





	//std::vector<std::wstring> names;
};

enum Bones : int
{
	HumanBase = 0,
	HumanPelvis = 14,
	HumanLThigh1 = 15,
	HumanLThigh2 = 16,
	HumanLCalf = 17,
	HumanLFoot = 18,
	HumanLToe = 19,
	HumanRThigh1 = 20,
	HumanRThigh2 = 21,
	HumanRCalf = 22,
	HumanRFoot = 23,
	HumanRToe = 24,
	HumanSpine1 = 29,
	HumanSpine2 = 36,
	HumanSpine3 = 37,
	HumanLCollarbone = 89,
	HumanLUpperarm = 90,
	HumanLForearm1 = 91,
	HumanLForearm2 = 92,
	HumanLForearm3 = 93,
	HumanLPalm = 94,
	HumanRCollarbone = 110,
	HumanRUpperarm = 111,
	HumanRForearm1 = 112,
	HumanRForearm2 = 113,
	HumanRForearm3 = 114,
	HumanRPalm = 115,
	HumanNeck = 132,
	HumanHead = 133
}; 
