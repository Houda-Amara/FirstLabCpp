#pragma once
#include <vector>
#include <memory>

class Material;

class MaterialStrategy {
public:
    virtual ~MaterialStrategy() = default;
    virtual void purchaseMaterials(std::vector<std::unique_ptr<Material>>& materials, 
                                 const std::vector<std::pair<Material*, int>>& requirements,
                                 double& totalCost) = 0;
};

class JustInTimeStrategy : public MaterialStrategy {
public:
    void purchaseMaterials(std::vector<std::unique_ptr<Material>>& materials, 
                         const std::vector<std::pair<Material*, int>>& requirements,
                         double& totalCost) override;
};

class WithReserveStrategy : public MaterialStrategy {
public:
    void purchaseMaterials(std::vector<std::unique_ptr<Material>>& materials, 
                         const std::vector<std::pair<Material*, int>>& requirements,
                         double& totalCost) override;
};

class LargeReserveStrategy : public MaterialStrategy {
public:
    void purchaseMaterials(std::vector<std::unique_ptr<Material>>& materials, 
                         const std::vector<std::pair<Material*, int>>& requirements,
                         double& totalCost) override;
};