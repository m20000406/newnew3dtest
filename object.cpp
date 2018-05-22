#include "object.h"
#include <tuple>
#include "obj_line.h"
#include "obj_axis.h"

std::shared_ptr<IObject> objFactory(std::string objname) {
	if (objname.compare("obj_line") == 0) {
		std::shared_ptr<IObject> p(new obj_line());
		return p;
	}
	else if (objname == "obj_axis") {
		std::shared_ptr<IObject> p(new obj_axis());
		return p;
	}
}
