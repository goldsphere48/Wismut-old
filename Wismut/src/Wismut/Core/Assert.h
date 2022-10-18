#pragma once
#include <Wismut/Core/Core.h>
#include <Wismut/Core/Log.h>

#define WI_CORE_ASSERT(condition, msg) if(!(condition)) { WI_CORE_CRITICAL(msg); WI_DEBUGBREAK(); }