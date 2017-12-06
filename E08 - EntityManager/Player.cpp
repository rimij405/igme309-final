#include "Player.h"
using namespace Simplex;

uint Player::GetPlayerHealth(void)
{
	return m_uPlayerHealth;
}

void Player::SetPlayerHealth(uint a_uPlayerHealth)
{
	m_uPlayerHealth = a_uPlayerHealth;
}

Player::Player(void) : GameObject("Player")
{
	m_uPlayerHealth = 3;
}
