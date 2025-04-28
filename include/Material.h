#pragma once
#include <string>

class Material {
protected:
    std::string name;
    double basePrice;
    double priceIncreaseRate;
    int quantity;

public:
    Material(const std::string& name, double basePrice, double increaseRate);
    virtual ~Material() = default;
    
    virtual void updatePrice();
    double getPrice() const;
    std::string getName() const;
    int getQuantity() const;
    void addQuantity(int amount);
    bool useQuantity(int amount);
};