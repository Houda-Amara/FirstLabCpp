#include "Simulation.h"
#include <iostream>

Simulation::Simulation() : totalCost(0.0), week(0) {}

void Simulation::addSite(std::unique_ptr<ConstructionSite> site) {
    sites.push_back(std::move(site));
}

void Simulation::addMaterial(std::unique_ptr<Material> material) {
    materials.push_back(std::move(material));
}

void Simulation::setStrategy(std::unique_ptr<MaterialStrategy> strategy) {
    this->strategy = std::move(strategy);
}

std::vector<Material*> Simulation::getMaterials() {
    std::vector<Material*> materialsPtr;
    for (auto& material : materials) {
        materialsPtr.push_back(material.get());
    }
    return materialsPtr;
}

std::vector<ConstructionSite*> Simulation::getSites() {
    std::vector<ConstructionSite*> sitesPtr;
    for (auto& site : sites) {
        sitesPtr.push_back(site.get());
    }
    return sitesPtr;
}

void Simulation::simulateWeek() {
    std::cout << "\n=== Неделя " << ++week << " ===\n";
    
    for (auto& material : materials) {
        material->updatePrice();
    }
    
    if (strategy) {
        for (auto& site : sites) {
            if (site->isConstructionActive()) {
                std::cout << "Для площадки: " << site->getBuilding()->getDescription() << "\n";
                strategy->purchaseMaterials(materials, site->getRequiredMaterials(), totalCost);
            }
        }
    }
    
    for (auto& site : sites) {
        if (site->isConstructionActive()) {
            site->advanceWeek();
        }
    }
}

void Simulation::printStatus() const {
    std::cout << "\nТекущее состояние:\n";
    std::cout << "Общая стоимость: $" << totalCost << "\n";
    std::cout << "Материалы:\n";
    for (const auto& material : materials) {
        std::cout << "- " << material->getName() << ": " << material->getQuantity() 
                  << " единиц по $" << material->getPrice() << " за единицу\n";
    }
    
    std::cout << "\nСтроительные площадки:\n";
    for (const auto& site : sites) {
        std::cout << "- " << site->getBuilding()->getDescription() 
                  << ", Фаза: ";
        switch (site->getCurrentPhase()) {
            case ConstructionPhase::FOUNDATION: std::cout << "Фундамент"; break;
            case ConstructionPhase::STRUCTURE: std::cout << "Каркас"; break;
            case ConstructionPhase::ROOFING: std::cout << "Кровля"; break;
            case ConstructionPhase::FINISHING: std::cout << "Отделка"; break;
            case ConstructionPhase::COMPLETED: std::cout << "Завершено"; break;
            case ConstructionPhase::SUSPENDED: std::cout << "Приостановлено"; break;
        }
        std::cout << ", Прогресс: " << (site->getProgress() * 100) << "%"
                  << ", Активно: " << (site->isConstructionActive() ? "Да" : "Нет")
                  << "\n";
    }
}

void Simulation::printStatistics() const {
    std::cout << "\n=== Итоговая статистика ===\n";
    std::cout << "Всего недель симуляции: " << week << "\n";
    std::cout << "Всего строительных площадок: " << sites.size() << "\n";
    
    int completed = 0, active = 0, suspended = 0;
    for (const auto& site : sites) {
        if (site->getCurrentPhase() == ConstructionPhase::COMPLETED) {
            completed++;
        } else if (site->isConstructionActive()) {
            active++;
        } else {
            suspended++;
        }
    }
    
    std::cout << "- Завершено: " << completed << "\n";
    std::cout << "- Активных: " << active << "\n";
    std::cout << "- Приостановлено: " << suspended << "\n";
    
    std::cout << "Общая стоимость закупок: $" << totalCost << "\n";
    std::cout << "Остатки материалов:\n";
    for (const auto& material : materials) {
        std::cout << "- " << material->getName() << ": " << material->getQuantity() 
                  << " единиц (последняя цена: " << material->getPrice() << ")\n";
    }
}

int Simulation::getWeek() const {
    return week;
}

double Simulation::getTotalCost() const {
    return totalCost;
}