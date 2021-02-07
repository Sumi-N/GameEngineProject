#pragma once

#include "SceneEntity.h"

std::vector<OwningPointer<SceneProxy>> SceneEntity::List;
OwningPointer<SceneProxy> SceneEntity::SkyBoxProxy;