#include "object.h"
#include "obj_axis.h"

std::shared_ptr<IObject> objFactory(std::string objname) {
	if (objname == "obj_axis") {
		std::shared_ptr<IObject> p(new obj_axis());
		return p;
	}
}
