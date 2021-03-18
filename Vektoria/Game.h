#pragma once


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif


#include "Vektoria\Root.h"

#define NR_OF_ASTEROIDS 1000

using namespace Vektoria;

//#define LIGHTRADIAL_IN_SUN
#define MAX_NR_OF_BULLETS 100u
#define F_BULLET_VELOCITY 2.0f



class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

private:
    // Hier ist Platz für Deine Vektoriaobjekte:
	CRoot m_zr;
	CScene m_zs;
	CPlacement m_zpCamera;
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;

#ifdef LIGHTRADIAL_IN_SUN
	CLightRadial m_zlr;
#else
	CPlacement m_zpLight;
	CLightSpot m_zls;
#endif

	//Background
	CBackground m_zb;
	CMaterial m_zmb;

	//Sun
	CPlacement m_zpSphereSun;
	CGeoSphere m_zgSphereSun;
	CMaterial m_zmSun;

	//Earth Moon System
	CPlacement m_zpEarthMoonSystem;

	//Earth
	CPlacement m_zpSphereEarth;
	CGeoSphere m_zgSphereEarth;
	CMaterial m_zm;

	//Clouds
	CPlacement m_zpSphereClouds;
	CPlacement m_zpSphereClouds2;

	CGeoSphere m_zgSphereClouds;
	CGeoSphere m_zgSphereClouds2;

	CMaterial m_zmClouds;
	CMaterial m_zmClouds2;

	//Moon
	CPlacement m_zpSphereMoon;
	CGeoSphere m_zgSphereMoon;
	CMaterial m_zmMoon;

	//Deathstar
	CPlacement m_zpSphereDeathStar;
	CGeoSphere m_zgSphereDeathStar;
	CMaterial m_zmDeathStar;

	//Satellit
	CPlacement m_azpSatellit[10];

	CGeoCylinder m_zgSatellit;
	CGeoCylinder m_zgBar;
	CGeoCube m_zgSolarPanelL;
	CGeoCube m_zgSolarPanelR;

	CMaterial m_zmSatellit;
	CMaterial m_zmSolarPanel;

	//Rocket
	CPlacement m_zpRocket;
	CGeoSweep m_zgRocket;
	CMaterial m_zmRocket;

	CHMat m_amRocket[5];
	CHMats m_msRocket;

	//Sky Sphere
	CPlacement m_zpSkySphere;
	CGeoSphere m_zgSkySphere;
	CMaterial m_zmSkySphere;

	//Keyboard Device
	CDeviceKeyboard m_zdk;

	//Cursor Device
	CDeviceCursor m_zdc;

	//Geo Container
	CGeos m_zgs;
	CMaterial m_zmPicked;

	//Asteroiden
	CPlacement m_zpAsteroids;
	CPlacement m_azpAsteroid[NR_OF_ASTEROIDS];
	CGeoQuad m_zgAsteroidEros;
	CMaterial m_zmEros;

	//Mauszeiger
	COverlay m_zoCursor;
	CMaterial m_zmCursor;

	//Bullets
	CGeoSphere m_zgBullet;
	CPlacement m_azpBullets[MAX_NR_OF_BULLETS];
	float m_afBulletCountdown[MAX_NR_OF_BULLETS];
	CHVector m_avBullets[MAX_NR_OF_BULLETS];
	unsigned int m_uStart = 0u;
	unsigned int m_uEnd = 0u;
	
};


