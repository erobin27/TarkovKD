#include "UM-Memory.h"
#include "GameSDK.h"
#include "globalFunctions.h"
Memory* mem = nullptr;
UINT64 StringAddress = 0;
//TARKOV
auto gameData = EFTData::Instance();
void gameLoop() {
	getSettings();
	cout << selectedItems[0];
	gameData->setupItemIdDict();
	while (true) {

		if (!gameData->Read())
			gameData->InitOffsets();

		gameData->Read();
		gameData->loopThroughList();

		for (int i = 0; i < selectedItems.size(); i++) {
			if (gameData->lootDict.find(selectedItems[i]) != gameData->lootDict.end()) {
			//if selected item has spawned
				std::vector<EFTLoot> itemVector = gameData->lootDict[selectedItems[i]];
			for (int j = 0; j < itemVector.size(); j++) {
				cout << itemVector[j].name << ": " << itemVector[j].origin.x << ", " << itemVector[j].origin.y << ", " << itemVector[j].origin.z << endl;
			}


			}
			//std::cout << gameData->lootDict[selectedItems[i]][0].name << ":\t" << gameData->lootDict["Physical bitcoin"][0].origin.x << ", " << gameData->lootDict["Physical bitcoin"][0].origin.y << ", " << gameData->lootDict["Physical bitcoin"][0].origin.z << std::endl;
		}
		//render RADAR

		if (GetKeyState(VK_END) & 0x8000) {
			break;
		}

		Sleep(60000);
	}
}
int main()
{
	printf("PID: %d", process_id);
	printf("Base Address: %Id", base_address);
	bool breakVal = false;
	
	auto gameName = skCrypt("EscapeFromTarkov.exe");
	auto gameBase = skCrypt("UnityPlayer.dll");
	process_id = mem->get_process_id(gameName.decrypt());
	base_address = mem->get_module_base_address(gameBase.decrypt());
	gameName.clear();
	gameBase.clear();
	

	if (!base_address)
	{
		printf("GOD MOTHAFUCKIN DAAAAAAAAAAAMN");
		Sleep(5000);
	}
	else
	{
		printf("Yes\n");
		printf("PID: %d\n", process_id);
		printf("Base Address: %Id\n", base_address);
			
		gameLoop();
		breakVal = true;
	}
	std::cout << "CLOSING";
	Sleep(10000);
	return NULL;
}