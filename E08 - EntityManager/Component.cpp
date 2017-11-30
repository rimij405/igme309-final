#include "Component.h"
using namespace Simplex;

Simplex::Component::Component(void)
{
	m_uComponentType = -1;
	m_sName = "Component";
}

Simplex::Component::Component(uint a_uComponentType, String a_sName)
{
	m_uComponentType = a_uComponentType;
	m_sName = a_sName;
}

uint Simplex::Component::GetComponentType()
{
	return m_uComponentType;
}

String Simplex::Component::GetName()
{
	return m_sName;
}
