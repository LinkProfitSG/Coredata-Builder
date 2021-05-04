#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>

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
		switch (actionType) {
			case 0:
				return "Fist";
			case 1:
				return "Wrench";
			case 2:
				return "Door";
			case 3:
				return "Lock";
			case 4:
				return "Gems";
			case 5:
				return "Treasure";
			case 6:
				return "Deadly_Block";
			case 7:
				return "Trampoline_Block";
			case 8:
				return "Consummable";
			case 9:
				return "Gateway";
			case 10:
				return "Sign";
			case 11:
				return "SFX_Foreground";
			case 12:
				return "Toggleable_Foreground";
			case 13:
				return "Main_Door";
			case 14:
				return "Platform";
			case 15:
				return "Bedrock";
			case 16:
				return "Pain_Block";
			case 17:
				return "Foreground_Block";
			case 18:
				return "Background_Block";
			case 19:
				return "Seed";
			case 20:
				return "Clothing";
			case 21:

				return "Animated_Foreground_Block";
				

			case 22:

				return "SFX_Background";
				

			case 23:

				return "Toggleable_Background";
				

			case 24:

				return "Bouncy";
				

			case 25:

				return "Spike";
				

			case 26:

				return "Portal";
				

			case 27:

				return "Checkpoint";
				

			case 28:

				return "Sheet_Music";
				

			case 29:

				return "Slippery_Block";
				

			case 30:
			case 48:

				return "Unknown";
				

			case 31:

				return "Switch_Block";
				

			case 32:

				return "Chest";
				

			case 33:

				return "Mailbox";
				

			case 34:

				return "Bulletin_Board";
				

			case 35:

				return "Event_Mystery_Block";
				

			case 36:

				return "Random_Block";
				

			case 37:

				return "Component";
				

			case 38:

				return "Provider";
				

			case 39:

				return "Chemical_Combiner";
				

			case 40:

				return "Achievement_Block";
				

			case 41:

				return "Weather_Machine";
				

			case 42:

				return "Scoreboard";
				

			case 43:

				return "Sungate";
				

			case 44:

				return "Profile";
				

			case 45:

				return "Toggleable_Deadly_Block";
				

			case 46:

				return "Heart_Monitor";
				

			case 47:

				return "Donation_Box";
				

			case 49:

				return "Mannequin";
				

			case 50:

				return "Security_Camera";
				

			case 51:

				return "Magic_Egg";
				

			case 52:

				return "Game_Block";
				

			case 53:

				return "Game_Generator";
				

			case 54:

				return "Xenonite";
				

			case 55:

				return "Phone_Booth";
				

			case 56:

				return "Crystal";
				

			case 57:

				return "Crime_Villain";
				

			case 58:

				return "Clothing_Compactor";
				

			case 59:

				return "Spotlight";
				

			case 60:

				return "Pushing_Block";
				

			case 61:

				return "Display";
				

			case 62:

				return "Vending";
				

			case 63:

				return "Fish";
				

			case 64:

				return "Fish_Tank_Port";
				

			case 65:

				return "Solar_Collector";
				

			case 66:

				return "Forge";
				

			case 67:

				return "Giving_Tree";
				

			case 68:

				return "Giving_Tree_Stump";
				

			case 69:

				return "Steam_Block";
				

			case 70:

				return "Steam_Pain_Block";
				

			case 71:

				return "Steam_Music_Block";
				

			case 72:

				return "Silkworm";
				

			case 73:

				return "Sewing_Machine";
				

			case 74:

				return "Country_Flag";
				

			case 75:

				return "Lobster_Trap";
				

			case 76:

				return "Painting_Easel";
				

			case 77:

				return "Battle_Pet_Cage";
				

			case 78:

				return "Pet_Trainer";
				

			case 79:

				return "Steam_Engine";
				

			case 80:

				return "Lock_Bot";
				

			case 81:

				return "Weather_Machine_S1";
				

			case 82:

				return "Spirit_Storage";
				

			case 83:

				return "Display_Shelf";
				

			case 84:

				return "VIP";
				

			case 85:

				return "Chal_Timer";
				

			case 86:

				return "Chal_Flag";
				

			case 87:

				return "Fish_Mount";
				

			case 88:

				return "Portrait";
				

			case 89:

				return "Weather_Machine_S2";
				

			case 90:

				return "Fossil";
				

			case 91:

				return "Fossil_Prep_Station";
				

			case 92:

				return "DNA_Processor";
				

			case 93:

				return "Blaster";
				

			case 94:

				return "Valhowla_Treasure";
				

			case 95:

				return "Chemsynth";
				

			case 96:

				return "Chemsynth_Tank";
				

			case 97:

				return "Untrade_A_Box";
				

			case 98:

				return "Oven";
				

			case 99:

				return "Audio";
				

			case 100:

				return "Geiger_Charger";
				

			case 101:

				return "Adventure_Reset";
				

			case 102:

				return "Tomb_Robber";
				

			case 103:

				return "Faction";
				

			case 104:

				return "Red_Faction";
				

			case 105:

				return "Green_Faction";
				

			case 106:

				return "Blue_Faction";
				

			case 107:

				return "Artifact";
				

			case 108:

				return "LemonJelly";
				

			case 109:

				return "FishTrainingTank";
				

			case 110:

				return "FishingBlock";
				

			case 111:

				return "ItemSucker";
				

			case 112:

				return "Planter";
				

			case 113:

				return "Robot";
				

			case 114:

				return "Command";
				

			case 115:

				return "Ticket";
				

			case 116:

				return "Stats_Block";
				

			case 117:

				return "Field_Node";
				

			case 118:

				return "Ouija_Board";
				

			case 119:

				return "Architect_Machine";
				

			case 120:

				return "Starship";
				

			case 121:

				return "Spike";
				

			case 122:

				return "Gravity_Well";
				

			case 123:

				return "Autobreak_Blocks";
				

			case 124:

				return "Autobreak_Trees";
				

			case 125:

				return "Autobreak";
				

			case 126:

				return "TimedBlock";
				

			case 127:

				return "TimedPlatform";
				

			case 128:

				return "Mud_Puddle";
				

			case 129:

				return "Root_Cutting";
				

			case 130:

				return "Safe_Vault";
				

			default:
				return "";
		}
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

		printf("items.dat version : %d\n", version);
		
		printf("Please enter a file name as the output. Press enter to ignore (Default: %s) : ", outputFile.c_str());
		std::getline(std::cin, outputFile);

		if (outputFile.empty()) outputFile = this->outputFile_;

		printf("Please enter the range of items that will be parsed. Press enter to ignore (Default: %i-%i) : ", startItem, totalItem);
		{
			std::string content;
			std::getline(std::cin, content);

			if (!content.empty()) {
				startItem = std::stoi(split(content, '-')[0]);
				endItem = std::stoi(split(content, '-')[1]);
			}
		}

		printf(R"(Starting to parse from item "%i" to "%i" with %s as the output file...)", startItem, endItem, outputFile.c_str());
		printf("\n");
		
		std::ofstream outStream(outputFile + ".txt");
		outStream << "Item range : " << startItem << "-" << endItem << "\n";

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
			
			outStream << content << std::endl;
		}
		outStream.close();

		printf("%s.txt has been successfully built.\n", outputFile.c_str());
		printf(R"(items.dat version with version "%i" with "%i" total item in it.)", version, totalItem);
	}
};
