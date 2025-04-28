#include "ConstructionSite.h"
#include <iostream>

ConstructionSite::ConstructionSite(std::unique_ptr<Building> building)
    : building(std::move(building)), currentPhase(ConstructionPhase::FOUNDATION), 
      progress(0.0), isActive(false) {}

void ConstructionSite::startConstruction() {
    isActive = true;
    std::cout << "Строительство начато для " << building->getDescription() << std::endl;
}

void ConstructionSite::suspendConstruction() {
    isActive = false;
    std::cout << "Строительство приостановлено для " << building->getDescription() << std::endl;
}

void ConstructionSite::resumeConstruction() {
    isActive = true;
    std::cout << "Строительство возобновлено для " << building->getDescription() << std::endl;
}

void ConstructionSite::completeConstruction() {
    currentPhase = ConstructionPhase::COMPLETED;
    isActive = false;
    progress = 1.0;
    std::cout << "Строительство завершено для " << building->getDescription() << std::endl;
}

bool ConstructionSite::advanceWeek() {
    if (!isActive || currentPhase == ConstructionPhase::COMPLETED) {
        return false;
    }

    // Расход материалов (5% от требуемого количества в неделю)
    for (auto& [material, quantity] : requiredMaterials) {
        int toUse = static_cast<int>(quantity * 0.05);
        if (!material->useQuantity(toUse)) {
            std::cout << "Недостаточно материалов " << material->getName() 
                      << " для продолжения строительства!\n";
            suspendConstruction();
            return false;
        }
    }

    progress += 0.05; // 5% прогресса в неделю
    
    if (progress >= 1.0) {
        switch (currentPhase) {
            case ConstructionPhase::FOUNDATION:
                currentPhase = ConstructionPhase::STRUCTURE;
                progress = 0.0;
                std::cout << "Фундамент завершен для " << building->getDescription() << std::endl;
                break;
            case ConstructionPhase::STRUCTURE:
                currentPhase = ConstructionPhase::ROOFING;
                progress = 0.0;
                std::cout << "Каркас здания завершен для " << building->getDescription() << std::endl;
                break;
            case ConstructionPhase::ROOFING:
                currentPhase = ConstructionPhase::FINISHING;
                progress = 0.0;
                std::cout << "Кровля завершена для " << building->getDescription() << std::endl;
                break;
            case ConstructionPhase::FINISHING:
                completeConstruction();
                return true;
            default:
                break;
        }
    }
    return false;
}

ConstructionPhase ConstructionSite::getCurrentPhase() const {
    return currentPhase;
}

double ConstructionSite::getProgress() const {
    return progress;
}

Building* ConstructionSite::getBuilding() const {
    return building.get();
}

bool ConstructionSite::isConstructionActive() const {
    return isActive;
}

void ConstructionSite::addRequiredMaterial(Material* material, int quantity) {
    requiredMaterials.emplace_back(material, quantity);
}

const std::vector<std::pair<Material*, int>>& ConstructionSite::getRequiredMaterials() const {
    return requiredMaterials;
}