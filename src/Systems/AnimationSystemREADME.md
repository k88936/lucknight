## AnimationSystem

**Purpose:**  
Manages entity animations, updates animation frames, and handles animation state changes in an ECS (Entity Component System) architecture.

### Public Methods

- **AnimationSystem()**  
  Constructor. Connects the system to `AnimationChangeEvent` events.

- **~AnimationSystem()**  
  Destructor. Disconnects from `AnimationChangeEvent` events.

- **void update() override**  
  Updates all entities with `Animator` and `Drawable` components:
    - Advances animation frames based on elapsed time.
    - Updates the drawable texture to the current animation frame.

- **template <typename State> void registerAnimation(...)**  
  Registers an animation for a given entity and state. Loads textures from a directory and associates them with a state.

- **template <typename State> void play(...)**  
  Triggers an animation state change for an entity by enqueuing an `AnimationChangeEvent`.

- **void onChange(const AnimationChangeEvent& event)**  
  Handles animation state changes, updating the current animation and resetting frame counters.

### Private Methods

- **void registerAnimation_aux(...)**  
  Helper for registering animations, loads textures, and sets up animation clips.

- **void updateAnimation(...)**  
  Advances the animation frame based on elapsed time and handles looping or stopping at the end.

- **void updateDrawableTexture(...)**  
  Updates the `Drawable` component's texture to match the current animation frame.