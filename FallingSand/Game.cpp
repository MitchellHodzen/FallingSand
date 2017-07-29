#include "Game.h"


Game::Game()
{
	screenWidth = 800;
	screenHeight = 600;

	renderer = new Renderer(screenWidth, screenHeight, false);
	//mediaManager = new MediaManager();
	inputManager = new InputManager();
}


Game::~Game()
{
	delete renderer;
	//delete mediaManager;
	delete inputManager;
}

void Game::Start()
{
	std::cout<<0x10<<std::endl<<0x80<<std::endl<<0x100<<std::endl;
	if (Initialize())
	{
		float averageFramerate = 0;
		int frames = 0;
		bool quit = false;

		//How often the board updates, must be a low enough framerate to ensure update finishes in time
		const float fixedTimeStep = 1.0/10.0;
		float physicsTimer = 0;

		Uint32 lastFrameTime = 0;
		Uint32 currentFrameTime = 0;
		float deltaTime = 0.0f;
		currentFrameTime = SDL_GetTicks();


		Board board(screenWidth, screenHeight, renderer);


		while (quit == false)
		{
			//Calculate frame time
			lastFrameTime = currentFrameTime;
			currentFrameTime = SDL_GetTicks();
			deltaTime = (float)(currentFrameTime - lastFrameTime) / 1000;
			averageFramerate += 1/deltaTime;
			frames++;
			//if (deltaTime > 1.0/1.0) {deltaTime = 1.0/1.0;}
			//std::cout<<1/deltaTime<<std::endl;
			
			//Get user input
			quit = inputManager->HandleInput();
			
			//Fixed time step for calculating change in board
			physicsTimer += deltaTime;
			//while (physicsTimer >= fixedTimeStep)
			//{
				//Update board
				board.Update();
				//physicsTimer -= fixedTimeStep;
			//}
				
			//Draw board
			renderer->Draw(board.GetTexture());
			//SDL_Delay(30);
		}
		averageFramerate = averageFramerate / frames;
		std::cout<<"Average Framerate: " << averageFramerate << std::endl;
	}
}

bool Game::Initialize()
{
	if (renderer->Initialize() == true)
	{
		//mediaManager->CreateTexture("Media/Sprites/megamanx.png", renderer->GetRenderer());
		return true;
	}
	else
	{
		return false;
	}
}


