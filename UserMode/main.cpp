#include "UM-Memory.h"
#include "GameSDK.h"
#include "globalFunctions.h"
#include "RenderGraphics.h"
Memory* mem = nullptr;
UINT64 StringAddress = 0;

//radar






//TARKOV
auto gameData = EFTData::Instance();
void gameLoop() {
	getSettings();
	Radar myRadar = Radar::Radar(1080, 1080);
	myRadar.drawWindowTesting();
	gameData->setupItemIdDict();
	while (true) {

		if (!gameData->Read()) {
			myRadar.drawBlank();
			gameData->InitOffsets();
		}

		gameData->Read();	//setsup players
		gameData->loopThroughList();	//setsup loot

		//check if player count == new player count
		//if not then Read()
		//if(!gameData->refreshPlayerCount())
		//	gameData->Read();

		//loop through our player list
			//check if dead
				//if dead remove from our playerlist?
			//if not dead
				//draw location on radar

		if (gameData->players.empty()) {
			myRadar.drawBlank();
			Sleep(100);
			continue;
		}

		myRadar.setRange(200);
		myRadar.createPlayerBlips(gameData->localPlayer, true);
		for (int i = 0; i < gameData->players.size(); i++) {
			if (i == 0) continue;
			myRadar.createPlayerBlips(gameData->players[i], false);
		}

		//this prints the location of loot
		for (int i = 0; i < selectedItems.size(); i++) {
			if (gameData->lootDict.find(selectedItems[i]) != gameData->lootDict.end()) {
				//if selected item has spawned
				std::vector<EFTLoot> itemVector = gameData->lootDict[selectedItems[i]];
				for (int j = 0; j < itemVector.size(); j++) {
					myRadar.createLootBlips(itemVector[j]);
				}
			}
		}
		//render RADAR
			myRadar.drawWindowTesting();
		
		myRadar.clearBlips();
		if (GetKeyState(VK_END) & 0x8000) {
			break;
		}

		Sleep(100);
	}
}
int main()
{
	//printf("PID: %d", process_id);
	//printf("Base Address: %Id", base_address);
	bool breakVal = false;
	
	auto gameName = skCrypt("EscapeFromTarkov.exe");
	auto gameBase = skCrypt("UnityPlayer.dll");
	process_id = mem->get_process_id(gameName.decrypt());
	base_address = mem->get_module_base_address(gameBase.decrypt());
	gameName.clear();
	gameBase.clear();
	

	if (!base_address)
	{
		Radar myRadar = Radar::Radar(1280, 720);
		myRadar.drawWindowTesting();
		printf(skCrypt("GOD MOTHAFUCKIN DAAAAAAAAAAAMN"));
		Sleep(5000);
	}
	{
		//printf("Yes\n");
		//printf("PID: %d\n", process_id);
		//printf("Base Address: %Id\n", base_address);
			
		gameLoop();
		breakVal = true;
	}
	std::cout << skCrypt("CLOSING");
	Sleep(10000);
	return NULL;
}