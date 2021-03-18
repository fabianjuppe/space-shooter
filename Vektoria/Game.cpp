#include "Game.h"

CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	//Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_zr.Init(psplash);
	m_zc.Init(0.7f, 0.5,70000);
	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);


	//Background
	m_zmb.MakeTextureSprite("textures\\8k_stars.jpg");
	m_zb.InitFull(&m_zmb);


	//Bloom
	m_zv.SetBloomOn();
	m_zv.SetBloomStrengthNear(4.0f);
	m_zv.SetBloomStrengthFar(2.0f);
	m_zv.SetBloomWidth(5);


	//Sun
	m_zs.AddPlacement(&m_zpSphereSun);
	m_zpSphereSun.AddPlacement(&m_zpEarthMoonSystem);
	m_zpSphereSun.AddGeo(&m_zgSphereSun);
	m_zgSphereSun.Init(10.0F, &m_zmSun, 30, 30);
	m_zmSun.MakeTextureGlow("textures\\SunG.jpg");
	m_zmSun.SetGlowEverywhere();
	m_zmSun.SetTextureSpecularBlack();
	m_zmSun.SetGlowStrength(2.0f);
	

#ifdef LIGHTRADIAL_IN_SUN
	m_zlr.Init();
	m_zpSphereSun.AddLightRadial(&m_zlr);
#else
	m_zls.Init(CColor(1.0f, 1.0f, 1.0f), 0.3f, 0.4f);
	m_zls.SetShadowOn();
	m_zls.SetShadowMapResolution(8000, 8000);
	m_zpLight.AddLightSpot(&m_zls);
	m_zpSphereSun.AddPlacement(&m_zpLight);
	m_zpLight.SetPointing(&m_zpEarthMoonSystem);
	m_zs.SetLightAmbient(0.2f);
#endif


	//Earth
	m_zpEarthMoonSystem.AddPlacement(&m_zpSphereEarth);
	m_zpSphereEarth.AddGeo(&m_zgSphereEarth);
	m_zgSphereEarth.Init(1.0F, &m_zm, 50, 50);
	m_zm.MakeTextureDiffuse("textures\\earth_image.jpg");
	m_zm.MakeTextureSpecular("textures\\earth_refelction.jpg");
	m_zm.MakeTextureBump("textures\\earth_bump.jpg");
	m_zm.MakeTextureGlow("textures\\earth_glow.jpg");


	//Clouds
	m_zpSphereEarth.AddPlacement(&m_zpSphereClouds);
	m_zpSphereClouds.AddGeo(&m_zgSphereClouds);
	m_zgSphereClouds.Init(1.001F, &m_zmClouds, 50, 50);
	m_zmClouds.MakeTextureDiffuse("textures\\clouds_alpha_l1.gif");
	m_zmClouds.SetTransparencyOn();

	m_zpSphereEarth.AddPlacement(&m_zpSphereClouds2);
	m_zpSphereClouds2.AddGeo(&m_zgSphereClouds2);
	m_zgSphereClouds2.Init(1.002F, &m_zmClouds2, 50, 50);
	m_zmClouds2.MakeTextureDiffuse("textures\\clouds_alpha_l2.gif");
	m_zmClouds2.SetTransparencyOn();


	//Moon
	m_zpEarthMoonSystem.AddPlacement(&m_zpSphereMoon);
	m_zpSphereMoon.AddGeo(&m_zgSphereMoon);
	m_zgSphereMoon.Init(0.4f, &m_zmMoon, 40, 40);
	m_zmMoon.MakeTextureDiffuse("textures\\moon_image.jpg");
	m_zmMoon.MakeTextureBump("textures\\moon_bump.jpg");


	//Deathstar
	m_zpEarthMoonSystem.AddPlacement(&m_zpSphereDeathStar);
	m_zpSphereDeathStar.AddGeo(&m_zgSphereDeathStar);
	m_zgSphereDeathStar.Init(0.2f, &m_zmDeathStar, 30, 30);
	m_zmDeathStar.MakeTextureDiffuse("textures\\deathstar.jpg");


	//Satellit
	for (int i = 0; i < 10; i++)
	{
		m_zpSphereEarth.AddPlacement(&m_azpSatellit[i]);

		float fa = TWOPI * ((float)i / 10.0f);

		m_azpSatellit[i].Scale(1.0f);

		float fRadiusOrbitSatellit = 5.0f;
		m_azpSatellit[i].TranslateDelta(fRadiusOrbitSatellit * sinf(fa), 0.0f, fRadiusOrbitSatellit * cosf(fa));

		float faY = HALFPI * (rand() % 1000) * 0.001f;
		m_azpSatellit[i].RotateXDelta(faY);
		m_azpSatellit[i].AddGeo(&m_zgSatellit);
	}
	float fSatellitHeight = 0.05f;

	m_zgSatellit.Init(0.02f, 0.02f, fSatellitHeight, &m_zmSatellit);
	
	float fBarHeight = 0.035771f;
	float fBarRadius = 0.0025f;
	float fSolarPanelSizeX = fSatellitHeight / 2.0f;
	float fSolarPanelSizeY = fSatellitHeight;
	float fSolarPanelSizeZ = 0.025f;

	m_zgBar.Init(fBarRadius, fBarRadius, fBarHeight, &m_zmSatellit);
	m_zgSatellit.AddGeo(&m_zgBar);
	CHMat m;
	m.TranslateY(-fBarHeight / 2.0f);
	m.RotateX(HALFPI);
	m_zgBar.Transform(m);

	m.TranslateY(-fBarHeight / 2.0f);
	m_zgSatellit.Transform(m);

	m_zgSolarPanelL.Init(fSolarPanelSizeX, fSolarPanelSizeY, fSolarPanelSizeZ, &m_zmSolarPanel, 2.0f);
	m_zgSolarPanelR.Init(fSolarPanelSizeX, fSolarPanelSizeY, fSolarPanelSizeZ, &m_zmSolarPanel, 2.0f);
	m_zgSatellit.AddGeo(&m_zgSolarPanelL);
	m_zgSatellit.AddGeo(&m_zgSolarPanelR);
	m.TranslateX((fBarHeight + fSolarPanelSizeX) * 0.5f);
	m_zgSolarPanelL.Transform(m);
	m.TranslateX(-(fBarHeight + fSolarPanelSizeX) * 0.5f);
	m_zgSolarPanelR.Transform(m);

	m_zmSatellit.LoadPreset("PanoPlate");
	m_zmSolarPanel.LoadPreset("TilesDirty");
	m_zmSolarPanel.Scale(CColor(0.5f, 0.5f, 2.0f));
	m_zmSolarPanel.TranslateDelta(CColor(-0.2f, -0.2f, 0.3f));


	//Rocket
	m_zpEarthMoonSystem.AddPlacement(&m_zpCamera);
	m_zpRocket.AddGeo(&m_zgRocket);
	m_zpRocket.Scale(0.05f);
	m_zpRocket.Translate(0.0f, -4.0f, -25.0f);
	m_zpRocket.ScaleDelta(0.1f);

	m_zmRocket.LoadPreset("PanoPlate");
	m_zmRocket.Translate(CColor(0.4f, 0.0f, 0.0f));

	//Punkt an der Basis der Rakete
	m_amRocket[0].Scale(0.0f);

	//Basis der Rakete
	m_amRocket[1].Scale(1.5f);

	//Erster Ring der Rakete
	m_amRocket[2].TranslateY(1.0f);

	//Oberer Ring der Rakete
	m_amRocket[3].TranslateY(5.0f);

	//Oberste Spitze der Rakete
	m_amRocket[4].Scale(0.0f);
	m_amRocket[4].TranslateYDelta(7.0f);

	for (int i = 0; i < 5; i++)
		m_msRocket.Add(&m_amRocket[i]);
	m_zgRocket.InitCircle(&m_zmRocket, 20, m_msRocket);

	CHMat mKipp;
	mKipp.RotateX(-HALFPI);
	m_zgRocket.Transform(mKipp);


	//Sky Sphere
	m_zs.AddPlacement(&m_zpSkySphere);
	m_zpSkySphere.AddGeo(&m_zgSkySphere);
	m_zpSkySphere.SetSky();
	m_zgSkySphere.Init(30000.0f, &m_zmSkySphere);
	m_zgSkySphere.Flip();
	m_zmSkySphere.MakeTextureSprite("textures\\8k_stars.jpg");


	//Frame
	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zv.AddBackground(&m_zb);
	m_zf.AddDeviceKeyboard(&m_zdk);
	m_zf.AddDeviceCursor(&m_zdc);
	m_zr.AddScene(&m_zs);


	//Camera
	m_zs.AddPlacement(&m_zpCamera);
	m_zpCamera.AddPlacement(&m_zpRocket);
	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.SetTranslationSensitivity(20.0f);


	//Mauszeiger
	m_zmCursor.MakeTextureSprite("textures\\Mauszeiger.tiff");
	m_zmCursor.SetTransparencyOn();
	m_zoCursor.Init(&m_zmCursor, CFloatRect(0.3f, 0.3f, 0.05f, 0.05f));
	m_zv.AddOverlay(&m_zoCursor);


	//Geo Container
	m_zgs.Add(&m_zgSphereSun);
	m_zgs.Add(&m_zgSphereEarth);
	m_zgs.Add(&m_zgSphereMoon);
	m_zgs.Add(&m_zgSphereDeathStar);
	m_zgs.Add(&m_zgSatellit);
	m_zgs.Add(&m_zgRocket);
	m_zmPicked.LoadPreset("SpriteRed");
	m_zr.AddMaterial(&m_zmPicked);
	m_zs.SetDynamicBVHsOn();


	//Asteroiden
	m_zgAsteroidEros.Init(0.2f, 0.3f, &m_zmEros);
	m_zmEros.MakeTextureBillboard("textures\\asteroid_image_1.bmp");
	m_zmEros.SetChromaKeyingOn();
	m_zs.AddPlacement(&m_zpAsteroids);
	for (int i = 0; i < NR_OF_ASTEROIDS; i++)
	{
		//Asteroidenhierarchie
		m_zpAsteroids.AddPlacement(&m_azpAsteroid[i]);
		m_azpAsteroid[i].AddGeo(&m_zgAsteroidEros);

		//Zufälliger Abstand
		float frRandTranslationX = UM_FRAND();
		frRandTranslationX *= frRandTranslationX * frRandTranslationX;
		float frMinusPlusX = UM_FRAND();
		if (frMinusPlusX > 0.5f)
			m_azpAsteroid[i].TranslateX(40.0f + frRandTranslationX * 10.0f);
		else
			m_azpAsteroid[i].TranslateX(40.0f - frRandTranslationX * 10.0f);

		//Zufällige Höhe
		float frRandTranslationY = UM_FRAND();
		frRandTranslationY *= frRandTranslationY * frRandTranslationY;
		float frMinusPlusY = UM_FRAND();
		if (frMinusPlusY > 0.5f)
			m_azpAsteroid[i].TranslateYDelta(frRandTranslationY * 3.0f);
		else
			m_azpAsteroid[i].TranslateYDelta(-frRandTranslationY * 3.0f);

		//Zufällige Anordnung
		float faAsteroidRotation = UM_FARAND();
		m_azpAsteroid[i].RotateYDelta(faAsteroidRotation);

		//Zufällige Rotation
		float faAsteroidBillboardRotation = UM_FARAND();
		m_azpAsteroid[i].SetBillboardAngle(faAsteroidBillboardRotation);

		//Zufällige Größe
		float faAsteroidBillboardScaling = 0.03f + UM_FARAND() * 0.07f;
		m_azpAsteroid[i].SetBillboardScaling(faAsteroidBillboardScaling, faAsteroidBillboardScaling);

		//Asteroiden zu Billboards
		m_azpAsteroid[i].SetBillboard();
	}


	//Bullets
	m_zgBullet.Init(0.3f, &m_zmRocket);
	m_zv.SetBackfaceCullingOff();
	for (unsigned int u = 0u; u < MAX_NR_OF_BULLETS; u++)
	{
		m_zs.AddPlacement(&m_azpBullets[u]);
		m_azpBullets[u].AddGeo(&m_zgBullet);
		m_azpBullets[u].SwitchOff();
	}
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zr.Tick(fTimeDelta);

	//Earth Moon System
	m_zpEarthMoonSystem.TranslateX(55.0f);
	m_zpEarthMoonSystem.RotateYDelta(fTime*20.0f / 60.0f);

	//Light
	m_zpLight.TranslateX(10.5f);
	m_zpLight.RotateYDelta(fTime * 20.0f / 60.0f);

	//Earth
	m_zpSphereEarth.RotateY(fTime);
	m_zpSphereEarth.RotateZDelta(UM_DEG2RAD(24.0f));

	//Clouds
	m_zpSphereClouds.RotateY(fTime * 0.1f);
	m_zpSphereClouds2.RotateY(fTime * 0.23f);

	//Moon
	m_zpSphereMoon.TranslateX(5.0f);
	m_zpSphereMoon.RotateYDelta(fTime * 20.0f / 28.0f);

	//Deathstar
	m_zpSphereDeathStar.TranslateX(3.0f);
	m_zpSphereDeathStar.RotateZDelta(fTime * 20.0f / 20.0f);

	//WASD Steuerung
	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta, true);

	//Mauszeiger
	static float frx = 0.0f;
	static float fry = 0.0f;
	m_zdc.GetFractional(frx, fry, true);
	m_zoCursor.SetRect(CFloatRect(frx, fry, 0.05f, 0.05f));

	//Cursor Picking
	static bool s_bPickedSun = false;
	static bool s_bPickedEarth = false;
	static bool s_bPickedMoon = false;
	static bool s_bPickedDeathStar = false;
	static bool s_bPickedSatellit = false;
	static bool s_bPickedRocket = false;
	if (m_zdc.ButtonDownLeft())
	{
		CGeo* pzgPicked = m_zdc.PickGeoPreselected(m_zgs);
		if (pzgPicked == &m_zgSphereSun)
		{
			if (s_bPickedSun)
				m_zgSphereSun.SetMaterial(&m_zmSun);
			else
				m_zgSphereSun.SetMaterial(&m_zmPicked);
			s_bPickedSun != s_bPickedSun;
		}
		if (pzgPicked == &m_zgSphereEarth)
		{
			if (s_bPickedEarth)
				m_zgSphereEarth.SetMaterial(&m_zm);
			else
				m_zgSphereEarth.SetMaterial(&m_zmPicked);
			s_bPickedEarth != s_bPickedEarth;
		}
		if (pzgPicked == &m_zgSphereMoon)
		{
			if (s_bPickedMoon)
				m_zgSphereMoon.SetMaterial(&m_zmMoon);
			else
				m_zgSphereMoon.SetMaterial(&m_zmPicked);
			s_bPickedMoon != s_bPickedMoon;
		}
		if (pzgPicked == &m_zgSphereDeathStar)
		{
			if (s_bPickedDeathStar)
				m_zgSphereDeathStar.SetMaterial(&m_zmDeathStar);
			else
				m_zgSphereDeathStar.SetMaterial(&m_zmPicked);
			s_bPickedDeathStar != s_bPickedDeathStar;
		}
		if (pzgPicked == &m_zgSatellit)
		{
			if (s_bPickedSatellit)
				m_zgSatellit.SetMaterial(&m_zmSatellit);
			else
				m_zgSatellit.SetMaterial(&m_zmPicked);
			s_bPickedSatellit != s_bPickedSatellit;
		}
		if (pzgPicked == &m_zgRocket)
		{
			if (s_bPickedRocket)
				m_zgRocket.SetMaterial(&m_zmRocket);
			else
				m_zgRocket.SetMaterial(&m_zmPicked);
			s_bPickedRocket != s_bPickedRocket;
		}
	}

	//Asteroiden
	m_zpAsteroids.RotateY(fTime * 0.2f);
	for (int i = 0; i < 30; i++)
		m_azpAsteroid[i].RotateYDelta(fTimeDelta * UM_FRAND()*40.5f);

	//Bullets
	if (m_zdk.KeyDown(DIK_SPACE))
	{
		CHVector vCam = m_zpCamera.GetPos();

		m_azpBullets[m_uStart].Translate(vCam);
		m_azpBullets[m_uStart].SwitchOn();

		m_avBullets[m_uStart] = m_zpCamera.GetDirection();

		m_afBulletCountdown[m_uStart] = 5.0f;
		m_uStart = (m_uStart+1u)%MAX_NR_OF_BULLETS;
	}

	for (unsigned int u = m_uEnd; u != m_uStart; u = (u + 1) % MAX_NR_OF_BULLETS)
	{
		m_afBulletCountdown[u] -= fTimeDelta;
		if (m_afBulletCountdown[u] <= 0.0f)
		{
			m_azpBullets[u].SwitchOff();
			m_uEnd = (m_uEnd + 1u) % MAX_NR_OF_BULLETS;
			break;
		}
	}


	for (unsigned int u = m_uEnd; u != m_uStart; u = (u + 1) % MAX_NR_OF_BULLETS)
	{
		CHVector vDir = m_zpCamera.m_mLocal.GetDirection();
		vDir *= fTimeDelta * F_BULLET_VELOCITY;
		m_azpBullets[u].TranslateDelta(vDir);

	}
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}

