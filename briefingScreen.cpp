#include "briefingScreen.h"

BriefingScreen::BriefingScreen()
{
	
}

BriefingScreen::~BriefingScreen()
{

}

void BriefingScreen::initialise(int _width,int _height,IDirect3DDevice9* device)
{
	localDevice = device;
	width = _width;
	height = _height;

	D3DXMatrixPerspectiveFovLH(
		& matProj,
		D3DX_PI * 0.25f,
		(float)width / (float)height,
		1.0f,
		10000000.0f);

	localDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	backGround.setupSprite(localDevice,1024,768,"sprites/high/screen.jpg");

	//
	// Initialize a LOGFONT structure that describes the font
	// we want to create.
	//

	D3DXFONT_DESCA lf;
	ZeroMemory(&lf, sizeof(D3DXFONT_DESCA));

	lf.Height         = 12;    // in logical units
	lf.Width          = 8;    // in logical units   
	lf.Weight         = 500;   // boldness, range 0(light) - 1000(bold) 
	lf.CharSet        = DEFAULT_CHARSET;
	lf.OutputPrecision  = 0;                       
	lf.Quality        = 0;           
	lf.PitchAndFamily = 0;           
	strcpy(lf.FaceName, "Times New Roman"); // font style

	//
	// Create an ID3DXFont based on 'lf'.
	//

	if(FAILED(D3DXCreateFontIndirectA(localDevice, &lf, &font)))
	{
		::MessageBox(0, L"D3DXCreateFontIndirect() - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
}

void BriefingScreen::setText(std::string newText)
{
	text = newText;
}

void BriefingScreen::displayScreen()
{
	float aspectRatio = (float)width / (float)height;

	RECT rect = { (width / 100) * 22, (height / 100) * 28, (width / 100 * 90),height };
	if (aspectRatio == 1.77777779f)
	{
		rect = { (long)(((float)width / 100) * 30), (long)(((float)height / 100) * 30), (long)(((float)width / 100) * 70), height };
	}

	D3DXMATRIX RotationMatrix;
	D3DXMATRIX Translation;
	D3DXMATRIX Scaling; 
	D3DXMATRIX World;

	D3DXMatrixScaling(&Scaling,1.0f,1.0f,1.0f);
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix,0*(D3DX_PI/180),0.0f,0.0f);
	D3DXMatrixTranslation(&Translation, 0.0f,0.0f,0.0f);

	World = RotationMatrix * Translation * Scaling;

	localDevice->SetTransform(D3DTS_WORLD, &World);
	backGround.draw();

	font->DrawTextA(NULL, text.c_str(), -1,&rect,DT_TOP | DT_LEFT, 0xffffffff);

	D3DXVECTOR3 cameraPosition = D3DXVECTOR3(0.0f,0.0f,-910.0f);
	D3DXVECTOR3 cameraLookAt = D3DXVECTOR3(0.0f,0.0f,100.0f);
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f,1.0f,0.0f);

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &cameraPosition,&cameraLookAt,&up);
	localDevice->SetTransform(D3DTS_VIEW, &matView);	
}