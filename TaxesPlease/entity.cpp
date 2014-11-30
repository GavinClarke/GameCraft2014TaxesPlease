#include "entity.h"


entity::entity(SDL_Renderer * renderer, int i, std::vector<int> & tickets,SDL_mutex * l)
{
	mRenderer = renderer;
	MAX = 6;
	ticket = tickets;
	m_id = i;
	lock = l;
}

entity::~entity()
{
}


void entity::LoadImage(std::string image, entity * ent)
{
	ent->LockTwo();
	ent->mTexture = IMG_LoadTexture(ent->mRenderer, image.c_str());
	ent->UnlockTwo();
}

void entity::setTextureName(std::string value)
{
	name = value;
}

void entity::setSizeRect(float x, float y, float h, float w)
{
	sizeRect.x = x;
	sizeRect.y = y;
	sizeRect.h = h;
	sizeRect.w = w;
}

void entity::setImageSourceRect(float x, float y, float h, float w)
{
	imageSourceRect.x = x;
	imageSourceRect.y = y;
	imageSourceRect.h = h;
	imageSourceRect.w = w;
}

void entity::setRotation(float value)
{
	rotation = value;
}


int entity::CallDraw()
{
	
	
	while(true)
	{
		if ((*count) == 0)
		{
			
		}
		
		LockTwo();
		Draw();
		UnlockTwo();
		
	}
	
	return 0;
}

void entity::LockTwo()
{
	SDL_LockMutex(lock);
}

void entity::UnlockTwo()
{
	
	
	SDL_UnlockMutex( lock );
	
	
}

void entity::Lock(int pid)
{
	ticket[pid] = getMax(ticket) + 1;

	for (int i = 0; i < MAX; i++)
		if(i != pid)
		{
			
			//while(Main.entering.get(i) == 1){}
			
			while(ticket[i] != 0 && 
				 (ticket[pid] > ticket[i] ||
				 (ticket[pid] == ticket[i] && pid > i ))){}
			
		}
}

void entity::Unlock(int pid)
{
	ticket[pid] = 0;
	if ((*count) >=6)
	{
		SDL_RenderPresent(mRenderer);
		(*count) = 0;
	}
}

int entity::getMax(std::vector<int> ticketA)
{
	int current = 0;
	for (int i = 0; i < MAX; i++)
	{
		if (ticketA[i] >= current)
		{
			current = ticketA[i];
		}
	}
	return current;
}

void entity::Draw()
{
	SDL_RenderCopyEx(mRenderer, mTexture, &imageSourceRect, &sizeRect, (rotation*180.0/3.14159265), NULL, SDL_RendererFlip::SDL_FLIP_NONE);

}