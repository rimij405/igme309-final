/*---------------------------------
Programmer: Ian Effendi (iae2784@g.rit.edu)
Team: The SQL
Date: 11/29/2017
-----------------------------------*/
#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Definitions.h"
#include "GameObject.h"

// Add the player class to the simplex namespace.
namespace Simplex 
{

	// The Player class wraps information and data regarding the Player object.
	class Player : public GameObject
	{

	private:

	#pragma region Private Fields
		// The health of a player.
		uint m_uPlayerHealth = 100;


	#pragma endregion

	#pragma region Private Methods

	#pragma endregion

	public:

	#pragma region Public Properties
		uint GetPlayerHealth(void);

		void SetPlayerHealth(uint a_uPlayerHealth);

	#pragma endregion

	#pragma region Public Methods

	#pragma endregion
	
	#pragma region //	Constructor / Init / Destructor
		
		Player(void);

	#pragma endregion
	};

}

#endif // __PLAYER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/