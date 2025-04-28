#include "MaterialStrategy.h"
#include "Material.h"
#include <iostream>

void JustInTimeStrategy::purchaseMaterials(std::vector<std::unique_ptr<Material>>& materials, 
                                         const std::vector<std::pair<Material*, int>>& requirements,
                                         double& totalCost) {
    std::cout << "\nИспользуется стратегия закупки 'Точно в срок'\n";
    for (const auto& req : requirements) {
        for (auto& mat : materials) {
            if (mat->getName() == req.first->getName()) {
                int needed = req.second - mat->getQuantity();
                if (needed > 0) {
                    double cost = needed * mat->getPrice();
                    mat->addQuantity(needed);
                    totalCost += cost;
                    std::cout << "  Закуплено " << needed << " единиц " << mat->getName() 
                              << " по цене " << mat->getPrice() << " за единицу"
                              << " (Общая стоимость: " << cost << ")\n";
                }
                break;
            }
        }
    }
}

void WithReserveStrategy::purchaseMaterials(std::vector<std::unique_ptr<Material>>& materials, 
                                         const std::vector<std::pair<Material*, int>>& requirements,
                                         double& totalCost) {
    std::cout << "\nИспользуется стратегия закупки 'С запасом'\n";
    for (const auto& req : requirements) {
        for (auto& mat : materials) {
            if (mat->getName() == req.first->getName()) {
                int needed = static_cast<int>(req.second * 1.2) - mat->getQuantity();
                if (needed > 0) {
                    double cost = needed * mat->getPrice();
                    mat->addQuantity(needed);
                    totalCost += cost;
                    std::cout << "  Закуплено " << needed << " единиц " << mat->getName() 
                              << " по цене " << mat->getPrice() << " за единицу"
                              << " (Общая стоимость: " << cost << ")\n";
                }
                break;
            }
        }
    }
}

void LargeReserveStrategy::purchaseMaterials(std::vector<std::unique_ptr<Material>>& materials, 
                                         const std::vector<std::pair<Material*, int>>& requirements,
                                         double& totalCost) {
    std::cout << "\nИспользуется стратегия закупки 'С большим запасом'\n";
    for (const auto& req : requirements) {
        for (auto& mat : materials) {
            if (mat->getName() == req.first->getName()) {
                int needed = static_cast<int>(req.second * 1.5) - mat->getQuantity();
                if (needed > 0) {
                    double cost = needed * mat->getPrice();
                    mat->addQuantity(needed);
                    totalCost += cost;
                    std::cout << "  Закуплено " << needed << " единиц " << mat->getName() 
                              << " по цене " << mat->getPrice() << " за единицу"
                              << " (Общая стоимость: " << cost << ")\n";
                }
                break;
            }
        }
    }
}