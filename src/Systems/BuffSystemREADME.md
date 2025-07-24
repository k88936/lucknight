
## Buff System Overview

The Buff System manages temporary effects ("buffs") applied to entities in the game. It uses the ECS (Entity Component System) pattern with the `entt` library.

### Key Components

- **BuffBase**: Abstract base class for all buffs. Defines lifecycle methods (`onEnter`, `onUpdate`, `onExit`) and expiration logic.
- **BUFF Macro**: Simplifies buff class creation and registration.
- **BuffSystem**: Handles buff registration, updates, and event-driven addition/removal of buffs.
- **BuffEvents**: Defines events for adding and removing buffs (`AddBuff`, `RemoveBuff`).

### Workflow

1. **Buff Registration**: Buffs are registered via the `BUFF` macro and `BuffSystem::registerBuff`.
2. **Buff Application**: When an `AddBuff` event is received, the buff is constructed and attached to the entity.
3. **Buff Update**: Each frame, buffs are updated. If expired, a `RemoveBuff` event is triggered.
4. **Buff Removal**: On `RemoveBuff`, the buff is cleaned up and removed from the entity.

### Example

```cpp
BUFF(BuffCrouching, (Body))
{
    void onEnter() override { /* Apply crouch effect */ }
    void onExit() override { /* Remove crouch effect */ }
};
```

---

**Files:**
- `src/Scripts/Buff/BuffBase.h`: Buff base class and macro.
- `src/Scripts/Buff/Buffs.h`: Buff implementations.
- `src/Systems/BuffSystem.h` / `.cpp`: Buff system logic.
- `src/Events/BuffEvents.h`: Buff event definitions.

---

**Usage:**  
Define buffs with the macro, register them, and use events to add/remove buffs on entities. The system handles updates and expiration automatically.