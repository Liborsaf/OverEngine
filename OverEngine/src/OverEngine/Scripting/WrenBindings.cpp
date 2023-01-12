#include "pcheader.h"
#include "Wren.h"

#include <wren.h>

#include "OverEngine/Input/Input.h"
#include "OverEngine/Scene/Entity.h"
#include "OverEngine/Scene/Components.h"
#include "OverEngine/Scene/TransformComponent.h"

#define WRENPP_BIND_STATIC(f, sig) .bindFunction<decltype(&f), &f>(true, sig)
#define WRENPP_BIND_STATIC_EXACT(f, args) .bindFunction<decltype(&f), &f>(true, #f "(" args ")")

#define WRENPP_BIND_GETTER(f, sig) .bindGetter<decltype(f), &f>(sig)
#define WRENPP_BIND_SETTER(f, sig) .bindSetter<decltype(f), &f>(sig)
#define WRENPP_BIND_GETSET(klass, f) WRENPP_BIND_GETTER(klass::f, #f) WRENPP_BIND_SETTER(klass::f, #f "=(_)")

namespace OverEngine
{
	namespace WrenBindings
	{
		#define WREN_INPUT(name, wrenParams, nativeCallParams)            \
			auto Input_##name(wrenParams) \
			{                                                                \
				return Input::name(nativeCallParams);                \
			}

		WREN_INPUT(IsKeyPressed, int keycode, (KeyCode)keycode)
		WREN_INPUT(IsMouseButtonPressed, int keycode, (KeyCode)keycode)
		WREN_INPUT(GetMousePosition,,)
		WREN_INPUT(GetMouseX,,)
		WREN_INPUT(GetMouseY,,)

		#define WREN_COMPONENT_HAS(component)                 \
			bool component##_has(Entity& entity)         \
			{                                            \
				return entity.HasComponent<component>(); \
			}

		WREN_COMPONENT_HAS(NameComponent)
		WREN_COMPONENT_HAS(TransformComponent)
		WREN_COMPONENT_HAS(RigidBody2DComponent)

		const String& NameComponent_name(Entity& entity)
		{
			return entity.GetComponent<NameComponent>().Name;
		}

		void NameComponent_set_name(Entity& entity, const String& name)
		{
			entity.GetComponent<NameComponent>().Name = name;
		}

		Vector3 TransformComponent_position(Entity& entity)
		{
			return entity.GetComponent<TransformComponent>().GetPosition();
		}

		void TransformComponent_set_position(Entity& entity, const Vector3& position)
		{
			entity.GetComponent<TransformComponent>().SetPosition(position);
		}

		void RigidBody2DComponent_applyLinearImpulseToCenter(Entity& entity, const Vector2& impulse)
		{
			entity.GetComponent<RigidBody2DComponent>().RigidBody->ApplyLinearImpulseToCenter(impulse);
		}
	}

	void Wren::InitializeBindings()
	{
		using namespace WrenBindings;

		m_VM.beginModule("input")
			.beginClass("Input")
				WRENPP_BIND_STATIC(Input_IsKeyPressed, "isKeyPressed(_)")
				WRENPP_BIND_STATIC(Input_IsMouseButtonPressed, "isMouseButtonPressed(_)")
				
				WRENPP_BIND_STATIC(Input_GetMousePosition, "mousePosition")
				WRENPP_BIND_STATIC(Input_GetMouseX, "mouseX")
				WRENPP_BIND_STATIC(Input_GetMouseY, "mouseY")
			.endClass()
		.endModule();

		m_VM.beginModule("entity")
			.bindClass<Entity>("Entity")
			.endClass()
		.endModule();

		m_VM.beginModule("components")
			.beginClass("ComponentInternals")
				WRENPP_BIND_STATIC_EXACT(NameComponent_name, "_")
				WRENPP_BIND_STATIC_EXACT(NameComponent_set_name, "_,_")

				WRENPP_BIND_STATIC_EXACT(TransformComponent_position, "_")
				WRENPP_BIND_STATIC_EXACT(TransformComponent_set_position, "_,_")

				WRENPP_BIND_STATIC_EXACT(RigidBody2DComponent_applyLinearImpulseToCenter, "_,_")
			.endClass()

			#define BIND_WREN_COMPONENT_HAS(component) .beginClass(#component) WRENPP_BIND_STATIC(component##_has, "has(_)").endClass()

			BIND_WREN_COMPONENT_HAS(NameComponent)
			BIND_WREN_COMPONENT_HAS(TransformComponent)
			BIND_WREN_COMPONENT_HAS(RigidBody2DComponent)

		.endModule();

		m_VM.beginModule("math")
			.bindClass<Vector3, float, float, float>("Vector3")
				WRENPP_BIND_GETSET(Vector3, x)
				WRENPP_BIND_GETSET(Vector3, y)
				WRENPP_BIND_GETSET(Vector3, z)
			.endClass()

			.bindClass<Vector2, float, float>("Vector2")
				WRENPP_BIND_GETSET(Vector2, x)
				WRENPP_BIND_GETSET(Vector2, y)
			.endClass()
		.endModule();

		LoadModule("lib");
	}
}

