#include <iostream>
#include "driver.hpp"
#include "draw.hpp"
#include "overlay.hpp"
#include "Glob.hpp"


int main() {

	if (function.setup())
		std::cout << _("[+] Function Setup Successful\n").c_str();

	if (!function.setup()) {
		driver.set_pid(_("HLL-Win64-Shipping.exe").c_str());
		if (driver.get_pid()) {
			MessageBoxA(NULL, _("Please have the game closed before you launch").c_str(), _("").c_str(), 0);
			exit(2);
		}
	}


	if (!driver.is_mapped()) std::cout << _("[-] Driver Is Not Mapped or Is Not Mapped Properly\n").c_str();
	else std::cout << _("[+] Driver Mapped | Loaded\n").c_str();

	while (driver.get_pid() == NULL) {
		driver.set_pid(_("HLL-Win64-Shipping.exe").c_str());
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	printf(_("Found Game | PID %u\nPlease press insert once you are in the game's menu").c_str(), driver.get_pid());
	driver.get_module_base(_("HLL-Win64-Shipping.exe").c_str());
	Functions::Base = driver.get_base();
	std::cout << Functions::Base;
	



	system("cls");
	system("color 4");
	std::cout << "Free Unkowncheats Hell Let Loose external + driver Made by vMt#4759 2 hour project hope you enjoy!";


	setup_window();

	setup_directx(MyWnd);

	while (true)
	{
		ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
		ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;
		main_loop();
	}
}
	
