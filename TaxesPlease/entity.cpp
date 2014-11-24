#include "entity.h"


entity::entity(SDL_Renderer * renderer, int i)
{
	mRenderer = renderer;
}

entity::~entity()
{
}


void entity::LoadImage()
{
	mTexture = IMG_LoadTexture(mRenderer, name.c_str());
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

void entity::CallDraw()
{
	while(true)
	{
		Lock(m_id);
		Draw(m_id);
		Unlock(m_id);
	}
}

void entity::Lock(int pid)
{
	ticket[pid] = getMax(ticket) + 1;

	for(int i =0; i < max; i++)
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
}

void entity::Draw()
{

	SDL_RenderCopyEx(mRenderer, mTexture, &imageSourceRect, &sizeRect, (rotation*180.0/3.14159265), NULL, SDL_RendererFlip::SDL_FLIP_NONE);

}