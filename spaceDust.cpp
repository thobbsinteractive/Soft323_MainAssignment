
#include "spaceDust.h"
//*****************************************************************************
// Snow System
//***************

SpaceDust::SpaceDust(BoundingBox* _boundingBox, int numParticles)
{
	boundingBox   = *_boundingBox;
	size          = 10.0f;
	vbSize        = 2048;
	vbOffset      = 0; 
	vbBatchSize   = 512; 
	
	for(int i = 0; i < numParticles; i++)
		addParticle();
}

void SpaceDust::resetParticle(Attribute* attribute)
{
	attribute->isAlive  = true;

	// get random x, y, z coordinate for the position of the snow flake.

		getRandomVector(
		&attribute->position,
		&boundingBox.min,
		&boundingBox.max,
		&boundingBox.pos);

	// no randomness for height (y-coordinate).  Snow flake
	// always starts at the top of bounding box.
	//attribute->position.y = boundingBox.max.y; 

	// snow flakes fall downwards and slightly to the left
	attribute->velocity.x = getRandomFloat(0.0f, 0.0f);
	attribute->velocity.y = getRandomFloat(0.0f, 0.0f);
	//attribute->velocity.z = getRandomFloat(0.0f, 1.0f) * -10.0f;

	// white snow flake
	attribute->color = D3DXCOLOR( D3DCOLOR_XRGB(255, 255, 255) );
}

void SpaceDust::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for(i = particles.begin(); i != particles.end(); i++)
	{
		i->position += i->velocity * timeDelta;

		// is the point outside bounds?
		if( boundingBox.isPointInside( i->position ) == false ) 
		{
			// nope so kill it, but we want to recycle dead 
			// particles, so respawn it instead.
			resetParticle( &(*i) );
		}
	}
}
