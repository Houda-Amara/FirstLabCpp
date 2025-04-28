#pragma once
#include "Building.h"
#include "Material.h"
#include <vector>
#include <memory>

enum class ConstructionPhase {
    FOUNDATION,
    STRUCTURE,
    ROOFING,
    FINISHING,
    COMPLETED,
    SUSPENDED
};

class ConstructionSite {
private:
    std::unique_ptr<Building> building;
    ConstructionPhase currentPhase;
    double progress;
    std::vector<std::pair<Material*, int>> requiredMaterials;
    bool isActive;

public:
    ConstructionSite(std::unique_ptr<Building> building);
    
    void startConstruction();
    void suspendConstruction();
    void resumeConstruction();
    void completeConstruction();
    
    bool advanceWeek();
    ConstructionPhase getCurrentPhase() const;
    double getProgress() const;
    Building* getBuilding() const;
    bool isConstructionActive() const;
    
    void addRequiredMaterial(Material* material, int quantity);
    const std::vector<std::pair<Material*, int>>& getRequiredMaterials() const;
};