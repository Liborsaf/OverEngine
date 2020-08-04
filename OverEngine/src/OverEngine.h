#pragma once

#include "pcheader.h"

// To be used in OverApps
#include "OverEngine/Core/Application.h"
#include "OverEngine/Core/Log.h"
#include "OverEngine/Core/Time/Time.h"
#include "OverEngine/Core/Math/Math.h"
#include "OverEngine/Layers/Layer.h"

#include "OverEngine/ImGui/ImGuiLayer.h"

// ------- Scenes --------------------
#include "OverEngine/Scene/Scene.h"
#include "OverEngine/Scene/Entity.h"
#include "OverEngine/Scene/Components.h"
// -----------------------------------

// ------- Renderer ------------------
#include "OverEngine/Renderer/Renderer.h"
#include "OverEngine/Renderer/Renderer2D.h"

#include "OverEngine/Renderer/VertexArray.h"
#include "OverEngine/Renderer/Buffer.h"
#include "OverEngine/Renderer/Shader.h"
#include "OverEngine/Renderer/Texture.h"
#include "OverEngine/Renderer/FrameBuffer.h"
#include "OverEngine/Renderer/TextureManager.h"
#include "OverEngine/Renderer/Camera.h"
// -----------------------------------

// ------- Physics -------------------
#include "OverEngine/Physics/PhysicsWorld2D.h"
#include "OverEngine/Physics/PhysicsBody2D.h"
#include "OverEngine/Physics/PhysicsCollider2D.h"
#include "OverEngine/Physics/PhysicsShape2D.h"
#include "OverEngine/Physics/PhysicsMaterial2D.h"
// -----------------------------------

// ------- Input ---------------------
#include "OverEngine/Input/Input.h"
#include "OverEngine/Input/InputSystem.h"
// -----------------------------------

// ------- Entry Point ---------------
#ifdef OE_CLIENT_INCLUDE_ENTRY_POINT
#include "OverEngine/Core/EntryPoint.h"
#endif
//------------------------------------