#include "Definitions.h"
#include "Component.h"
#include "GameObject.h"
using namespace Simplex;

void Simplex::GameObject::Release(void)
{
}

Simplex::GameObject::GameObject(void)
{
	// assume disabled
	Simplex::GameObject::Init("", false);
}

Simplex::GameObject::GameObject(String a_sName)
{
	// assign name and assume disabled
	Simplex::GameObject::Init(a_sName, false);
}

void Simplex::GameObject::Init(String a_sName, bool a_bEnabled)
{
	m_sName = a_sName;
	m_bEnabled = a_bEnabled;
}

Simplex::GameObject::~GameObject(void)
{
}

Simplex::GameObject::GameObject(GameObject const & input)
{
	this->m_cComponents = input.m_cComponents;
	//this->
}

GameObject & Simplex::GameObject::operator=(GameObject const & input)
{
	return *this;
}

void Simplex::GameObject::Update(float a_fDelta)
{
}

bool Simplex::GameObject::HasComponent(uint a_uComponentType)
{
	uint uNumComponents = m_cComponents.size();
	for (uint i = 0; i < uNumComponents; i++)
	{
		if (m_cComponents[i]->GetComponentType() == a_uComponentType)
			return true;
	}

	return false;
}

bool Simplex::GameObject::IsEmpty(void)
{
	return (m_cComponents.size() > 0)? false : true;
}

bool Simplex::GameObject::IsEnabled(void)
{
	return m_bEnabled;
}

bool Simplex::GameObject::AddComponent(uint a_uComponentType, Component& a_cComponent)
{
	if (this->HasComponent(a_uComponentType))
		return false;
	
	m_cComponents.push_back(&a_cComponent);
	return true;
}

Component& Simplex::GameObject::AddComponent(Component& a_cComponent)
{
	uint type = a_cComponent.GetComponentType();
	if (type != -1)
	{
		std::cout << "Type isn't -1!\n";

		if (!this->HasComponent(type))
		{
			std::cout << "Adding!\n";
			m_cComponents.push_back(&a_cComponent);
			return a_cComponent;
		}
	}

	std::cout << "Already present!\n";
	return *GetComponent(type);
}

Component* Simplex::GameObject::GetComponent(uint a_uComponentType)
{
	uint uNumComponents = m_cComponents.size();
	for (uint i = 0; i < uNumComponents; i++)
	{
		if (m_cComponents[i]->GetComponentType() == a_uComponentType)
			return m_cComponents[i];
	}

	return nullptr;
}

String Simplex::GameObject::GetName(void)
{
	return m_sName;
}

String Simplex::GameObject::toString(void)
{
	
	uint uNumComponents = m_cComponents.size();
	String sOutput = "The Object \"" + m_sName + "\" has " + std::to_string(uNumComponents) + " components\n";
	for (uint i = 0; i < uNumComponents; i++)
	{
		sOutput += "Type: " + std::to_string(m_cComponents[i]->GetComponentType()) + ", Name: " + m_cComponents[i]->GetName();
	}
	sOutput += "\n";
	return sOutput;
}
