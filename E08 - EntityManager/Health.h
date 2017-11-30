/*---------------------------------
Programmer: Ian Effendi (iae2784@g.rit.edu)
Team: The SQL
Date: 11/29/2017
-----------------------------------*/

#ifndef __HEALTH_H_
#define __HEALTH_H_

#include "Definitions.h"

// Add the health class to the Simplex namespace.
namespace Simplex {
	
	// A health class contains functionality and data for keeping track of an entity's health.
	class Health {

	private:

#pragma region //	Private Fields

		// Health associated with this component. (Must be an int and not a uint, because we'll be subtracting value).
		int m_uHealth = 0;

		// The maximum health this component can have. (Must be positive).
		uint m_uMaxHealth = 100;
		
		// Minimum health this component can have.
		uint m_uMinHealth = 0;

#pragma endregion

#pragma region //	Helper Methods

		/*
		USAGE: Clamps the health value between the minimum and maximum health values.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void ValidateHealth(void);
		
		/*
		USAGE: Sets the health field to the input value and then calls the validate health method.
		ARGUMENTS: int value -> The value to set the health to.
		OUTPUT: ---
		*/
		void SetHealth(int value);

#pragma endregion

	public:

#pragma region //	Constructor / Init / Destructor

		/*
		USAGE: Default Constructor.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		Health(void);

		/*
		USAGE: Parameterized constructor. Set the maximum and minimum health values.
		ARGUMENTS:
		-	uint m_uMaxHealth -> Maximum health in the health component. 
		-	uint m_uMinHealth -> Minimum health in the health component.
		OUTPUT: ---
		*/
		Health(uint a_uMaxHealth, uint a_uMinHealth);
		
		/*
		USAGE: Set the maximum, minimum, and current health values.
		ARGUMENTS:
		-	int a_iCurrentHealth -> Current health of the component.
		-	uint m_uMaxHealth -> Maximum health in the health component.
		-	uint m_uMinHealth -> Minimum health in the health component.
		OUTPUT: ---
		*/
		void Init(int a_iCurrentHealth, uint a_uMaxHealth, uint a_uMinHealth);

		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~Health(void);

#pragma endregion

#pragma region //	The Rule of Three
		
		/*
		USAGE: Copy consntructor for the Health component.
		ARGUMENTS: Health const& other -> Object to copy.
		OUTPUT: ---
		*/
		Health(Health const& other);

		/*
		USAGE: Copy assignment for the Health component.
		ARGUMENTS: Health const& other -> Object to copy.
		OUTPUT: ---
		*/
		Health& operator=(Health const& other);
		
#pragma endregion

	};
}


#endif // __HEALTH_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/