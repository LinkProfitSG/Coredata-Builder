#include <fstream>
#include <filesystem>
#include <iostream>
#include <format>
#include <string>
#include <array>
#include <cassert>
#include <vector>
#include <charconv>

namespace {
	std::array<std::string, 130> categoryNames = {
		"Fist",
		"Wrench",
		"Door",
		"Lock",
		"Gems",
		"Treasure",
		"Deadly_Block",
		"Trampoline_Block",
		"Consumable",
		"Gateaway",
		"Sign",
		"SFX_Foreground",
		"Toggleable_Foreground",
		"Main_Door",
		"Platform",
		"Bedrock",
		"Pain_Block",
		"Foreground_Block",
		"Background_Block",
		"Seed",
		"Clothing",
		"Animated_Foreground_Block",
		"SFX_BACKGROUND",
		"Toggleable_Background",
		"Bouncy",
		"Spike",
		"Portal",
		"Checkpoint",
		"Sheet_Music",
		"Slippery_Block",
		"Switch_Block",
		"Chest",
		"Mailbox",
		"Bulletin_Board",
		"Event_Mystery_Block",
		"Random_Block",
		"Component",
		"Provider",
		"Chemical_Combiner",
		"Achievement_Block",
		"Weather_Machine",
		"Scoreboard",
		"Sungate",
		"Profile",
		"Toggleable_Deadly_Block",
		"Heart_Monitor",
		"Donation_Box",
		"Mannequin",
		"Security_Camera",
		"Magic_Egg",
		"Game_Block",
		"Game_Generator",
		"Xenonite",
		"Phone_Booth",
		"Crystal",
		"Crime_Villain",
		"Clothing_Compactor",
		"Spotlight",
		"Pushing_Block",
		"Display",
		"Vending",
		"Fish",
		"Fish_Tank_Port",
		"Solar_Collector",
		"Forge",
		"Giving_Tree",
		"Giving_Tree_Stump",
		"Steam_Block",
		"Stream_Pain_Block",
		"Stream_Music_Block",
		"Silkworm",
		"Sewing_Machine",
		"Country_Flag",
		"Lobster_Trap",
		"Painting_Easel",
		"Battle_Pet_Cage",
		"Pet_Trainer",
		"Steam_Engine",
		"Lock_Bot",
		"Weather_Machine_S1",
		"Spirit_Storage",
		"Display_Shelf",
		"VIP",
		"Chal_Timer",
		"Chal_Flag",
		"Fish_Mount",
		"Portrait",
		"Weather_Machine_S2",
		"Fossil",
		"Fossil_Prep_Station",
		"DNA_Processor",
		"Blaster",
		"Valhowla_Treasure",
		"Chemsynth_Tank",
		"Untrade_A_Box",
		"Oven",
		"Audio",
		"Geiger_Charger",
		"Adventure_Reset",
		"Tomb_Robber",
		"Faction",
		"Red_Faction",
		"Green_Faction",
		"Blue_Faction",
		"Artifact",
		"LemonJelly",
		"FishTrainingTank",
		"FishingBlock",
		"ItemSucker",
		"Planter",
		"Robot",
		"Command",
		"Ticket",
		"Stats_Block",
		"Field_Node",
		"Ouija_Board",
		"Architect_Machine",
		"Starship",
		"Spike",
		"Gravity_Well",
		"Autobreak_Blocks",
		"Autobreak_Trees",
		"Autobreak",
		"TimedBlock",
		"TimedPlatform",
		"Mud_Puddle",
		"Root_Cutting",
		"Safe_Vault"
	};
}

int main() {
	assert(std::filesystem::exists("items.dat"));

	std::size_t dataLength = std::filesystem::file_size("items.dat");

	std::byte* data = new std::byte[dataLength];
	std::ifstream("items.dat", std::ios::binary).read(std::bit_cast<char*>(data), dataLength);

	int memPos = 0;

	short dataVersion = *std::bit_cast<short*>(data + memPos);
	memPos += sizeof(short);
	std::cout << "Current items.dat version: " << dataVersion << '\n';

	int arraySize = *std::bit_cast<int*>(data + memPos);
	memPos += sizeof(int);
	std::cout << "Total items in items.dat: " << arraySize << '\n';

	int itemId = 0;

	if (std::filesystem::exists("Coredata.txt")) /* Coredata.txt checking (Append only if exists) */ {
		std::vector<std::string> lines;

		std::ifstream fstream("Coredata.txt");
		for (std::string line; std::getline(fstream, line);) {
			if (line.empty()) continue;
			lines.emplace_back(line);
		}

		if (!lines.empty()) {
			std::string itemIdStr = lines.back().substr(0, lines.back().find('|'));
			std::from_chars(itemIdStr.data(), itemIdStr.data() + itemIdStr.length(), itemId);

			itemId++;

			std::cout << "Coredata.txt found, appending definitions from id: " << itemId << '\n';
		}
	}

	std::ofstream fstream("Coredata.txt", std::ios::app);

	struct {
		std::string name;

		int id;
		int breakHits;

		char category;
		char clothType;

		short actionType;
		short rarity;

		std::int64_t growTime;
	} itemInfo = {};

	const std::string itemNameKey = "PBG892FXX982ABC*";

	for (int i = 0; i < arraySize; i++) {
		itemInfo.id = *std::bit_cast<int*>(data + memPos);
		memPos += sizeof(int) + sizeof(char);

		itemInfo.category = *std::bit_cast<char*>(data + memPos);
		memPos += sizeof(char);

		itemInfo.actionType = *std::bit_cast<char*>(data + memPos);
		memPos += sizeof(short);

		{
			itemInfo.name.clear();

			short length = *std::bit_cast<short*>(data + memPos);
			memPos += sizeof(short);

			for (short j = 0; j < length; j++) {
				itemInfo.name += (*std::bit_cast<char*>(data + memPos)) ^ (itemNameKey[(itemInfo.id + j) % itemNameKey.length()]);
				memPos += sizeof(char);
			}
		}

		memPos += *std::bit_cast<short*>(data + memPos) + sizeof(short);

		memPos += 14;

		itemInfo.breakHits = *std::bit_cast<char*>(data + memPos) / 6;
		memPos += sizeof(int) + sizeof(char);

		itemInfo.clothType = *std::bit_cast<char*>(data + memPos);
		memPos += sizeof(char);

		itemInfo.rarity = *std::bit_cast<short*>(data + memPos);
		memPos += sizeof(short) + sizeof(char);

		memPos += *std::bit_cast<short*>(data + memPos) + sizeof(short);

		memPos += sizeof(int) * 2;

		for (int j = 0; j < 4; j++)
			memPos += *std::bit_cast<short*>(data + memPos) + sizeof(short);

		memPos += 16;

		itemInfo.growTime = *std::bit_cast<std::int64_t*>(data + memPos);
		memPos += sizeof(std::int64_t);

		for (int j = 0; j < 3; j++)
			memPos += *std::bit_cast<short*>(data + memPos) + sizeof(short);

		memPos += 80;

		if (dataVersion >= 11) memPos += *std::bit_cast<short*>(data + memPos) + sizeof(short);

		if (dataVersion >= 12) memPos += 13;

		if (dataVersion >= 13) memPos += sizeof(int);

		if (dataVersion >= 14) memPos += sizeof(int);

		if (itemInfo.id < itemId) continue;

		std::string actionType = itemInfo.actionType > categoryNames.size() ? "" : categoryNames[static_cast<std::size_t>(itemInfo.actionType)];

		if (itemInfo.id % 2 != 0) actionType = "Seed";

		std::string clothingType = "None";
		if (itemInfo.actionType == 20) {
			switch (itemInfo.clothType) {
				case 0: clothingType = "Hair";
					break;
				case 1: clothingType = "Shirt";
					break;
				case 2: clothingType = "Pants";
					break;
				case 3: clothingType = "Feet";
					break;
				case 4: clothingType = "Face";
					break;
				case 5: clothingType = "Hand";
					break;
				case 6: clothingType = "Back";
					break;
				case 7: clothingType = "Mask";
					break;
				case 8: clothingType = "Necklace";
					break;
				default: break;
			}
		}

		fstream << std::format("\n{}|{}|{}|0|{}|0|0|{}|{}|{}", itemInfo.id, itemInfo.name, itemInfo.rarity, actionType, itemInfo.breakHits, itemInfo.growTime, clothingType);
	}

	std::cout << "Coredata.txt was successfully built.";

	std::getchar();
	return 0;
}