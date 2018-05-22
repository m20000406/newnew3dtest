#include "color.h"
color::color(unsigned char rr, unsigned char gg, unsigned char bb) :r(rr), g(gg), b(bb) { }

color::color():r(0),g(0),b(0){}

bool operator==(color a, color b) {
	return (a.r == b.r && a.g == b.g && a.g == b.g);
}

bool operator!=(color a, color b) {
	return !(a == b);
}