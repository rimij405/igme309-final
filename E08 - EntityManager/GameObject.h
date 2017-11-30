/*---------------------------------
Programmer: Ian Effendi (iae2784@g.rit.edu)
Team: The SQL
Date: 11/29/2017
-----------------------------------*/

#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include "Definitions.h"
#include "Component.h"

// Add the gameobject to the simplex namespace.
namespace Simplex 
{

	// The game object stores a collection of components and updates all of them.
	class GameObject {
	private:

#pragma region //	Private Fields

		// Name of the game object.
		String m_sName = "Empty Game Object";

		// Collection of components.
		std::vector<Component*> m_cComponents;

		// Flag determining if this game object is currently enabled.
		bool m_bEnabled = false;
		
#pragma endregion

#pragma region //	Helper Methods

		/*
		Usage: Deallocates member fields
		Arguments: ---
		Output: ---
		*/
		void Release(void);

#pragma endregion

	public:
		
#pragma region //	Constructor / Init / Destructor

		/*
		USAGE: Default constructor.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		GameObject(void);

		/*
		USAGE: Constructor that takes a name for the game object.
		ARGUMENTS: a_sName -> Name of the GameObject.
		OUTPUT: ---
		*/
		GameObject(String a_sName = "Untitled Game Object");
		
		/*
		USAGE: Public access initialization method.
		ARGUMENTS:
		-	a_sName -> Name of the GameObject.
		-	a_bEnabled -> Flag determining if the GameObject is enabled.
		OUTPUT: ---
		*/
		void Init(String a_sName, bool a_bEnabled);
		
		/*
		USAGE: Destructor.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~GameObject(void);

#pragma endregion

#pragma region //	Rule of Three

		/*
		USAGE: Copy constructor.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		GameObject(GameObject const& input);

		/*
		USAGE: Copy assignment.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		GameObject& operator=(GameObject const& input);

#pragma endregion

#pragma region //	Service Methods

		/*
		USAGE: Update the GameObject.
		ARGUMENTS: a_fDelta -> Time that has passed (in seconds) since the last update call.
		OUTPUT: ---
		*/
		void Update(float a_fDelta);

#pragma endregion

#pragma region //	Status Checking Methods

		/*
		USAGE: Returns true if the GameObject has a component of the specified type.
		ARGUMENTS: a_uComponentType -> Unique type identifier for a given Component.
		OUTPUT: ---
		*/
		bool HasComponent(uint a_uComponentType);

		/*
		USAGE: Check if the game object has any components.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		bool IsEmpty(void);

		/*
		USAGE: Check if the object has been enabled.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		bool IsEnabled(void);
		
#pragma endregion

#pragma region //	Mutator Methods

		/*
		USAGE: Adds component to GameObject and returns a true if the operation was successful.
		ARGUMENTS:
		-	a_uComponentType -> Unique type identifier for a given Component.
		-	a_cComponent -> Component to be added to the GameObject.
		OUTPUT: ---
		*/
		bool AddComponent(uint a_uComponentType, Component const& a_cComponent) const;

		/*
		USAGE: Adds component to GameObject and returns a reference to either the same component or the component already on the GameObject, if it exists.
		ARGUMENTS: a_cComponent -> Component to be added to the GameObject.
		OUTPUT: ---
		*/
		Component& AddComponent(Component const& a_cComponent) const;

#pragma endregion

#pragma region //	Accesor Methods

		/*
		USAGE: Returns the component, if one of the specified type exists. Else, returns a nullptr.
		ARGUMENTS: a_uComponentType -> Unique type identifier for a given Component.
		OUTPUT: ---
		*/
		Component* GetComponent(uint a_uComponentType);

		/*
		USAGE: Returns the name of the game object as a string.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		String GetName(void);

		/*
		USAGE: Returns information and class definition about a particular instance of the GameObject as a human-readable string.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		String toString(void);

#pragma endregion

	}; // class GameObject

} // namespace Simplex.

#endif // __GAMEOBJECT_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/