#include "Material.h"

Material::Material(const std::string& name, double basePrice, double increaseRate)
    : name(name), basePrice(basePrice), priceIncreaseRate(increaseRate), quantity(0) {}

void Material::updatePrice() {
    basePrice *= (1.0 + priceIncreaseRate);
}

double Material::getPrice() const {
    return basePrice;
}

std::string Material::getName() const {
    return name;
}

int Material::getQuantity() const {
    return quantity;
}

void Material::addQuantity(int amount) {
    quantity += amount;
}

bool Material::useQuantity(int amount) {
    if (quantity >= amount) {
        quantity -= amount;
        return true;
    }
    return false;
}