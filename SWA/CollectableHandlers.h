#pragma once
#include <cstdint>
#include "EntityManager.h"
#include "BaseSystem.h"
#include "Core.h"

void BlueFlaskUtilizeHandler(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component>* manager, Core* core);
