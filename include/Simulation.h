#pragma once
#include "ConstructionSite.h"
#include "MaterialStrategy.h"
#include <vector>
#include <memory>

class Simulation {
private:
    std::vector<std::unique_ptr<ConstructionSite>> sites;
    std::vector<std::unique_ptr<Material>> materials;
    std::unique_ptr<MaterialStrategy> strategy;
    double totalCost;
    int week;

public:
    Simulation();
    
    void addSite(std::unique_ptr<ConstructionSite> site);
    void addMaterial(std::unique_ptr<Material> material);
    void setStrategy(std::unique_ptr<MaterialStrategy> strategy);
    
    std::vector<Material*> getMaterials();
    std::vector<ConstructionSite*> getSites();
    
    void simulateWeek();
    void printStatus() const;
    void printStatistics() const;
    
    int getWeek() const;
    double getTotalCost() const;
};