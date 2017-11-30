#include "Player.h"
using namespace Simplex;

uint Simplex::Player::GetPlayerHealth(void)
{
	return m_uPlayerHealth;
}

void Simplex::Player::SetPlayerHealth(uint a_uPlayerHealth)
{
	m_uPlayerHealth = a_uPlayerHealth;
}

Simplex::Player::Player(void) : GameObject("Player")
{

}
