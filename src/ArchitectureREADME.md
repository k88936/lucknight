# Architecture Overview

## World
World is a container for the EnTT registry, managing all entities and their components.

## Scene
Scene is the Qt frontend, providing input and rendering functions.

## Components
Defines the data for entities, such as Transform, Status, Attachment, Physics, Input, etc. Each component represents a specific aspect of an entity.

## Systems
Contain the logic for updating and managing entities. Examples include AnimationSystem, PhysicsSystem, TreasureSystem, WeaponSystem, BuffSystem, etc. Systems operate on entities with relevant components.

## Managers
Handle global resources and events, such as EventManager (for event dispatching) and TextureManager (for texture resources).

## Prefab
Provides reusable blueprints for entities, such as PrefabPlayer, PrefabTreasure, PrefabWeapon, etc. Prefabs simplify entity creation with predefined components and settings.

## Scripts
Contains game logic scripts, such as buffs or custom behaviors, to extend or modify entity behavior.

## Type & Utils
Type contains type definitions and aliases. Utils provides utility functions and helpers used throughout the codebase.

