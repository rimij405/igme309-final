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
		vector3(0.0f, 0.0f, 13.0f), //Position
		vector3(0.0f, 0.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	//Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();

	// Instantiate Player
	m_pPlayer = new Player();
	
	// test out tostring
	std::cout << m_pPlayer->toString();

	//creeper
	//m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Creeper");
	//m_pEntityMngr->AddEntity("Projectile.fbx", "Creeper");
	//m_pEntityMngr->AddEntity("Pyramid.obj", "Creeper");
	//m_pEntityMngr->SetModelMatrix(glm::scale(vector3(0.001f, 0.001f, 0.001f)) * ToMatrix4(m_qCreeper), "Creeper");

	//steve
	//m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	//m_pEntityMngr->AddEntity("Tile.fbx", "Steve");
	//m_pEntityMngr->AddEntity("Tile2.obj", "Steve");

	//add an entity
	//m_pEntityMngr->AddEntity("Minecraft\\Cow.obj", "Cow");
	////set the model matrix
	//m_pEntityMngr->SetModelMatrix(glm::translate(vector3(2.0f, -1.5f, -1.0f)));
	
	//add an entity
	//m_pEntityMngr->AddEntity("Minecraft\\Zombie.obj", "Zombie");
	////set the model matrix
	//m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -2.5f, 0.0f)));
	//spawn the enemies in
	EnemySpawnPoints();
	for (int i = 0; i < numEnemySpawn; i++)
	{
		std::stringstream enemyName;
		enemyName << "enemy " << i;
		m_pEntityMngr->AddEntity("Pyramid.obj", enemyName.str());
		m_pEntityMngr->SetModelMatrix(glm::translate(vector3(enemySpawnPoints[i].x, enemySpawnPoints[i].y, enemySpawnPoints[i].z)));
	}
	//spawn walls in
	SpawnWalls();
	//add an entity
	//m_pEntityMngr->AddEntity("Minecraft\\Pig.obj", "Pig");
	//m_pEntityMngr->AddEntity("Projectile2.obj", "Pig");
	//set the model matrix
	//m_pEntityMngr->SetModelMatrix(glm::translate(vector3(-2.0f, -1.0f, -1.0f)));

}
void Application::Update(void)
{
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
		std::cout << "In Game Loop!\n";

		//

		//Move the last entity added slowly to the right
		matrix4 lastMatrix = m_pEntityMngr->GetModelMatrix();// get the model matrix of the last added
		lastMatrix *= glm::translate(IDENTITY_M4, vector3(0.01f, 0.0f, 0.0f)); //translate it
		m_pEntityMngr->SetModelMatrix(lastMatrix); //return it to its owner

		//Update Entity Manager
		m_pEntityMngr->Update();

		//Add objects to render list
		m_pEntityMngr->AddEntityToRenderList(-1, true);
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
	float radius = numEnemySpawn;
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
	float radius = 150.0f;
	float subDivisions = 150.0f;
	float theta = 0;
	float diff = (2 * PI) / subDivisions;
	//create a vector to store the points
	std::vector<vector3> wallSpawnPoints;
	//calculate the points based on the number of sub divisions radius and diffTheta
	for (int i = 0; i < subDivisions; i++)
	{
		wallSpawnPoints.push_back(vector3{ (radius * cos(theta)), 0.0f, (radius * sin(theta)) });
		theta += diff;
	}
	//spawn in all of the walls and rotate them.
	for (int i = 0; i < subDivisions; i++)
	{
		std::stringstream wallName;
		wallName << "wall " << i;
		m_pEntityMngr->AddEntity("Tile2.obj", wallName.str());
		//calculate the rotation of the walls
		float rotationDeg = 0;
		float rotationDegStep = 360 / subDivisions;
		m_pEntityMngr->SetModelMatrix(glm::translate(vector3(wallSpawnPoints[i].x, wallSpawnPoints[i].y, wallSpawnPoints[i].z)) * glm::rotate(IDENTITY_M4, rotationDeg, AXIS_Z));
		rotationDeg += rotationDegStep;

	}

}