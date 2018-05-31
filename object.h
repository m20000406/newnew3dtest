#pragma once
#include <string>
#include <memory>
#include <tuple>
#include <map>
#include <vector>

typedef std::map<std::string,std::string> Attr;

class IObject {
public:
	virtual void draw() = 0;
	virtual ~IObject() {};
	virtual void addInf(std::string, std::string, Attr = Attr() ) = 0;
	std::vector<std::string> tags;
};

std::shared_ptr<IObject> objFactory(std::string);