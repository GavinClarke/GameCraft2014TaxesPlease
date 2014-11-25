#include "Menu.h"


Menu::Menu(SDL_Renderer * renderer,Constants * con)
{
	
	mRenderer = renderer;
	LoadImage();
	c = con;
	playRect = SDL_Rect();
	playRect.x = 0;
	playRect.y = 0;
	playRect.h = 100;
	playRect.w = 200;

	QuitRect = SDL_Rect();
	QuitRect.x = 0;
	QuitRect.y = 150;
	QuitRect.h = 100;
	QuitRect.w = 200;
}


Menu::~Menu(void)
{
}

int Menu::Update()
{
	if(MouseClick(playRect))
	{
		return 1;
	}
	else if(MouseClick(QuitRect))
	{
		c->QUIT = false;
	}
}

void Menu::LoadImage()
{
	Play = IMG_LoadTexture(mRenderer,"PLAY.png");
	Quit = IMG_LoadTexture(mRenderer,"Quit.png");
}

void Menu::Draw()
{
	SDL_RenderCopy(mRenderer,Play,NULL,&playRect);
	SDL_RenderCopy(mRenderer,Quit,NULL,&QuitRect);
}

bool Menu::MouseClick(SDL_Rect rect)
{
	int x;
	int y;
	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if(x > rect.x && y > rect.y && x < rect.x + rect.w && y < rect.y + rect.h)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	return false;
}