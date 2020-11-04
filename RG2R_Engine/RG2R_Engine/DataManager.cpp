#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager() {}

DataManager::~DataManager() {}

DataManager* DataManager::Insert(const std::string& key, int value) {
	datas.insert(std::pair<std::string, int>(key, value));

	return this;
}

DataManager* DataManager::Save(const std::string& path) {
	std::ofstream writeFile;
	writeFile.open(path);

	for (auto iter : datas) {
		std::string data = iter.first + ":" + std::to_string(iter.second) + "\n";

		writeFile.write(data.c_str(), data.size());
	}

	return this;
}

DataManager* DataManager::Load(const std::string& path) {
	std::ifstream readFile;
	readFile.open(path);

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			std::string data;

			std::getline(readFile, data);

			if (data == "") {
				break;
			}
			
			std::string key = data.substr(0, data.find(':'));
			std::string value_S = data.substr(data.find(':') + 1);

			int value = std::stoi(value_S);

			Insert(key, value);
		}
	}
	else {
		std::cout << "Error Can't load file" << std::endl;
		std::cout << "Path : " << path << std::endl;
	}

	return this;
}

bool DataManager::GetIsLoad() {
	return loaded;
}

int DataManager::GetData(const std::string& key) {
	return datas[key];
}