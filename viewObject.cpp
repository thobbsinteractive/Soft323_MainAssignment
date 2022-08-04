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
}

ViewObject::~ViewObject()
{
	cleanUP();
}

bool ViewObject::loadMeshIntoBuffer(char sysPath[],
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
	if( FAILED( D3DXLoadMeshFromX( sysPath, 
									D3DXMESH_MANAGED, 
                                    localDevice,
									&adjBuffer,
                                    &mtrlBuffer, 
									NULL, 
									&numMtrls, 
                                    &pMesh ) ) )
    {
		MessageBox(NULL, "Could not find Mesh", "Meshes.exe", MB_OK);
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
				D3DXCreateTextureFromFile(
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
		computeBoundingBox();
	}
    return result;
};

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
		::MessageBox(0, "OptimizeInplace() - FAILED", 0, 0);
	}
};

bool ViewObject::computeBoundingBox()
{
	HRESULT hr = 0;

	BYTE* v = 0;
	pMesh->LockVertexBuffer(0, (void**)&v);

	hr = D3DXComputeBoundingBox(
			(D3DXVECTOR3*)v,
			pMesh->GetNumVertices(),
			D3DXGetFVFVertexSize(pMesh->GetFVF()),
			&box.min,
			&box.max);

	pMesh->UnlockVertexBuffer();

	D3DXCreateBox(
		localDevice,
		box.max.x - box.min.x,
		box.max.y - box.min.y,
		box.max.z - box.min.z,
		&boxMesh,
		0);

	if( FAILED(hr) )
		return false;

	return true;
}

bool ViewObject::isPointInsideBoundingBox(D3DXVECTOR3* p,D3DXVECTOR3* currentPosition)
{
	return box.isPointInside(p,currentPosition);
}

void ViewObject::drawObject()
{
	for(int i = 0; i < (int)Mtrls.size(); i++)
	{
		localDevice->SetMaterial(&Mtrls[i]);
		localDevice->SetTexture(0,Textures[i]);
		pMesh->DrawSubset(i);
	}
};

void ViewObject::drawBoundingBox()
{
	boxMesh->DrawSubset(0);
};

void ViewObject::cleanUP()
{
	// release meshes
	Release<ID3DXMesh*>(boxMesh);
	Release<ID3DXMesh*>(pMesh);

	Release<ID3DXBuffer*>(adjBuffer); // done w/ buffer

	for(int i = 0; i < (int)Textures.size(); i++)
		Release<IDirect3DTexture9*>( Textures[i] );
};