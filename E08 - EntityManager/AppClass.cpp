#include "AppClass.h"
#include "GameObject.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(
		vector3(0.0f, 0.0f, 0.0f), //Position
		vector3(0.0f, 0.0f, 10.0f),	//Target
		AXIS_Y);				//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	//Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();

	// Instantiate Player
	m_pPlayer = new Player();
	
	// test out tostring
	std::cout << m_pPlayer->toString();

	// Makes a makeshift player hitbox
	m_pEntityMngr->AddEntity("Projectile.fbx", "player");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, 0.0f)) * glm::scale(vector3(0.5f, 0.5f, 0.5f)));

	//calculate the enemy spawn points
	EnemySpawnPoints();
	//spawn walls in
	SpawnWalls();

}
void Application::Update(void)
{
	//create a timer (this timer is from the 14B Lerp Video by Alberto)
	static uint uClock = m_pSystem->GenClock();
	static float fTime = 0.0f;
	float fDelta = m_pSystem->GetDeltaTime(uClock);
	fTime += fDelta;

	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	// game loop debug
	if (m_pPlayer->GetPlayerHealth() != 0)
	{
		// in game

		//spawn an enemy at a spawn point once every second has elapsed and set its velocity toward the center where the player is (is the timer in second because if it is not this wont work correctly)
		if (fTime >= 2) 
		{
			fTime = 0.0f;
			int randomSpawnNumber = rand() % (numEnemySpawn - 1);
			std::stringstream enemyName;
			enemyName << "enemy " << randomSpawnNumber;
			m_pEntityMngr->AddEntity("Pyramid.obj", enemyName.str());
			m_pEntityMngr->SetModelMatrix(glm::translate(vector3(enemySpawnPoints[randomSpawnNumber].x, enemySpawnPoints[randomSpawnNumber].y, enemySpawnPoints[randomSpawnNumber].z)));
			//make the enemy seek the center by assigning it a velocity
			int index = m_pEntityMngr->GetEntityIndex(enemyName.str());
			m_pEntityMngr->GetEntity(index)->SetVelocity(glm::normalize(-vector3(enemySpawnPoints[randomSpawnNumber].x, enemySpawnPoints[randomSpawnNumber].y, enemySpawnPoints[randomSpawnNumber].z)) * 0.2f);
		}

		//when the spacen bar is pressed fire the bullet infront of the player along the players forward vector
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isPressed == false)
		{
			isPressed = true;
			std::stringstream projectileName;
			projectileName << "bullet " << numProjectileSpawn;
			m_pEntityMngr->AddEntity("Projectile2.obj", projectileName.str());
			m_pEntityMngr->SetModelMatrix(glm::translate(vector3(m_pCameraMngr->GetForward().x, m_pCameraMngr->GetForward().y, m_pCameraMngr->GetForward().z)) * glm::scale(vector3(0.2f, 0.2f, 0.2f)));
			numProjectileSpawn++;
			//Take the cameras forward vector and make the bullets velocity one unit in that direction store the velocity with the entity
			int index = m_pEntityMngr->GetEntityIndex(projectileName.str());
			m_pEntityMngr->GetEntity(index)->SetVelocity(m_pCameraMngr->GetForward() * 6.0f);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			isPressed = false;
		}

		//Move the last entity added slowly to the right
		//matrix4 lastMatrix = m_pEntityMngr->GetModelMatrix();// get the model matrix of the last added
		//lastMatrix *= glm::translate(IDENTITY_M4, vector3(0.01f, 0.0f, 0.0f)); //translate it
		//m_pEntityMngr->SetModelMatrix(lastMatrix); //return it to its owner

		//Update Entity Manager
		m_pEntityMngr->Update();

		//Add objects to render list
		m_pEntityMngr->AddEntityToRenderList(-1, true);

		//Checks to see if player got hit
		if (m_pEntityMngr->UpdatePlayerHP() == true) {
			m_pPlayer->SetPlayerHealth(m_pPlayer->GetPlayerHealth() - 1);
		}

	}
 	else
	{
		// game over
		std::cout << "Game Over!\n";
	}
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release the entity manager
	m_pEntityMngr->ReleaseInstance();
	
	SafeDelete(m_pPlayer);
	
	//release GUI
	ShutdownGUI();
}

//calculate the spawn points of the enemies
void Application::EnemySpawnPoints(void)
{
	//calculate the circle to spawn the enemies
	//calculate the diff theta by using the nuber of subdivisions
	//the radius of the spawn circle
	float radius = numEnemyRad;
	float subDivisions = numEnemySpawn;
	float theta = 0;
	float diff = (2 * PI) / subDivisions;
	
	//calculate the points based on the number of sub divisions radius and diffTheta
	for (int i = 0; i < numEnemySpawn; i++)
	{
		enemySpawnPoints.push_back(vector3{ (radius * cos(theta)),0.0f, (radius * sin(theta)) });
		theta += diff;
	}

}
//calculate the spawn points of the walls and spawn them
void Application::SpawnWalls(void) 
{
	//calculate the points for the arena circles walls to spawn on
	//calculate the diff theta by using the nuber of subdivisions
	//the radius of the spawn circle (Make subdivisions = to the radius
	float radius = 80.0f;
	float subDivisions = 50.0f;
	float theta = 0.0f;
	float deg = 90.0f;
	float diff = (2.0f * PI) / subDivisions;
	float degStep = 360 / subDivisions;
	float x;
	float z;
	glm::mat4 rotMat;

	//spawn in all of the walls and rotate them
	for (int i = 0; i < subDivisions; i++)
	{
		// Get the obj
		std::stringstream wallName;
		wallName << "wall " << i;
		m_pEntityMngr->AddEntity("Tile2.obj", wallName.str());

		// calculate position
		x = radius * cos(theta);
		z = radius * sin(theta);

		rotMat = glm::translate(vector3(x, 0.0f, z));
		rotMat = glm::rotate(rotMat, deg, AXIS_Y);

		m_pEntityMngr->SetModelMatrix(rotMat);

		// update rotation for rad and degrees
		theta += diff;
		deg -= degStep;

	}

}