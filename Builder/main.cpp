#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;
typedef unsigned char BYTE;

template<typename T>
string join(const T& vec, char delimeter) {
	string str;

	for (auto p = vec.begin(); p != vec.end(); p++) {
		str += *p;

		if (p != (vec.end() - 1))
			str += delimeter;
	}

	return str;
}

void appendFile(string file, string str) {
	ofstream ofs(file, ios_base::out | ios::app);
	ofs << str << endl;
}

void build() {
	string secret = "PBG892FXX982ABC*";
	ifstream file("items.dat", ios::binary | ios::ate);
	int size = (int)file.tellg();

	if (size == -1) {
		cout << "Unable to load items.dat! Make sure you have items.dat in the current directory" << endl;
		return;
	}

	char* data = new char[size];
	file.seekg(0, ios::beg);

	if (file.read((char*)(data), size)) 
		cout << "Starting to decode items.dat..." << endl;
	else {
		cout << "Updating items.dat failed!" << endl;
		return;
	}

	int itemCount, memPos = 0;
	int16_t version;

	memcpy(&version, data + memPos, 2);
	memPos += 2;
	memcpy(&itemCount, data + memPos, 4);
	memPos += 4;

	string fileName = "Coredata.txt";

	appendFile(fileName, "//Start by parsing this in your map/dictionary to parse the other data.");
	appendFile(fileName, "//ID|Item Name|Rarity|Properties|Category|Base Color|Overlay Color|Hits to break|Growtime in seconds|Clothing Type (None if its not a clothing,specified in category)\n\n");

	for (int i = 0; i < itemCount; i++) {
		int itemID, extraFileHash, seedColor, growTime = 0;
		char itemCategory, actionType, clothType, breakHits;
		int16_t rarity;
		vector<string> properties;
		string itemName, clothingType = "None", category;;

		memcpy(&itemID, data + memPos, 5);
		memPos += 5;

		itemCategory = data[memPos];
		memPos += 1;

		actionType = data[memPos];
		memPos += 2;

		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				itemName += data[memPos] ^ (secret[(j + itemID) % secret.length()]);
				memPos++;
			}
		}
		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}

		memPos += 14;
		breakHits = data[memPos];

		memPos += 5;
		clothType = data[memPos];

		memPos += 1;
		memcpy(&rarity, data + memPos, 3);
		memPos += 3;

		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}

		memcpy(&extraFileHash, data + memPos, 8);
		memPos += 8;

		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}
		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}
		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}
		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}
		memPos += 4;

		memcpy(&seedColor, data + memPos, 12);
		memPos += 12;

		memcpy(&growTime, data + memPos, 8);
		memPos += 8;

		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}
		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}
		{
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;

			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}

		memPos += 80;

		if (version >= 11) {
			int16_t len = *(int16_t*)&data[memPos];
			memPos += 2;
			for (int j = 0; j < len; j++) {
				memPos++;
			}
		}

		if (version >= 12)
			memPos += 13;

		bool untradeable = false, autopickup = false, mod = false;
		
		switch (itemCategory) {
		case 2:
			autopickup = true;
			break;
		case 4:
			mod = true;
			break;
		case -123:
			mod = true;
		case -126:
			autopickup = true;
		}

		if ((itemCategory * -1) > 0)
			untradeable = true;

		if (mod)
			properties.push_back("Mod");
		if (untradeable)
			properties.push_back("Untradable");
		if (autopickup)
			properties.push_back("AutoPickup");

		switch (actionType) {
		case 0:
			category = "Fist";
			break;
		case 3:
			category = "Lock";
			break;
		case 10:
			category = "Sign";
			break;
		case 13:
			category = "Main_Door";
			break;
		case 15:
			category = "Bedrock";
			break;
		case 17:
			category = "Foreground_Block";
			break;
		case 18:
			category = "Background_Block";
			break;
		case 20:
			category = "Clothing";
			switch (clothType) {
			case 0:
				clothingType = "Hair";
				break;
			case 1:
				clothingType = "Shirt";
				break;
			case 2:
				clothingType = "Pants";
				break;
			case 3:
				clothingType = "Feet";
				break;
			case 4:
				clothingType = "Face";
				break;
			case 5:
				clothingType = "Hand";
				break;
			case 6:
				clothingType = "Back";
				break;
			case 7:
				clothingType = "Mask";
				break;
			case 8:
				clothingType = "Necklace";
				break;
			default:
				break;
			}
			break;
		case 26:
			clothingType = "Door";
			break;
		case 27:
			category = "Checkpoint";
			break;
		case 28:
			category = "Background_Block";
			break;
		case 31:
			category = "Switch_Block";
			break;
		case 34:
			category = "Bulletin_Board";
			break;
		case 107:
			clothingType = "Artifact";
			category = "Artifact";
			break;
		default:
				break;
		}

		if (itemID % 2 == 1)
			category = "Seed";

		//ID|Item Name|Rarity|Properties|Category|Base Color|Overlay Color|Hits to break|Growtime in seconds|Clothing Type (None if its not a clothing,specified in category)

		string propertyStr = (properties.empty()) ? "0" : join(properties, ',');

		string str = to_string(itemID) + "|" + itemName + "|" + to_string(rarity) + "|";
		str.append(propertyStr + "|" + category + "|000000|000000|" + to_string(breakHits) + "|");
		str.append(to_string(growTime) + "|" + clothingType);

		appendFile(fileName, str);
	}

	cout << "Coredata.txt has been built! There are " << itemCount << " items in total" << endl;
}

int main() {
	cout << "Building..." << endl;

	build();

	char c;
	cin >> c;

	return 0;
}