#include "Building.h"

Building::Building(BuildingType type, int floors, double area, const std::string& address)
    : type(type), floors(floors), area(area), address(address) {}

std::string Building::getDescription() const {
    return "Здание: " + address + ", Этажи: " + std::to_string(floors) + 
           ", Площадь: " + std::to_string(area) + " м²";
}

int Building::getFloors() const {
    return floors;
}

double Building::getArea() const {
    return area;
}

BuildingType Building::getType() const {
    return type;
}