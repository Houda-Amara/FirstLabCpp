#pragma once
#include <string>
#include <vector>
#include <memory>

enum class BuildingType {
    RESIDENTIAL,
    COMMERCIAL,
    INDUSTRIAL
};

class Building {
protected:
    BuildingType type;
    int floors;
    double area;
    std::string address;

public:
    Building(BuildingType type, int floors, double area, const std::string& address);
    virtual ~Building() = default;
    
    virtual double calculateTotalCost() const = 0;
    virtual std::string getDescription() const;
    
    int getFloors() const;
    double getArea() const;
    BuildingType getType() const;
};