# Scripts Module Overview

## IndicatorScript.h / IndicatorScript.cpp
Defines and implements logic for indicator objects, such as UI markers or in-game pointers.

## PlayerScript.h / PlayerScript.cpp
Handles player-specific scripting, including input processing and player behavior.

## ProjectileScript.h / ProjectileScript.cpp
Implements scripting for projectile objects, managing their behavior and interactions.

## Script.h
Base class or interface for all scriptable behaviors in the game.

---

## Buff/

### BuffBase.h
Defines the base class for buffs, encapsulating common buff logic.

### Buffs.h
Declares and manages various buff types applied to entities.

### ExpiredMixin.h
Provides mixin functionality for handling buff expiration.

### TimingExpiredMixin.h
Implements timing-based expiration logic for buffs.

---

## StateMachine/

### StateMachine.h
Defines the state machine logic for managing entity states and transitions.