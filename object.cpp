#include "object.h"
#include "obj_axis.h"
#include "obj_plate.h"

std::shared_ptr<IObject> objFactory(std::string objname) {
	if (objname == "obj_axis") {
		std::shared_ptr<IObject> p(new obj_axis());
		return p;
	}else if(objname == "obj_plate"){
		std::shared_ptr<IObject> p(new obj_plate());
		return p;
	}
}