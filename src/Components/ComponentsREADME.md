# Components Overview

## Animator.h
Handles animation state and transitions for entities.

## Attachment.h
Manages attachments or child components linked to an entity.

## Body.h
Contains the handle for Box2D physics bodies.

## Drawable.h
Contains the handle of the texture for rendering.

## Input.h
Describes the input command from the player or AI.

## Keymap.h
Defines key mappings for input handling.

## PhysicsDesciption.h
Describes the physical properties and parameters of an entity.

## SpaceQuery.h
Provides spatial queries, such as collision or area checks.

## Status.h
Tracks the status or condition (e.g., health, buffs) of an entity.

## Tags.h
Stores tags or labels for categorizing entities.

## Transform.h
Manages position, rotation, and scale of entities.

## Types.h
Defines common types and aliases used by components.

---

## Output.h (not present in directory)
Describes the output result by StateMachine to move the role, via continuous force (for move), or impulse (for jump).

## State.h (not present in directory)
Describes the state of the role, which is managed by StateMachine.