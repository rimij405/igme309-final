#include "Definitions.h"
#include "Component.h"
#include "GameObject.h"
using namespace Simplex;

void GameObject::Release(void)
{
}

GameObject::GameObject(void)
{
	// assume disabled
	 //GameObject::Init("", false);
}

GameObject::GameObject(String a_sName)
{
	// assign name and assume disabled
	 //GameObject::Init(a_sName, false);
}

void  GameObject::Init(String a_sName, bool a_bEnabled)
{
	// m_sName = a_sName;
	// m_bEnabled = a_bEnabled;
}

 GameObject::~GameObject(void)
{
}

 GameObject::GameObject(GameObject const & input)
{
	// this->m_cComponents = input.m_cComponents;
	
}

GameObject &  GameObject::operator=(GameObject const & input)
{
	return *this;
}

void  GameObject::Update(float a_fDelta)
{
}

bool  GameObject::HasComponent(uint a_uComponentType)
{
	// uint uNumComponents = m_cComponents.size();
	// for (uint i = 0; i < uNumComponents; i++)
	// {
	//	if (m_cComponents[i]->GetComponentType() == a_uComponentType)
	//		return true;
	// }

	return false;
}

bool  GameObject::IsEmpty(void)
{
	return false;
	// return (m_cComponents.size() > 0)? false : true;
}

bool  GameObject::IsEnabled(void)
{
	return m_bEnabled;
}

bool  GameObject::AddComponent(uint a_uComponentType, Component& a_cComponent)
{
	// if (this->HasComponent(a_uComponentType))
	// 	return false;
	
	// m_cComponents.push_back(&a_cComponent);
	return true;
}

/*
Component&  GameObject::AddComponent(Component& a_cComponent)
{
	/* uint type = a_cComponent.GetComponentType();
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
	return *GetComponent(type);*/
//	return ;
// }*/

Component*  GameObject::GetComponent(uint a_uComponentType)
{
	/* uint uNumComponents = m_cComponents.size();
	for (uint i = 0; i < uNumComponents; i++)
	{
		if (m_cComponents[i]->GetComponentType() == a_uComponentType)
			return m_cComponents[i];
	}*/

	return nullptr;
}

String  GameObject::GetName(void)
{
	return m_sName;
}

String  GameObject::toString(void)
{
	
	// uint uNumComponents = m_cComponents.size();
	// String sOutput = "The Object \"" + m_sName + "\" has " + std::to_string(uNumComponents) + " components\n";
	// for (uint i = 0; i < uNumComponents; i++)
	// {
	// 	sOutput += "Type: " + std::to_string(m_cComponents[i]->GetComponentType()) + ", Name: " + m_cComponents[i]->GetName();
	// }
	// sOutput += "\n";
	return String();// sOutput;
}
