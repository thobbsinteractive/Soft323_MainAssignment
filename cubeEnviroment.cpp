//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: cubeEnviroment
// loosley based on the cube class by Frank Luna, this class draws a cube textured with the 
// textures passed to it during creation.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "cubeEnviroment.h"
#include "vertex.h"

cubeEnviroment::cubeEnviroment()
{

}

cubeEnviroment::~cubeEnviroment()
{	
	Release<ID3DXMesh*>(pMesh);
	for(int i = 0; i < (int)Textures.size(); i++)
		Release<IDirect3DTexture9*>(Textures[i]);
}

bool cubeEnviroment::loadMeshIntoBuffer(char sysPath[],
										char backPath[],
										char frontPath[],
										char leftPath[],
										char rightPath[],
										char topPath[],
										char bottomPath[],
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
	if( FAILED(D3DXLoadMeshFromXA(sysPath,
									D3DXMESH_MANAGED, 
                                    localDevice,
									&adjBuffer,
                                    &mtrlBuffer, 
									NULL, 
									&numMtrls, 
                                    &pMesh ) ) )
    {
		MessageBox(NULL, L"Could not find Mesh", L"Meshes.exe", MB_OK);
        result = false;
    }

	material.Specular.r = 0;
	material.Specular.g = 0;
	material.Specular.b = 0;
	material.Specular.a = 0;
	material.Power	  = 100;
	material.Diffuse.r = 1.0;
	material.Diffuse.g = 1.0;
	material.Diffuse.b = 1.0;
	material.Diffuse.a = 0;
	material.Ambient.r = 1.0;
	material.Ambient.g = 1.0;
	material.Ambient.b = 1.0;
	material.Ambient.a = 0.0;
	material.Emissive.r= 1.0;
	material.Emissive.g= 1.0;
	material.Emissive.b= 1.0;
	material.Emissive.a= 0;

	IDirect3DTexture9* top = 0;
	IDirect3DTexture9* bottom = 0;
	IDirect3DTexture9* back = 0;
	IDirect3DTexture9* front = 0;
	IDirect3DTexture9* right = 0;
	IDirect3DTexture9* left = 0;

	D3DXCreateTextureFromFileA(localDevice, backPath,&back);
	D3DXCreateTextureFromFileA(localDevice, frontPath,&front);
	D3DXCreateTextureFromFileA(localDevice, leftPath,&left);
	D3DXCreateTextureFromFileA(localDevice, rightPath,&right);
	D3DXCreateTextureFromFileA(localDevice, topPath,&top);
	D3DXCreateTextureFromFileA(localDevice, bottomPath,&bottom);
	
	Textures.push_back(front);
	Textures.push_back(back);
	Textures.push_back(right);
	Textures.push_back(left);
	Textures.push_back(top);
	Textures.push_back(bottom);

    return result;
};

void cubeEnviroment::draw()
{

// Temp
	localDevice->SetRenderState(D3DRS_LIGHTING, false);

	
	// Set the first color argument to the texture associated with this stage
	//localDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	// Use this texture stage's first color unmodified, as the output. 
	//localDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);


	// Clamp texture co-ordinates to get rid of horrible seam
	localDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP );
	localDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP );


	int j = 0;
	localDevice->SetMaterial(&material);
	
	for(int i = 0; i < (int)Textures.size(); i++)
	{
		j = i+1;
		localDevice->SetTexture(0,Textures[i]);
		pMesh->DrawSubset(i); 
	}
	
	// Reset texture coordinates
	localDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP );
	localDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP );
	localDevice->SetRenderState(D3DRS_LIGHTING, true);

	localDevice->SetTexture(0, NULL);
}