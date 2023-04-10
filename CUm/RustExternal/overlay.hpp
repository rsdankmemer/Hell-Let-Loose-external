#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_win32.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi")
#include "Player.hpp"
#include <d3d9.h>
#include "imgui/imgui_impl_dx9.h"
#pragma comment(lib, "d3d9.lib")
#pragma warning(disable : 4838)
#pragma warning(disable : 4244)
#include <d3dx9core.h>
#include "draw.hpp"
#include "Glob.hpp"
#include "xor.hpp"
#include <D3dx9tex.h>
HWND hwnd;




namespace misc {
	bool InstantAim = true;
}
#pragma comment(lib, "d3dx9.lib")
bool amenu = false;
HWND GameWnd = 0, MyWnd = 0;
RECT GameRect = {};

IDirect3D9Ex* p_Object = nullptr;
extern IDirect3DDevice9Ex* p_Device;
D3DPRESENT_PARAMETERS p_Params = { 0 };
extern LPDIRECT3DDEVICE9 d3ddev;
extern ID3DXLine* dx_Line;
extern ID3DXFont* dx_Font;
LPDIRECT3D9 d3d;
float ColorsVisuals[4] = { 127, 127, 127, 255 };

ImVec2 menuSize = ImVec2(850, 600);

float width = 1920.f;
float height = 1080.f;

template<typename T> void SetColor(T value, float R, float G, float B, float A) {
	value[0] = R; value[1] = G; value[2] = B; value[3] = A;
}
void Style()
{
	// Dark Theme
	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.009f, 0.009f, 0.009f, 0.50f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.2f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.0f, 0.0f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.3f, 0.3f, 0.3f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.10f, 1.80f, 0.1f, 0.51f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.96f, 0.96f, 0.98f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	//ImGui::PopStyleColor();
	//style->WindowPadding = ImVec2(0.00f, 8.00f);
//	style->FramePadding = ImVec2(0.00f, 6.00f);
	style->WindowBorderSize = 0.50f;
	//style->ChildBorderSize = 0.00f;
	//style->PopupBorderSize = 1.00f;
	style->FrameBorderSize = 1.00f;
	style->WindowRounding = 5.00f;
	style->ChildRounding = 1.00f;
	style->FrameRounding = 5.00f;
	style->WindowTitleAlign = ImVec2(0.46f, 0.50f);


}


void Line(int newId)
{
	std::string id = (_("imguipp_line_").c_str() + std::to_string(newId));
	ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
	{
		ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
		ImGui::Separator();
		ImGui::EndChild();
	}
	ImGui::PopStyleColor();
}
void CenterTextEx(const char* text, float width, int lineId, bool separator)
{
	if (text == nullptr)
		return;

	ImGui::Spacing();
	ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
	ImGui::Text(text);
	ImGui::Spacing();

	if (separator)
		Line(lineId);
}



inline void __fastcall set_window_to_target()
{
	while (true)
	{
		GameWnd = FindWindowA(0, (_("OBS 28.1.2 (64-bit, windows) - Profile: Untitled - Scenes: Untitled").c_str()));
		if (GameWnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(GameWnd, &GameRect);

			width = GameRect.right - GameRect.left;
			height = GameRect.bottom - GameRect.top;

			DWORD dwStyle = GetWindowLong(GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				height -= 39;
			}

			MoveWindow(MyWnd, GameRect.left - 2.f, GameRect.top - 2.f, width + 2.f, width + 2.f, true);
		}
		else exit(8);
	}
}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
inline auto __fastcall wnd_proc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) -> LRESULT
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		if (p_Device != 0)
		{
			p_Device->EndScene();
			p_Device->Release();
		}

		if (p_Object != 0)
		{
			p_Object->Release();
		}

		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (p_Device != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Params.BackBufferWidth = LOWORD(lParam);
			p_Params.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = p_Device->Reset(&p_Params);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}
void Update()
{
	HWND activeWnd = GetForegroundWindow();
	if (activeWnd == MyWnd)
	{
		HWND hwndtest = GetWindow(activeWnd, GW_HWNDPREV);
		SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	if (GetAsyncKeyState(VK_UP) & 1)
	{
		amenu = !amenu;
		std::cout << "up";

		if (amenu)
		{
			SetWindowLongA(MyWnd, GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
		}
		else
		{
			// Add layer flag so we cannot click through to application
			SetWindowLongA(MyWnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
		}
	}
}
inline auto __fastcall setup_window() -> void
{
	WNDCLASSEX wClass =
	{
		sizeof(WNDCLASSEX),
		0,
		wnd_proc,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		"Rust",
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	if (!RegisterClassEx(&wClass))

		exit(1);

	//R6Game
	GameWnd = FindWindowA(("UnrealWindow"), NULL); //
	if (GameWnd)
	{
		GetClientRect(GameWnd, &GameRect);
		POINT xy;
		ClientToScreen(GameWnd, &xy);
		GameRect.left = xy.x;
		GameRect.top = xy.y;

		width = GameRect.right;
		height = GameRect.bottom;
	}
	else exit(2);

	MyWnd = CreateWindowExA(0, wClass.lpszClassName, ("¬¬¬¬¬¬¬¬¬¬"), WS_POPUP | LWS_TRANSPARENT | WS_VISIBLE, GameRect.left - 2.f, GameRect.top - 2.f, width + 2.f, height + 2.f, 0, 0, 0, 0);


	MARGINS Margin = { GameRect.left - 2.f, GameRect.top - 2.f, width + 2.f, height + 2.f };
	DwmExtendFrameIntoClientArea(MyWnd, &Margin);

	SetWindowLongA(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	ShowWindow(MyWnd, SW_SHOW);
	UpdateWindow(MyWnd);
}
inline auto setup_directx(HWND hWnd) -> int
{
	Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object);

	D3DPRESENT_PARAMETERS p_Params;

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = width + 2.f;
	p_Params.BackBufferHeight = height + 2.f;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	p_Params.MultiSampleQuality = DEFAULT_QUALITY;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
	{
		p_Object->Release();
		exit(4);
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.FontDefault = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ntailu.ttf", 15.0f);






	if (!dx_Line)
	{
		D3DXCreateLine(p_Device, &dx_Line);
	}

	D3DXCreateFont(p_Device, 18, 0, FW_LIGHT, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "ntailu", &dx_Font);


	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(p_Device);
	ImGui_ImplDX9_NewFrame();
	Style();



	p_Object->Release();
}
enum
{
	TAB_VISUALS = 0,
	TAB_AIMBOT
};



static float isRed = 0.0f, isGreen = 0.0f, isBlue = 0.0f;

ImVec4 isRGB = ImVec4(isRed, isGreen, isBlue, 1.0f);







int FrameRate()
{
	static int iFps, iLastFps;
	static float flLastTickCount, flTickCount;
	flTickCount = clock() * 0.001f;
	iFps++;
	if ((flTickCount - flLastTickCount) >= 1.0f) {
		flLastTickCount = flTickCount;
		iLastFps = iFps;
		iFps = 0;
	}
	return iLastFps;
}
void watermark()
{
	static std::chrono::time_point<std::chrono::steady_clock> oldTime = std::chrono::high_resolution_clock::now();
	static int fps; fps++;

	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::seconds{ 1 }) {
		oldTime = std::chrono::high_resolution_clock::now();
		fps = 0;
	}


	float rainbowSpeed = 0.0001;
	static float staticHue = 0;
	staticHue -= rainbowSpeed;
	ImColor cRainbow;
	if (staticHue < -1.f) staticHue += 1.f;
	for (int i = 0; i < width; i++)
	{
		float hue = staticHue + (1.f / (float)width) * i;
		if (hue < 0.f) hue += 1.f;
		cRainbow = ImColor::HSV(hue, 1.f, 1.f);
	}

	ImGui::SetNextWindowSize(ImVec2(200, 100));
	ImGui::SetWindowPos(ImVec2(5, 0));
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | WS_EX_TOPMOST | CS_CLASSDC | WS_EX_TOPMOST | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
	{
		ImGui::Text("Unkowncheats Hell Let Loose 2 Hour External ¬ vMt#4759 "); ImGui::SameLine(); ImGui::TextColored(cRainbow, " ~ "); ImGui::SameLine();
		ImGui::Text("FPS %d", fps);
		ImGui::Spacing();
		
		ImGui::End();


	}
}


#include <chrono>

int tab;

float test;



void RenderMenu()
{
	ImGuiIO& io = ImGui::GetIO();

	int switchTabs = 3;
	watermark();

	float rainbowSpeeda = 0.0001;
	static float staticHuea = 0;
	staticHuea -= rainbowSpeeda;
	ImColor cRainbowa;
	if (staticHuea < -1.f) staticHuea += 1.f;
	for (int i = 0; i < width; i++)
	{
		float huea = staticHuea + (1.f / (float)width) * i;
		if (huea < 0.f) huea += 1.f;
		cRainbowa = ImColor::HSV(huea, 1.f, 1.f);
	}
	if (GetAsyncKeyState(VK_UP) & 1)
		amenu = !amenu;
	if (amenu)
	{


		//ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2.f - menuSize.x / 2.f, io.DisplaySize.y / 2.f - menuSize.y / 2.f), ImGuiCond_Once);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 13.f);
		ImGui::SetWindowSize(ImVec2(380.0f, 700.0f));
		ImGui::SetNextWindowSize(ImVec2(600.0f, 425.0f));
		ImGui::Begin((_("Private Cheat").c_str()), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		{

			ImGui::SetCursorPos(ImVec2(250, 1));
			ImGui::TextColored(cRainbowa, "[Squad]");

			ImGui::BeginChild("##LeftSide", ImVec2(125, 400), true);

			if (ImGui::Button("Main Visuals", ImVec2(100, 50)))
			{
				tab = 1;
			}
			if (ImGui::Button("Aimbot", ImVec2(100, 50)))
			{
				tab = 4;
			}
			ImGui::Spacing();
			if (ImGui::Button("Expoits", ImVec2(100, 50)))
			{
				tab = 5;

			}
			ImGui::Spacing();
			if (ImGui::Button("Misc", ImVec2(100, 50)))
			{
				tab = 6;
			}
			ImGui::Spacing();
			if (ImGui::Button("Config", ImVec2(100, 50)))
			{
				tab = 7;
			}

			ImGui::EndChild();
			ImGui::SameLine();


			if (tab == 1)
			{
				ImGui::SameLine();
				ImGui::BeginChild("##MainTaaaaab", ImVec2(550, 400));

				ImGui::TextColored(cRainbowa, "->"); ImGui::SameLine(); ImGui::Text("Player Visuals"); ImGui::SameLine(); ImGui::TextColored(cRainbowa, "<-"); ImGui::SameLine(); ImGui::Spacing();
				ImGui::Spacing();



				ImGui::EndChild();

			}

			if (tab == 2)
			{
				ImGui::BeginChild("##MainTab", ImVec2(550, 400));

				ImGui::TextColored(cRainbowa, "->"); ImGui::SameLine(); ImGui::Text("Ore Visuals"); ImGui::SameLine(); ImGui::TextColored(cRainbowa, "<-"); ImGui::SameLine(); ImGui::Spacing();
			


				ImGui::EndChild();

			}



			if (tab == 3)
			{
				ImGui::BeginChild("##MainTab", ImVec2(550, 400));

				ImGui::TextColored(cRainbowa, "->"); ImGui::SameLine(); ImGui::Text("Loot Visuals"); ImGui::SameLine(); ImGui::TextColored(cRainbowa, "<-"); ImGui::SameLine(); ImGui::Spacing();
				


				ImGui::EndChild();

			}


			if (tab == 4)
			{
				ImGui::BeginChild("##MainTab", ImVec2(550, 400));

				ImGui::TextColored(cRainbowa, "->"); ImGui::SameLine(); ImGui::Text("Aimbot"); ImGui::SameLine(); ImGui::TextColored(cRainbowa, "<-"); ImGui::SameLine(); ImGui::Spacing();
			
				ImGui::EndChild();


			}

			if (tab == 5)
			{
				ImGui::BeginChild("##MainTab", ImVec2(550, 400));

				ImGui::TextColored(cRainbowa, "->"); ImGui::SameLine(); ImGui::Text("Player Visuals"); ImGui::SameLine(); ImGui::TextColored(cRainbowa, "<-"); ImGui::SameLine(); ImGui::Spacing();
			

				ImGui::EndChild();

			}

		}


	}

}



int ab;
int ac;
int ad;
void DrawCorneredBox(ImVec2 headPos, ImVec2 pos, const ImU32 color, int thickness) {
	int dist = pos.y - headPos.y;

	// these are the corners, I dont wanna write a background color because im lazy but i will if i have too

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(headPos.x - dist / 4, headPos.y), ImVec2(headPos.x - dist / 4 + dist / 5, headPos.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(headPos.x + dist / 4, headPos.y), ImVec2(headPos.x + dist / 4 - dist / 5, headPos.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(headPos.x - dist / 4, headPos.y), ImVec2(headPos.x - dist / 4, headPos.y + dist / 5), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(headPos.x + dist / 4, headPos.y), ImVec2(headPos.x + dist / 4, headPos.y + dist / 5), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos.x - dist / 4, pos.y), ImVec2(pos.x - dist / 4 + dist / 5, pos.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos.x + dist / 4, pos.y), ImVec2(pos.x + dist / 4 - dist / 5, pos.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos.x - dist / 4, pos.y), ImVec2(pos.x - dist / 4, pos.y - dist / 5), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos.x + dist / 4, pos.y), ImVec2(pos.x + dist / 4, pos.y - dist / 5), color, thickness);
}
void Linea(ImVec2 pos, ImVec2 size, ImU32 color, float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(pos, size, color, thickness);
}

inline auto __fastcall main_loop() -> WPARAM
{
	static RECT old_rc;
	static MSG Message;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessageA(&Message, MyWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageA(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (GetAsyncKeyState(VK_END) & 1)
			exit(8);

		if (hwnd_active == GameWnd)
		{
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			width = rc.right;
			height = rc.bottom;

			p_Params.BackBufferWidth = width + 2.f;
			p_Params.BackBufferHeight = height + 2.f;
			SetWindowPos(MyWnd, 0, xy.x, xy.y, width + 2.f, height + 2.f, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}


		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		Style();
		localplayer();
		Update();
		RenderMenu();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0)); // Invisible 
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		ImGui::Begin((_("##scene").c_str()), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
		//DrawStrokeText(xa /2 , ya/2, _("o").c_str());
		float xs = GetSystemMetrics(SM_CXSCREEN) - 175, ys = 200;
		float sa = GetSystemMetrics(SM_CXSCREEN);



		
		//Vector3 Screen;

		    
		

		//DrawCorneredBox(ImVec2(Screen.x, Screen.y), ImVec2(Screen1.x, Screen1.y), ImColor(255.0f, 0.0f, 0.0f, 1.0f), 3);
		Linea(ImVec2(sa, 1080), ImVec2(Screen.x, Screen.y), ImColor(255.0f, 100.f, 100.f, 1.0f), 1);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(xs, ys - 150), ImVec2(xs, ys + 150), ImColor(0.f, 0.f, 0.f, 1.f), 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(xs - 150, ys), ImVec2(xs + 150, ys), ImColor(0.f, 0.f, 0.f, 1.f), 3);
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(xs - 1, ys - 1), ImVec2(xs + 2, ys + 2), ImColor(1.0f, 1.0f, 0.0f), 1.5f);
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(xs - 150, ys - 150), ImVec2(xs + 150, ys + 150), ImColor(0.9f, 0.9f, 0.9f, 0.15f), 2);
		ImGui::GetWindowDrawList()->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);

		ImGui::EndFrame();
		p_Device->SetRenderState(D3DRS_ZENABLE, false);
		p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

		p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		if (p_Device->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			p_Device->EndScene();
		}

		if (p_Device->Present(0, 0, 0, 0) == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Device->Reset(&p_Params);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (p_Device != 0)
	{
		p_Device->EndScene();
		p_Device->Release();
	}

	if (p_Object != 0)
	{
		p_Object->Release();
	}

	DestroyWindow(MyWnd);
	return Message.wParam;
}