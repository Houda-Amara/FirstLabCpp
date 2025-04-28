#include <iostream>
#include "../include/Simulation.h"
#include "../include/Building.h"
#include "../include/Material.h"
#include "../include/MaterialStrategy.h"
#include <windows.h>

class ResidentialBuilding : public Building {
public:
    ResidentialBuilding(int floors, double area, const std::string& address)
        : Building(BuildingType::RESIDENTIAL, floors, area, address) {}
    
    double calculateTotalCost() const override {
        return getArea() * getFloors() * 500;
    }
    
    std::string getDescription() const override {
        return "Жилой дом (" + std::to_string(getFloors()) + " этажей) по адресу " + address;
    }
};

class CommercialBuilding : public Building {
public:
    CommercialBuilding(int floors, double area, const std::string& address)
        : Building(BuildingType::COMMERCIAL, floors, area, address) {}
    
    double calculateTotalCost() const override {
        return getArea() * getFloors() * 700;
    }
    
    std::string getDescription() const override {
        return "Коммерческое здание (" + std::to_string(getFloors()) + " этажей) по адресу " + address;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Simulation simulation;
    
    // Create materials
    simulation.addMaterial(std::make_unique<Material>("Бетон", 50.0, 0.01));
    simulation.addMaterial(std::make_unique<Material>("Сталь", 100.0, 0.02));
    simulation.addMaterial(std::make_unique<Material>("Кирпичи", 30.0, 0.005));
    simulation.addMaterial(std::make_unique<Material>("Стекло", 80.0, 0.015));
    simulation.addMaterial(std::make_unique<Material>("Дерево", 60.0, 0.01));
    
    // Create construction sites
    auto site1 = std::make_unique<ConstructionSite>(
        std::make_unique<ResidentialBuilding>(5, 2000, "ул. Главная, 123"));    
    auto site2 = std::make_unique<ConstructionSite>(
        std::make_unique<CommercialBuilding>(10, 5000, "Бизнес авеню, 456"));

    // Add required materials for sites
        auto materials = simulation.getMaterials();
        for (auto* mat : materials) {
            if (mat->getName() == "Бетон") {
                site1->addRequiredMaterial(mat, 1000);
                site2->addRequiredMaterial(mat, 3000);
            } else if (mat->getName() == "Сталь") {
                site1->addRequiredMaterial(mat, 500);
                site2->addRequiredMaterial(mat, 1500);
            } else if (mat->getName() == "Кирпичи") {
                site1->addRequiredMaterial(mat, 2000);
            }
        }
    
    simulation.addSite(std::move(site1));
    simulation.addSite(std::move(site2));
    
    // Start construction on first site
    simulation.getSites()[0]->startConstruction();
    
    // Set purchasing strategy
    simulation.setStrategy(std::make_unique<WithReserveStrategy>());
    
    // Run simulation for 20 weeks
    for (int i = 0; i < 20; ++i) {
        simulation.simulateWeek();
        simulation.printStatus();
        
        // Pause construction on site 1 after week 5
        if (i == 5) {
            simulation.getSites()[0]->suspendConstruction();
        }
        
        // Resume construction on site 1 and start site 2 after week 10
        if (i == 10) {
            simulation.getSites()[0]->resumeConstruction();
            simulation.getSites()[1]->startConstruction();
        }
    }
    
    simulation.printStatistics();
    
    return 0;
}