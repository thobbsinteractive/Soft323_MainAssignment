#include "3DSound.h"
#include "Core\DXUT.h"

_3DSound::_3DSound()
{

}

_3DSound::~_3DSound()
{
	//delete pSound3D;
	//delete sound3Dmanager;
}

void _3DSound::stop()
{
	pSound3D->Stop();
}

void _3DSound::reset()
{
	pSound3D->Reset();
}

void _3DSound::initialiseSound(IDirect3DDevice9* _pDevice,LPTSTR wavFileName, HWND handle,CSoundManager *_sound3Dmanager)
{
	//sound3Dmanager = _sound3Dmanager;
	pLocalDevice = _pDevice;

	HRESULT hr;

    // Create a static IDirectSound in the CSound class.
    // Set coop level to DSSCL_PRIORITY, and set primary buffer
    // format to stereo, 22kHz and 16-bit output.

    sound3Dmanager = new CSoundManager();

    hr = sound3Dmanager->Initialize( handle, DSSCL_PRIORITY );
       
    hr |= sound3Dmanager->SetPrimaryBufferFormat( 2, 22050, 16 );

    // Get the 3D listener, so we can control its params
    hr |= sound3Dmanager->Get3DListenerInterface( &pDSListener );

    if( FAILED(hr) )
		MessageBox(NULL, _T("Can't initialise directSound manager"), _T("FinalAssignment.exe"), MB_OK);


        // Get listener parameters
    dsListenerParams.dwSize = sizeof(DS3DLISTENER);
    pDSListener->GetAllParameters( &dsListenerParams );

    CWaveFile waveFile;
    if FAILED(waveFile.Open( wavFileName, NULL, WAVEFILE_READ ))
    {
	   MessageBox(NULL, _T("Can't open Wav file"), _T("FinalAssignment.exe"), MB_OK);
       return;
    }


    WAVEFORMATEX* pwfx = waveFile.GetFormat();
    if( pwfx == NULL )
    {
		MessageBox(NULL, _T("Invalid wave file format."), _T("FinalAssignment.exe"), MB_OK);
        return;
    }

    if( pwfx->nChannels > 1 )
    {
        // Too many channels in wave.  Sound must be mono when using DSBCAPS_CTRL3D
		MessageBox(NULL, _T("Wave file must be mono for 3D control."), _T("FinalAssignment.exe"), MB_OK);
        return;
    }

    if( pwfx->wFormatTag != WAVE_FORMAT_PCM )
    {
        // Sound must be PCM when using DSBCAPS_CTRL3D
		MessageBox(NULL, _T("Wave file must be PCM for 3D control."), _T("FinalAssignment.exe"), MB_OK);
        return;
    }



        // Load the wave file into a DirectSound buffer
    hr = sound3Dmanager->Create( &pSound3D, wavFileName, DSBCAPS_CTRL3D,
         DS3DALG_NO_VIRTUALIZATION);

    if( FAILED( hr ) || hr == DS_NO_VIRTUALIZATION )
    {
		MessageBox(NULL, _T("Error creating 3-d sound."), _T("FinalAssignment.exe"), MB_OK);
        if( DS_NO_VIRTUALIZATION == hr )
        {
			MessageBox(NULL, _T("The 3D virtualization algorithm requested is not supported under this"
                "operating system.  It is available only on Windows 2000, Windows ME, and Windows 98 with WDM"
                "drivers and beyond.  Creating buffer with no virtualization."), 
                _T("FinalAssignment.exe"), MB_OK);
       
        }

        // Unknown error, but not a critical failure, so just update the status
		MessageBox(NULL, _T("Could not create sound buffer."), _T("FinalAssignment.exe"),MB_OK);

        return;
    }

    // Get the 3D buffer from the secondary buffer
    if( FAILED( hr = pSound3D->Get3DBufferInterface( 0, &pDS3DBuffer ) ) )
    {
		MessageBox(NULL, _T("Could not get 3D buffer."), _T("FinalAssignment.exe"),MB_OK);
        return;
    }

    // Get the 3D buffer parameters
    dsBufferParams.dwSize = sizeof(DS3DBUFFER);
    pDS3DBuffer->GetAllParameters( &dsBufferParams );

    // Set new 3D buffer parameters
    dsBufferParams.dwMode = DS3DMODE_HEADRELATIVE;
    pDS3DBuffer->SetAllParameters( &dsBufferParams, DS3D_IMMEDIATE );

    DSBCAPS dsbcaps;
    ZeroMemory( &dsbcaps, sizeof(DSBCAPS) );
    dsbcaps.dwSize = sizeof(DSBCAPS);

    LPDIRECTSOUNDBUFFER pDSB = pSound3D->GetBuffer( 0 );
    pDSB->GetCaps( &dsbcaps );

    //if( ( dsbcaps.dwFlags & DSBCAPS_LOCHARDWARE ) != 0 )
        //ShowMessage("File loaded using hardware mixing.");
    //else
        //ShowMessage("File loaded using software mixing.");



    Set3DParameters( 1.5,    // Doppler Factor
                     0.0,  // Rolloff Factor
                     1000,  //MinDistance
                     10000000,D3DXVECTOR3(0.0f,0.0f,0.0f));  //MaxDistance.
}

void _3DSound::playSound3D()
{
   if (pSound3D != NULL)
   {
	   if(pSound3D->IsSoundPlaying()== false)
	   {
			pSound3D->Stop();
			pSound3D->Reset();
			pSound3D->Play(0, 0);
	   }else
	   {
			pSound3D->Play(0, 0);
	   }
   }
}

void _3DSound::playSound3D(unsigned long int dwPriority,unsigned long int dwFlags)
{
	if (pSound3D != NULL) 
	{
		pSound3D->Play(dwPriority, dwFlags);
	}
}

void _3DSound::setSoundPos(D3DXVECTOR3 position,float speed)
{
	if (pSound3D != NULL)   //i.e. there is a 3-d sound.
      {
      dsBufferParams.vPosition.x = position.x;
      dsBufferParams.vPosition.y = position.y;
      dsBufferParams.vPosition.z = position.z;

      dsBufferParams.vVelocity.x = 0;
      dsBufferParams.vVelocity.y = 0;
      dsBufferParams.vVelocity.z = speed;


    if( pDS3DBuffer )
        pDS3DBuffer->SetAllParameters( &dsBufferParams, DS3D_DEFERRED );
    }
}

void _3DSound::setListenerSoundPos(D3DXVECTOR3 soundPosition,float speed)
{
	//DWORD dwApplyFlag = DS3D_DEFERRED;//( bDeferSettings ) ? DS3D_DEFERRED : DS3D_IMMEDIATE;
	DWORD dwApplyFlag = DS3D_DEFERRED;
	
	if (pSound3D != NULL)   //i.e. there is a 3-d sound.
    {
		Set3DParameters(1.5,    // Doppler Factor
                     0.2,  // Rolloff Factor
                     0.5,  //MinDistance
                     100000,soundPosition);  //MaxDistance.

		//pDSListener->SetAllParameters( &dsListenerParams, dwApplyFlag,D3DXVECTOR3 soundPosition);
		pDSListener->CommitDeferredSettings(); // updates the listener for all sounds
	}
}

void _3DSound::Set3DParameters(float fDopplerFactor, float fRolloffFactor,
                               float fMinDistance,   float fMaxDistance,D3DXVECTOR3 soundPosition)
{
	// Every change to 3-D sound buffer and listener settings causes
    // DirectSound to remix, at the expense of CPU cycles.
    // To minimize the performance impact of changing 3-D settings,
    // use the DS3D_DEFERRED flag in the dwApply parameter of any of
    // the IDirectSound3DListener or IDirectSound3DBuffer methods that
    // change 3-D settings. Then call the IDirectSound3DListener::CommitDeferredSettings
    // method to execute all of the deferred commands at once.
    DWORD dwApplyFlag = ( bDeferSettings ) ? DS3D_DEFERRED : DS3D_IMMEDIATE;

	dsListenerParams.vPosition.x = soundPosition.x;
	dsListenerParams.vPosition.y = soundPosition.y;
	dsListenerParams.vPosition.z = soundPosition.z;

	dsListenerParams.vVelocity.x = 0;
	dsListenerParams.vVelocity.y = 0;
	dsListenerParams.vVelocity.z = 0;

    dsListenerParams.flDopplerFactor = fDopplerFactor;
    dsListenerParams.flRolloffFactor = fRolloffFactor;

    if( pDSListener )
        pDSListener->SetAllParameters( &dsListenerParams, dwApplyFlag );

    dsBufferParams.flMinDistance = fMinDistance;
    dsBufferParams.flMaxDistance = fMaxDistance;

    if( pDS3DBuffer )
	{
        pDS3DBuffer->SetAllParameters( &dsBufferParams, dwApplyFlag );
	}
}