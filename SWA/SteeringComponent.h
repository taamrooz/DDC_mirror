#pragma once
#include "Component.h"
struct SteeringComponent : Component
{
	// rectangle_drawable drawable_;
	float m_dWanderRadius = 25;
	//This is the radius of the constraining circle.
	float m_dWanderDistance = 5.f;
	//This is the distance the wander circle is projected in front of the agent.
	float m_dWanderJitter = 28.f;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["SteeringComponent"]["m_dWanderRadius"] = m_dWanderRadius;
		j[std::to_string(id)]["SteeringComponent"]["m_dWanderDistance"] = m_dWanderDistance;
		j[std::to_string(id)]["SteeringComponent"]["m_dWanderJitter"] = m_dWanderJitter;
	}
};