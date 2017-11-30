/*---------------------------------
Programmer: Ian Effendi (iae2784@g.rit.edu)
Team: The SQL
Date: 11/29/2017
-----------------------------------*/

#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "Definitions.h"

// Add the component class to the simplex namespace.
namespace Simplex {

	class Component {
	protected:
		// Component type assigned on construction of the component.
		// Every object can only have one type of a component.
		uint m_uComponentType = 0;

		// Name given to the component.
		String m_sName = "Component";

		// 

	public:

#pragma region //	Constructor / Init / Destructor

		Component(void);

#pragma endregion

	};


}

#endif // __COMPONENT_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/