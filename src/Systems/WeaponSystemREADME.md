# WeaponSystem

## Overview

The `WeaponSystem` manages weapon firing logic in the game. It handles weapon cooldowns, ammo consumption, and firing
events, integrating with the ECS (Entity Component System) and event management.

## Key Responsibilities

- Listens for `WeaponShootEvent` and processes weapon firing.
- Manages weapon cooldown (`delayLeft`) and ammo (`ammoLeft`).
- Handles both infinite and finite ammo logic.
- Spawns ammo entities and applies impulses to both ammo and shooter.

## Main Methods

### `update()`

- Updates weapon cooldown timers for all weapons.
- Called every frame or tick.

### `onShootEvent(const WeaponShootEvent& event)`

- Handles weapon firing logic:
    - Checks cooldown and ammo.
    - Decrements ammo and resets cooldown.
    - Spawns ammo entity and applies movement impulses.

### Constructor / Destructor

- Registers and unregisters the event handler for `WeaponShootEvent`.

## Constants

- `MAGIC_INFINITY_AMMO`: Special value (`-130724`) indicating infinite ammo.

## Dependencies

- Components: `TypeWeapon`, `StatusWeapon`, `Weapon`, `Transform`
- Events: `WeaponShootEvent`, `MoverEvent`
- Managers: `EventManager`
- Core: `World`
