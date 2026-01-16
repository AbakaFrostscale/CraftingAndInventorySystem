//InventoryAndCrafting.cpp
//Logic-only crafting and inventory management system
//Author: Kaden
//Descritpion: Portfolio project demonstrating gameplay systems logic
//version: 1.00

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <array>

enum class EMaterial {EMWood, EMStone, EMIron, EMCloth, EMLeather};

struct FMaterials 
{
	EMaterial Material;
	int MaterialAmount;
};

struct FInventory
{	
	std::vector<FMaterials> Materials;		
};

struct FCraftableItem
{
	std::string ItemName;
	std::vector<FMaterials> CraftingRequirements;
};

class FCraftingAndInventory
{
public:
	FCraftingAndInventory();
	void CraftItem();
private:
	void GatherMaterials();
	bool HasMaterials(const FCraftableItem& Item);
	void RemoveMaterials(const FCraftableItem& Item);
	void PrintInventory() const;
	std::string EMaterialToString(EMaterial Material);
private: 
	FCraftableItem Sword;
	FCraftableItem Shield;
	FCraftableItem Shirt;
	FCraftableItem Boots;
	FCraftableItem Pants;
	FCraftableItem Armour;

	FInventory Inventory;

	std::array<EMaterial, 5> GatheredItem = {EMaterial::EMWood, EMaterial::EMStone, EMaterial::EMIron, EMaterial::EMCloth, EMaterial::EMLeather};
	std::vector<FCraftableItem> CraftableItems;

	std::mt19937 RandomGenerator;
};

FCraftingAndInventory::FCraftingAndInventory()
{
	std::random_device rd;
	RandomGenerator = std::mt19937(rd());
	
	Sword = {"Iron Sword", {{EMaterial::EMIron, 2}, {EMaterial::EMWood, 1}}};
	CraftableItems.push_back(Sword);

	Shield = {"Wooden Shield", {{EMaterial::EMIron, 1}, {EMaterial::EMWood, 2}}};
	CraftableItems.push_back(Shield);

	Shirt = {"Cloth Shirt", {{EMaterial::EMCloth, 3}}};
	CraftableItems.push_back(Shirt);

	Pants = {"Leather Pants", {{EMaterial::EMCloth, 1}, {EMaterial::EMLeather, 3}}};
	CraftableItems.push_back(Pants);

	Boots = {"Leather Boots", {{EMaterial::EMIron, 1}, {EMaterial::EMLeather, 1}}};
	CraftableItems.push_back(Boots);

	Armour = {"Iron Armour", {{EMaterial::EMIron, 5}, {EMaterial::EMLeather, 3}, {EMaterial::EMCloth, 2}}};
	CraftableItems.push_back(Armour);

}

void FCraftingAndInventory::CraftItem()
{	
	std::string ItemToBeCrafted;
	std::cout << "What would you like to craft: ";
	std::getline(std::cin, ItemToBeCrafted);
	bool bIsCrafted = false;
 
	FCraftableItem* ItemToCraft = nullptr;	

	for(FCraftableItem& Item : CraftableItems)
	{ 
		if (ItemToBeCrafted == Item.ItemName) 
		{ 
			ItemToCraft = &Item;
			break;
		}
	}

	if (!ItemToCraft)
	{
		std::cout << "That item does not exist! pick another" << std::endl;
		return;
	}
	
	while (!bIsCrafted)
	{
		if (HasMaterials(*ItemToCraft))
			{
				RemoveMaterials(*ItemToCraft);
				std::cout << ItemToCraft->ItemName << " has been successfully crafted!" << std::endl;
				bIsCrafted = true;
				PrintInventory();
			}
		else
			{
				std::cout << "You do not have the required materials,gathering process has started!" << std::endl;
				bIsCrafted = false;
				GatherMaterials();
			}
	}
}

bool FCraftingAndInventory::HasMaterials(const FCraftableItem& Item)
{	
	for (const FMaterials& CraftMaterial : Item.CraftingRequirements)
	{
		bool MatchFound = false;
		for (const FMaterials& InventoryMaterial : Inventory.Materials)
		{
			if (InventoryMaterial.Material == CraftMaterial.Material && InventoryMaterial.MaterialAmount >= CraftMaterial.MaterialAmount)
			{
				MatchFound = true;
				break;
			}
			
		}
		if (!MatchFound)
		{
			return false;
		}
	}
	return true;
}

void FCraftingAndInventory::RemoveMaterials(const FCraftableItem& Item)
{
	if(!HasMaterials(Item)) {return;}	

	for (const FMaterials& CraftMaterial : Item.CraftingRequirements)
	{
		for (auto It = Inventory.Materials.begin(); It != Inventory.Materials.end(); )
		{
			if (CraftMaterial.Material == It->Material)
			{
				It->MaterialAmount -= CraftMaterial.MaterialAmount;
				if (It->MaterialAmount <= 0)
				{
					It = Inventory.Materials.erase(It);
				}
				else
				{
					++It;
				}
				break;		
			}
			else
			{
				++It;
			}
		}
	}

	
}

void FCraftingAndInventory::GatherMaterials()
{
	bool bFound = false;	

	std::uniform_int_distribution<int> amountDist(1, 5);	
	int RandomAmount = amountDist(RandomGenerator);
	
	std::uniform_int_distribution<size_t> materialDist(0, GatheredItem.size() -1);
	int RandomMaterial = materialDist(RandomGenerator);

	for (FMaterials& InventoryMaterial : Inventory.Materials)
	{
		if (GatheredItem[RandomMaterial] == InventoryMaterial.Material)
		{
			InventoryMaterial.MaterialAmount += RandomAmount;
			bFound = true;
			break;
		} 
	}

	if (!bFound)
	{
		Inventory.Materials.push_back({GatheredItem[RandomMaterial], RandomAmount});
	}

	std::cout << RandomAmount << " " << EMaterialToString(GatheredItem[RandomMaterial]) << " was gathered!" << std::endl;
}

std::string FCraftingAndInventory::EMaterialToString(EMaterial Material)
{
	switch(Material)
	{
		case EMaterial::EMWood: return "Wood";
		case EMaterial::EMStone: return "Stone";
		case EMaterial::EMIron: return "Iron";
		case EMaterial::EMCloth: return "Cloth";
		case EMaterial::EMLeather: return "Leather";
		default: return "No material found";
	}
} 

void FCraftingAndInventory::PrintInventory() const
{
	for (const FMaterials& InventoryMaterial : Inventory.Materials)
	{
		std::cout << InventoryMaterial.MaterialAmount << " " << EMaterialToString(InventoryMaterial.Material) << " left in the inventory!" << std::endl;
	}
}