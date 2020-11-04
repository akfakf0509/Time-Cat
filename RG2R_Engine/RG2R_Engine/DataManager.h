#pragma once
#include "Component.h"

#include <map>
#include <string>
#include <fstream>

class DataManager :
	public Component
{
private:
	std::map<std::string, int> datas;

	bool loaded;
public:
	DataManager();
	~DataManager();

	void Update() {};
	void Render() {};
	void Render(ViewRenderData&) {};

	std::type_index GetID(void) { return typeid(DataManager); }
	static std::type_index GetFamilyID(void) { return typeid(DataManager); }

	DataManager* Insert(const std::string&, int);
	DataManager* Save(const std::string&);
	DataManager* Load(const std::string&);

	bool GetIsLoad();
	int GetData(const std::string&);
};

