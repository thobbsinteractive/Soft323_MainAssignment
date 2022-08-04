/* Name: viewObject.cpp
   Description: The methods for the viewObject class
   This class loads a requested mesh from a file into the vertex buffer.
   The mesh is then optimized and when requested drawn. 
   
   This class is seperate from the object transform class because you may 
   have 20 ojects with the same mesh and in doing so, you do not want to 
   needlessly fill the vertex buffer with the same mesh data.
*/
#include "viewObject.h"

ViewObject::ViewObject()
{
	adjBuffer = 0;
	
	Light = D3DXVECTOR3(-1.0f,0.0f,1.0f);
	pNormalMap = NULL;
}

ViewObject::~ViewObject()
{
	cleanUP();
}

bool ViewObject::loadMeshIntoBuffer(char path[],
									IDirect3DDevice9* Device)
{
	// save a ptr to the device
	localDevice = Device;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;
	
	bool result = true;				// Initialise return result

	//MessageBox(NULL, sysPath, "Meshes.exe", MB_OK);

    // D3DXLoadMeshFromX
    // Load the mesh from the specified file
	if( FAILED( D3DXLoadMeshFromXA(path,
									D3DXMESH_MANAGED, 
                                    localDevice,
									&adjBuffer,
                                    &mtrlBuffer, 
									NULL, 
									&numMtrls, 
                                    &pMesh ) ) )
    {
		MessageBoxA(NULL, "Could not find Mesh", "Meshes.exe", MB_OK);
        result = false;
    }

	if (result)
	{
	//
	// Extract the materials, and load textures.
	//

	if( mtrlBuffer != 0 && numMtrls != 0 )
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for(int i = 0; i < (int)numMtrls; i++)
		{
			// the MatD3D property doesn't have an ambient value set
			// when its loaded, so set it now:
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			// save the ith material
			Mtrls.push_back( mtrls[i].MatD3D );

			// check if the ith material has an associative texture
			if( mtrls[i].pTextureFilename != 0 )
			{
				// yes, load the texture for the ith subset
				
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFileA(
					localDevice,
					mtrls[i].pTextureFilename,
					&tex);

				// save the loaded texture
				Textures.push_back( tex );
			}
			else
			{
				// no texture for the ith subset
				Textures.push_back( 0 );
			}
		}
	}
	Release<ID3DXBuffer*>(mtrlBuffer); // done w/ buffer
	}
	
	if(pMesh)
	{
		optmizeMesh();
		computeBoundingSphere();
	}

	// Bumpmapping
	D3DXCreateTextureFromFileA(localDevice,"models/high/normalmap.png",&pNormalMap);
    return result;
};

// For bumpmapping

DWORD ViewObject::VectorToRGB(D3DXVECTOR3* NormalVector)
{
DWORD dwR = (DWORD)(127 * NormalVector->x + 128);
DWORD dwG = (DWORD)(127 * NormalVector->y + 128);
DWORD dwB = (DWORD)(127 * NormalVector->z + 128);

return (DWORD)(0xff000000 + (dwR << 16) + (dwG << 8) + dwB);
}//VectorToRGB


void ViewObject::optmizeMesh()
{
	//
	// Optimize the mesh.
	//
	HRESULT hr = NULL;

	hr = pMesh->OptimizeInplace(		
	D3DXMESHOPT_ATTRSORT |
	D3DXMESHOPT_COMPACT  |
	D3DXMESHOPT_VERTEXCACHE,
	(DWORD*)adjBuffer->GetBufferPointer(),
	0, 0, 0);

	if(FAILED(hr))
	{
		::MessageBoxA(0, "OptimizeInplace() - FAILED", 0, 0);
	}
};

bool ViewObject::computeBoundingSphere()
{
	HRESULT hr = 0;

	BYTE* v = 0;
	pMesh->LockVertexBuffer(0, (void**)&v);

	hr = D3DXComputeBoundingSphere(
			(D3DXVECTOR3*)v,
			pMesh->GetNumVertices(),
			D3DXGetFVFVertexSize(pMesh->GetFVF()),
			&sphere.pos,
			&sphere.radius);
	
	//sphere.radius = sphere.radius/2;

	pMesh->UnlockVertexBuffer();

	D3DXCreateSphere(
		localDevice,
		sphere.radius,
		20,
		20,
		&sphereMesh,
		0);

	if( FAILED(hr) )
		return false;

	return true;
}

bool ViewObject::isPointInsideBoundingBox(D3DXVECTOR3* p,D3DXVECTOR3* currentPosition)
{
	sphere.setPosition(*currentPosition);
	return sphere.isPointInside(*p);
}

bool ViewObject::isPointIntersectingWithMesh(D3DXVECTOR3 rayObjOrigin,D3DXVECTOR3 rayObjDirection)
{
	BOOL hasHit;
	float distanceToCollision;

	D3DXIntersect(pMesh, &rayObjOrigin, &rayObjDirection, &hasHit, NULL, NULL, NULL, &distanceToCollision, NULL, NULL);


	if((distanceToCollision < 1000.0f)&&(hasHit == true))
	{
		hasHit = true;	
	}else
	{
		hasHit = false;
	}

	return hasHit;
}

ID3DXMesh* ViewObject::getMesh()
{
	return pMesh;
}

float  ViewObject::getBoundingRadius()
{
	return sphere.radius;
}

void ViewObject::drawObjectBump()
{	
	/*
		/// Layer 0 

		localDevice->SetTexture(0, pNormalMap);
		localDevice->SetTextureStageState(0, D3DTSS_COLOROP,       D3DTOP_DOTPRODUCT3);
		localDevice->SetTextureStageState(0, D3DTSS_COLORARG1,     D3DTA_TEXTURE);
		localDevice->SetTextureStageState(0, D3DTSS_COLORARG2,     D3DTA_DIFFUSE);

		/// Layer 1 

		localDevice->SetTexture(1,Textures[i]);
		localDevice->SetTextureStageState(1, D3DTSS_COLOROP,       D3DTOP_MODULATE);
		localDevice->SetTextureStageState(1, D3DTSS_COLORARG1,     D3DTA_TEXTURE);
		localDevice->SetTextureStageState(1, D3DTSS_COLORARG2,     D3DTA_CURRENT);
	*/

	// Set texture for the cube
	
	//for(int i = 0; i < (int)Mtrls.size(); i++)
	for(int i = 0; i < (int)Textures.size(); i++)
	{

		//
        // STAGE 0
        //
        // Use D3DTOP_DOTPRODUCT3 to find the dot-product of (N.L), where N is 
        // stored in the normal map, and L is passed in as the vertex color - 
        // D3DTA_DIFFUSE.
        //
		localDevice->SetMaterial(&Mtrls[i]);
    
		// Bump mapping
		localDevice->SetTexture( 0, pNormalMap );
        localDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );

        localDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3 ); // Perform a Dot3 operation...
        localDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );    // between the N (of N.L) which is stored in a normal map texture...
        localDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );    // with the L (of N.L) which is stored in the vertex's diffuse color.

        //
        // STAGE 1
        //
        // Modulate the base texture by N.L calculated in STAGE 0.
        //

		// Diffuse Map

        localDevice->SetTexture( 1, Textures[i] );
        localDevice->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 1 );

        localDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_MODULATE ); // Modulate...
        localDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE ); // the texture for this stage with...
        localDevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT ); // the current argument passed down from stage 0

		pMesh->DrawSubset(i);
	}

	// re-establishment of the parameters of returned
	
	localDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	localDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CURRENT);
	localDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

	localDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	localDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	localDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

	localDevice->SetTexture(0, NULL);
	localDevice->SetTexture(1, NULL);

	//localDevice->SetTexture(3, NULL);


};

void ViewObject::drawObject()
{	
	
	for(int i = 0; i < (int)Mtrls.size(); i++)
	{
		localDevice->SetMaterial(&Mtrls[i]);
		localDevice->SetTexture( 0,Textures[i]);
		pMesh->DrawSubset(i);
	}
	localDevice->SetTexture(0, NULL);
};

DWORD  ViewObject::F2DW( FLOAT f ) { 
	return *((DWORD*)&f); 
}

void ViewObject::drawObjectForRadar()
{
	for(int i = 0; i < (int)Mtrls.size(); i++)
	{
		pMesh->DrawSubset(i);
	}

};

void ViewObject::drawBoundingSphere()
{
	sphereMesh->DrawSubset(0);
};

void ViewObject::cleanUP()
{
	// release meshes
	//Release<ID3DXMesh*>(sphereMesh);
	//Release<ID3DXMesh*>(pMesh);

//	sphereMesh->Release();
	//if(pMesh)
	//{
	//	pMesh->Release();
	//}

	Release<ID3DXBuffer*>(adjBuffer); // done w/ buffer

	for(int i = 0; i < (int)Textures.size(); i++)
		Release<IDirect3DTexture9*>( Textures[i] );

	Mtrls.clear();
};