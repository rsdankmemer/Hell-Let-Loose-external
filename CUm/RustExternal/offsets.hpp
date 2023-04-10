#pragma once
#include "Glob.hpp"
#include "include.hpp"

namespace offsets {
	uintptr_t BaseEntityType = 0x3633500;
	


	uintptr_t Movment = 0x4F8;
	auto playerModel = 0x4D0; // PlayerModel
	auto collision = 0x500; // BaseCollision
	auto _lookingAt = 0x508; //GameObject
	auto _lookingAtEntity = 0x510; //baseEntity
	auto wasSleeping = 0x531; //bool
	auto currentTeam = 0x5A0; // ulong baseEntity
	auto clientTeam = 0x5A8; // PlayerTeam
	auto clActiveItem = 0x5D8; //item id correct
	auto modelState = 0x600; //module state
	auto mounted = 0x608; // EntityRef
	auto maxProjectileID = 0x640; //int weapon projectile 
	auto serverTickRate = 0x64C; // int
	auto clientTickRate = 0x650; // int
	auto serverTickInterval = 0x654; //float
	auto clientTickInterval = 0x658; // float
	auto drownEffect = 0x688; // Game Object Reference
	auto playerFlags = 0x690; // BasePlayer.PlayerFlags
	auto invintory = 0x6A0;  //Player Invintory
	auto playerCollider = 0x6C0; // Capsule Collider
	auto Held = 0x98; // Player belt
	auto userID = 0x6D8; // ulong base player
	auto UserIDString = 0x6E0; //string user
	auto clothingBlocksAiming = 0x760; //bool
	auto clothingMoveSpeedReduction = 0x764; //float
	auto clothingWaterSpeedBonus = 0x768; // flaot 
	auto clothingAccuracyBonus = 0x76C; //float
	auto containerBelt = 0x6C8;
	auto itemList = 0x38;

	auto groundAngle = 0xC4;
	auto oGravityMultiplier = 0x84;
	auto oclothingWaterSpeedBonus = 0x768;
	auto gravityTestRadius = 0x80;
	auto PlayerEyes = 0x698;
	auto automatic = 0x290;
	auto FlagOnGround = 4;
	auto RecoliPropitys = 0x2E0;
	auto RecoilYawMin = 0x18;
	auto RecoilYawMax = 0x1C;
	auto RecoilPitchMax = 0x24;
	auto RecoilPitchMin = 0x20;
	auto capsuleHeight = 0x68;
	auto capsuleCenter = 0x6C;
	auto groundAngleNew = 0xC8;
}