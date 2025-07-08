//
// Created by kvtoD on 7/1/2025.
//

#ifndef DUMPER_H
#define DUMPER_H
#include <sstream>

#include "../Core/World.h"


inline std::ostream &operator <<(std::ostream &os, const entt::entity &entity) {
    return os << static_cast<std::uintptr_t>(entity);
}

template<typename T>
inline void dump() {
    World::getInstance().registry.view<const T>().each([](const auto entity, const auto &component) {
        std::cout << entity << " " << component << std::endl;
    });
}

inline void dump(entt::entity entity) {
    auto &registry = World::getInstance().registry;
    // Iterate through all storage types in the registry
    for (auto [id, storage] : registry.storage()) {
        if (storage.contains(entity)) {
            // This is tricky because we don't know the component type at compile time
            // You'd need to maintain a type registry or use reflection
            std::cout << entity << " [Component type: " << id << "]" << std::endl;
        }
    }
}

#endif //DUMPER_H