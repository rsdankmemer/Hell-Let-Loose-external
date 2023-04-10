#pragma once
#include "driver.hpp"
#include "include.hpp"
#include "vec.h"
#include "Glob.hpp"
#include "overlay.hpp"
#include "matrix.hpp"
#include "Nameid.hpp"
#include "TypeInfo.hpp"
#include "draw.hpp"
#define M_PI 3.14159265358979323846264338327950288419716939937510

UPlayer player;
float ToMeters(float x)
{
	return x / 39.62f;
}

D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

Vector3 Screen1;

Vector3 WorldToScreen(Vector3 WorldLocation)
{
	Vector3 Screenlocation = Vector3(0, 0, 0);
	//FMinimalViewInfo CameraCacheEntry = rpm.read<FMinimalViewInfo>(PlayerCamera + CameraCache + POV);
	auto pCamera = driver.read<uintptr_t>(cameraManager);
	if (!pCamera) return { 0,0,0 };

	auto Check = driver.read<uintptr_t>(pCamera + 0x870);
	if (Check) {
		FMinimalViewInfo CameraCacheEntry = driver.read<FMinimalViewInfo>(pCamera + 0x870 );
		Vector3 Rotation = CameraCacheEntry.Rotation;
		D3DMATRIX tempMatrix = Matrix(Rotation);

		Vector3 vAxisX, vAxisY, vAxisZ;

		vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3 vDelta = WorldLocation - CameraCacheEntry.Location;
		Vector3 vTransformed = Vector3(vDelta.Dot( vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		float FovAngle = CameraCacheEntry.FOV;

		float ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
		float ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;

		Screenlocation.x = ScreenCenterX + vTransformed.z * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

		return Screenlocation;
	}
	return { 0,0,0 };

}

struct Vec4 {
	float x, y, z, w;
};

bool WorldToScreenX(Vector3 WorldLocation, FMinimalViewInfo CameraCacheL, Vector3& Screenlocation)
{

	auto POV = CameraCacheL;
	Vector3 Rotation = POV.Rotation;
	D3DMATRIX tempMatrix = Matrix(Rotation);

	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - POV.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		return false;

	float FovAngle = POV.FOV;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return true;
}


void localplayer()
{


	uWorld = driver.read<uintptr_t>(Functions::Base + 0x4151910); // Offsets::GWorld
	gameInstance = driver.read<uintptr_t>(uWorld + 0x188); // Offsets::Classes::UWorld::OwningGameInstance
	persistentLevel = driver.read<uintptr_t>(uWorld + 0x30); // Offsets::Classes::UWorld::PersistentLevel
	localPlayerPtr = driver.read<uintptr_t>(gameInstance + 0x38); // Offsets::Classes::UWorld::UGameInstance::LocalPlayers
	localPlayer = driver.read<uintptr_t>(localPlayerPtr);  // LocalPlayer lol
	playerController = driver.read<uintptr_t>(localPlayer + 0x30); // Offsets::Classes::UWorld::UGameInstance::UPlayer::PlayerController
	PlayerStateLocalPlayer = driver.read<uintptr_t>(playerController + 0x228);// Offsets::Classes::AActor::UObject::AController::PlayerState 0x250
	LocalTeamId.TeamId = driver.read<int>(PlayerStateLocalPlayer + 0x224);// Offsets::Classes::1PlayerState::Ainfo::AActor::UObject::ASQPlayerState::TeamId 0x420
	pawn = driver.read<uintptr_t>(playerController + 0x2a0); // Offsets::Classes::UWorld::UGameInstance::UPlayer::cc::AcknowledgedPawn
	cameraManager = driver.read<uintptr_t>(playerController + 0x2b8); //Offsets::Classes::UWorld::UGameInstance::UPlayer::APlayerController::PlayerCameraManager aussi offset_camera_manager
	cameraCache = driver.read<FCameraCacheEntry>(cameraManager + 0x1a60); // offset_camera_cache
	actorsArray = driver.read<uintptr_t>(persistentLevel + 0x98); // Offsets::Classes::UWorld::ULevel::UNetConnection::OwningActor
	actorsCount = driver.read<int>(persistentLevel + 0xa0); // Offsets::Classes::UWorld::ULevel::UNetConnection::MaxPacket
	for (int i = 1; i < actorsCount; i++)
	{
		uintptr_t actor = driver.read<uintptr_t>(actorsArray + i * 0x8);
		int playercount(i);
		if (actorsCount < 1) continue;
		if (!actor)
			continue;
		if (localPlayer == actor) continue;

		player.instance = actor;
		player.objectId = driver.read<int>(actor + 0x18); // offset_actor_id
		uintptr_t reoil = driver.read<uintptr_t>(pawn + 0x288);
		uintptr_t recpi = driver.read<uintptr_t>(actor + 0x338);
		uintptr_t glow = driver.read<uintptr_t>(pawn + 0x32c);
		//driver.write<int>(glow, 2);


			player.instigator = driver.read<uintptr_t>(player.instance + 0x118); // AActor::Instigator 
			player.PlayerState = driver.read<uintptr_t>(player.instigator + 0x240); // APawn::PlayerState
			player.team = driver.read<int>(player.PlayerState + 0x224); // ASQPlayerState::Teamid
			player.root_component = driver.read<uintptr_t>(player.instance + 0x130); // AActor::RootComponent
			player.origin = driver.read<Vector3>(player.root_component + 0x11c); // USceneComponent::RelativeLocation
			player.rootation = driver.read<Vector3>(player.root_component + 0x128);
			
			float dist = cameraCache.POV.Location.DistTo(player.origin);
			float DistM = ToMeters(dist);
		//	if (DistM < 125.0f) continue;
		//	std::cout << driver.read<uintptr_t>(player.PlayerState + 0xeb8);
		//	uintptr_t reveal = driver.read<uintptr_t>(actor + 0xeb8);
	//		uintptr_t Reveal_Class = driver.read<uintptr_t>(reveal + 0xb0);
		//	float viewdistance = driver.read<uintptr_t>(Reveal_Class + 0x230);
		//	Vec4 EnemyColor = driver.read<Vec4>(Reveal_Class + 0x23c);
		//	driver.write<float>(viewdistance, 0.0f);
			//driver.write<Vec4>(Reveal_Class + 0x23c, Vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

			//	player.health = driver.read<float>(actor + 0x1c18); //AActor::Uobject::ASQSolider::Health 0x1c18
			//std::string Distance = " [ " + std::to_string(int(DistM)) + "M ]";
			Vector3 Pos = WorldToScreen(player.origin);
			//std::cout << "Item [ " << GetNameById(player.objectId) << " ]\n";
			float ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
			float ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;
		//	if (dist > 100) continue;
		//	ImGui::GetOverlayDrawList()->AddText(ImVec2(Pos.x, Pos.y), ImColor(255, 255, 255, 255), "player");
			std::string PlayerName = driver.read_str(PlayerState + 0x300);
			player.health = driver.read<float>(actor + 0x7b4);
			std::string Hea = "[ " + std::to_string(int(player.health)) + "HP ]";
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (player.PlayerState)
				{
					if (player.health > 25.0f)
					{
						std::cout << GetNameById(player.objectId) << std::endl;

					}

				}
			}
			if (WorldToScreenX(player.origin, cameraCache.POV, Screen))
			{
				std::string Dist = "[ " + std::to_string(int(DistM)) + "M ]";
				if (GetNameById(player.objectId).find("AxisPlayerPawn_Anim_V2_C_CCC") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 155, 255), "Enemy");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 155, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 155, 255), Hea.c_str());


				}
				if (GetNameById(player.objectId).find("AxisPlayerPawn_Anim_V2_C_CCC") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 155, 255), "Enemy");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 155, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 155, 255), Hea.c_str());

				}
				if (GetNameById(player.objectId).find("AxisPlayerPawn_Anim_V2_C_CCC_C") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 155, 255), "Enemy");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 155, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 155, 255), Hea.c_str());

				}
				if (GetNameById(player.objectId).find("AxisPlayerPawn_Anim_V2_C_CCCck_CCC") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 155, 255), "Enemy");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 155, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 155, 255), Hea.c_str());

				}

				if (GetNameById(player.objectId).find("AlliesPlayerPawn_Anim_V2_CCCC_CC_C") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 155, 255), "Enemy");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 155, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 155, 255), Hea.c_str());

				}

				if (GetNameById(player.objectId).find("AlliesPlayerPawn_Anim_V2_CCC_V2_CC") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 155, 255), "Enemy");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 155, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 155, 255), Hea.c_str());

				}
				if (GetNameById(player.objectId).find("AxisPlayerPawn_Anim_V2_C_CCCC_CC_C") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 155, 255), "Enemy");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 155, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 155, 255), Hea.c_str());

				}


				if (GetNameById(player.objectId).find("AxisPlayerPawn_Anim_V2_Cck_Cck_CCC") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 155, 255), "Enemy");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 155, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 155, 255), Hea.c_str());

				}

			}
			if (WorldToScreenX(player.origin, cameraCache.POV, Screen))
			{
				
				std::string Dist = "[ " + std::to_string(int(DistM)) + "M ]";

				if (GetNameById(player.objectId).find("AlliesPlayerPawn_Anim_V2_C") != std::string::npos) {
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y), ImColor(0, 255, 0, 255), "Team");
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 10), ImColor(0, 255, 0, 255), Dist.c_str());
					ImGui::GetOverlayDrawList()->AddText(ImVec2(Screen.x, Screen.y + 25), ImColor(0, 255, 0, 255), Hea.c_str());

				}
				
			}
			
			
			

		
	}

}
