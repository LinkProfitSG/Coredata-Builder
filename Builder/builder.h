#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>
#include <format>

class Builder {
	const std::string key_ = "PBG892FXX982ABC*";
	const std::string outputFile_ = "Coredata";

	std::vector<std::string> split(const std::string& content, const char delimeter) {
		std::stringstream stream(content);
		std::string str;
		std::vector<std::string> result;

		while (std::getline(stream, str, delimeter)) result.push_back(str);

		return result;
	}
	std::string join(const std::vector<std::string> v, const char delimeter) {
		std::string str;

		for (auto p = v.begin(); p != v.end(); ++p) {
			str += *p;

			if (p != (v.end() - 1))
				str += delimeter;
		}

		return str;
	}
	std::string getItemCategory(const char actionType) {
		return actionType > itemCategories_.size() ? "" : itemCategories_[static_cast<std::size_t>(actionType)];
	}
public:
	void parseInfo(std::streamoff& fileSize, char*& data, int& totalItem, short& version) {
		std::ifstream fileStream("items.dat", std::ios::binary | std::ios::ate);
		fileSize = fileStream.tellg();
		data = new char[(static_cast<unsigned int>(fileSize))];
		
		if (fileSize == -1) 
			printf("Make sure the itmes.dat is at the same location as the executeable file.\n");

		fileStream.seekg(0, std::ios::beg);

		if (!fileStream.read(static_cast<char*>(data), fileSize))
			printf("Unable to read the items.dat.\n");

		int memPos = 0;

		memcpy(&version, data + memPos, 2);
		memPos += 2;
		memcpy(&totalItem, data + memPos, 4);
	}
	void buildCoredata() {
		std::streamoff fileSize;
		std::string outputFile = this->outputFile_;

		char* data;
		int totalItem;
		short version;

		parseInfo(fileSize, data, totalItem, version);

		int startItem = 0, endItem = totalItem;

		std::cout << std::format("items.dat version : {}\n", version);
		
		std::cout << std::format("Please enter a file name as the output. Press enter to ignore (Default: {}) : ", outputFile.c_str());
		std::getline(std::cin, outputFile);

		if (outputFile.empty()) outputFile = this->outputFile_;

		std::cout << std::format("Please enter the range of items that will be parsed. Press enter to ignore (Default: {}-{}) : ", startItem, totalItem);
		{
			std::string content;
			std::getline(std::cin, content);

			if (!content.empty()) {
				startItem = std::stoi(split(content, '-')[0]);
				endItem = std::stoi(split(content, '-')[1]);
			}
		}

		std::cout << std::format("Starting to parse from item \"{}\" to \"{}\" with %s as the output file...\n", startItem, endItem, outputFile.c_str());
		
		std::ofstream outStream(outputFile + ".txt");
		outStream << "// Item range : " << startItem << "-" << endItem << "\n";

		int memPos = 6;

		for (int i = startItem; i < endItem; i++) {
			int itemId = 0, growTime = 0;
			char itemCategory, actionType, clothType, breakHits;
			short rarity = 0;
			std::vector<std::string> properties;
			std::string itemName, clothingType = "None", category;

			memcpy(&itemId, data + memPos, 5);
			memPos += 5;
			
			itemCategory = data[memPos];
			memPos += 1;
			
			actionType = data[memPos];
			memPos += 2;

			{
				short length = *(short*)&data[memPos];
				memPos += 2;
				
				for (int j = 0; j < length; j++) {
					itemName += data[memPos] ^ (this->key_[(j + itemId) % this->key_.length()]);
					memPos++;
				}
			}
			{
				short length = *(short*)&data[memPos];
				memPos += 2;
				
				for (int j = 0; j < length; j++) memPos++;
			}
			memPos += 14;
			
			breakHits = data[memPos] / 6;
			memPos += 5;
			
			clothType = data[memPos];
			memPos += 1;
			
			memcpy(&rarity, data + memPos, 3);
			memPos += 3;

			{
				short length = *(short*)&data[memPos];
				memPos += 2;

				for (int j = 0; j < length; j++) memPos++;
			}
			memPos += 8;
			{
				short length = *(short*)&data[memPos];
				memPos += 2;

				for (int j = 0; j < length; j++) memPos++;
			}
			{
				short length = *(short*)&data[memPos];
				memPos += 2;

				for (int j = 0; j < length; j++) memPos++;
			}
			{
				short length = *(short*)&data[memPos];
				memPos += 2;

				for (int j = 0; j < length; j++) memPos++;
			}
			{
				short length = *(short*)&data[memPos];
				memPos += 2;

				for (int j = 0; j < length; j++) memPos++;
			}
			
			memPos += 24;

			memcpy(&growTime, data + (memPos - 8), 8);

			{
				short length = *(short*)&data[memPos];
				memPos += 2;

				for (int j = 0; j < length; j++) memPos++;
			}
			{
				short length = *(short*)&data[memPos];
				memPos += 2;

				for (int j = 0; j < length; j++) memPos++;
			}
			{
				short length = *(short*)&data[memPos];
				memPos += 2;

				for (int j = 0; j < length; j++) memPos++;
			}
			
			memPos += 80;

			if (version >= 11) {
				short length = *(short*)&data[memPos];
				memPos += 2;
				
				for (int j = 0; j < length; j++) {
					memPos++;
				}
			}
			if (version >= 12) memPos += 13;

			if (version >= 13) memPos += 4;

			if (itemCategory < 0) properties.emplace_back("Untradeable");

			category = getItemCategory(actionType);

			if (actionType == 20) {
				switch (clothType) {
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
			if ((itemId % 2) == 1) category = "Seed";

			std::string content =
				std::to_string(itemId) + "|" + itemName + "|" + std::to_string(rarity) + "|" +
				(properties.empty() ? "0" : join(properties, ',')) + "|" + category + "|" +
				"0|0|" + std::to_string(breakHits) + "|" + std::to_string(growTime) + "|" + clothingType;
			
			outStream << content << '\n';
		}
		outStream.close();

		std::cout << std::format("{}.txt has been successfully built.\n", outputFile.c_str());
		std::cout << std::format("items.dat version with version \"{}\" with \"{}\" total item in it.)", version, totalItem);
	}
private:
	std::array<std::string, 130> itemCategories_ = {
		"Fist",
                "Wrench",
                "Door",
                "Lock",
                "Gems",
                "Treasure",
                "Deadly_Block",
                "Trampoline_Block",
                "Consummable",
                "Gateway",
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
                "SFX_Background",
                "Toggleable_Background",
                "Bouncy",
                "Spike",
                "Portal",
                "Checkpoint",
                "Sheet_Music",
                "Slippery_Block",
                "Unknown",
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
                "Unknown",
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
                "Steam_Pain_Block",
                "Steam_Music_Block",
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
                "Chemsynth",
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
};
