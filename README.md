#Crafting & Inventory System (C++ | Engine-Agnostic)

A logic-only crafting and inventory management system written in UE-style, engine-agnostic C++, designed to demonstrate core gameplay systems such as resource tracking, crafting validation, random material gathering, and safe container mutation.

This project is intended as a portfolio piece showcasing clean gameplay logic that can be easily integrated into Unreal Engine or any custom engine.

#Features

Inventory System

Tracks materials and quantities

Prevents negative values

Automatically removes empty inventory entries

Crafting System

Multiple craftable items with material requirements

Validates inventory before crafting

Safely consumes materials on successful craft

Material Gathering

Randomized material type and quantity

Adds to inventory or stacks existing materials

Safe Container Modification

Iterator-safe removal from std::vector

No undefined behavior during inventory mutation

UE-Inspired Architecture

Clear separation of concerns

Familiar naming conventions (FStruct, EEnum, bBool)

Engine-agnostic, logic-only design

# System Overview
Core Types

EMaterial
Enum defining available crafting materials.

FMaterials
Represents a material type and quantity.

FInventory
Stores all player-owned materials.

FCraftableItem
Defines an item and its crafting requirements.

FCraftingAndInventory
Main system controller handling crafting, gathering, and inventory logic.

# Crafting Flow

Player selects an item to craft

System validates required materials

If materials are missing:

Random materials are gathered

Inventory is updated

Once requirements are met:

Materials are consumed

Inventory is cleaned

Craft succeeds

This loop continues until the item is successfully crafted.

# Technical Highlights

Uses std::mt19937 for deterministic-friendly random generation

Avoids recursion in gameplay loops

Iterator-based erase pattern to safely modify containers

Defensive checks to prevent invalid crafting states

Readable, maintainable logic suitable for extension

# Possible Extensions

Add crafted item storage (equipment or item inventory)

Introduce rarity tiers or quality modifiers

Replace console I/O with engine UI hooks

Convert materials to data-driven definitions (JSON / DataTables)

Add save/load support

# Build & Usage

This project is standard C++ and does not rely on any engine-specific libraries.

g++ InventoryAndCrafting.cpp -std=c++20 -o CraftingSystem
./CraftingSystem


Designed for logic demonstration rather than production UI.

# Portfolio Intent

This project demonstrates:

Gameplay systems thinking

Safe C++ container handling

Engine-agnostic design

Readable, scalable architecture

It is intentionally written in a style that translates cleanly into Unreal Engine gameplay code.

# Author

Kaden
Gameplay / Systems Programmer
Portfolio Project – 2026
