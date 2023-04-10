#pragma once
#include "Player.hpp"

struct FMinimalViewInfo
{
	Vector3 Location;
	Vector3 Rotation;
	float FOV;
};
struct FCameraCacheEntry
{
	char pad_0x0[0x10];
	FMinimalViewInfo POV;
};

class UPlayer {
private:
public:
	uintptr_t instance;
	uintptr_t mesh;
	uintptr_t root_component;
	uintptr_t instigator;
	uintptr_t PlayerState;
	Vector3 rootation;
	std::string name;
	int objectId;
	Vector3 origin;
	float health;
	float dist;
	int team;
};

class APlayerState
{
private:
public:
	uintptr_t SoldiersOnScreenSortedByNearestDistanceCache;// 0x0488
	int TeamId;// 0x0420 
};


FCameraCacheEntry cameraCache;
uintptr_t uWorld;
uintptr_t gameInstance;
uintptr_t persistentLevel;
uintptr_t localPlayerPtr;
uintptr_t localPlayer;
uintptr_t playerController;
uintptr_t pawn;
uintptr_t cameraManager;
uintptr_t actorsArray;
uintptr_t PlayerStateLocalPlayer;
uintptr_t PlayerState;
APlayerState LocalTeamId;
Vector3 Screen;
int actorsCount;
