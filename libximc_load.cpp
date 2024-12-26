#include <fmx.h>
#include <stdio.h>

#include "libximc_load.h"
/*
Function pointers definitions
*/
pfximc_version _ximc_version = nullptr;
pfopen_device _open_device;
pfclose_device _close_device;
pfcommand_movr _command_movr;
pfcommand_wait_for_stop _command_wait_for_stop;
pfget_move_settings _get_move_settings;
pfset_move_settings _set_move_settings;

HINSTANCE ximcdll; // DLL handle definition
/*
	The function of initializing the library
	and getting pointers to all the necessary functions
	For reliable operation,
	it is necessary to check the availability of all the functions used
*/

result_t init(void)
{
	// Opening libximc.dll

	ximcdll = LoadLibrary("libximc.dll");
	int error = GetLastError();
	if (ximcdll == NULL) {
		printf("Failed to load libximc.dll.Press a key to exit.\n");
		getchar();
		return result_nodevice;
	}
	// Getting the address the function ximc_version
	if ((_ximc_version = (pfximc_version)GetProcAddress(ximcdll, "ximc_version")) == NULL) {
		printf("\nFailed to call the function ximc_version\n");
		return result_nodevice;
	}
	// Getting the address the function  open_device
	if ((_open_device = (pfopen_device)GetProcAddress(ximcdll, "open_device")) == NULL) {
		printf("\nFailed to call the function open_device\n");
		return result_nodevice;
	}
	// Getting the address the function get_move_settings
	if ((_get_move_settings = (pfget_move_settings)GetProcAddress(ximcdll, "get_move_settings")) == NULL) {
		printf("\nFailed to call the function get_move_settings\n");
		return result_nodevice;
	}
	if ((_set_move_settings = (pfget_move_settings)GetProcAddress(ximcdll, "set_move_settings")) == NULL) {
		printf("\nFailed to call the function set_move_settings\n");
		return result_nodevice;
	}
	if ((_command_movr = (pfcommand_movr)GetProcAddress(ximcdll, "command_movr")) == NULL) {
		printf("\nFailed to call the function command_movr\n");
		return result_nodevice;
	}
	if ((_command_wait_for_stop = (pfcommand_wait_for_stop)GetProcAddress(ximcdll, "command_wait_for_stop")) == NULL) {
		printf("\nFailed to call the function command_wait_for_stop\n");
		return result_nodevice;
	}
	if ((_close_device = (pfclose_device)GetProcAddress(ximcdll, "close_device")) == NULL) {
		printf("\nFailed to call the function close_device\n");
		return result_nodevice;
	}
    
	return result_ok;
}

/*
	Clearing memory after using the library
*/
result_t deinit(void)
{
	FreeLibrary(ximcdll);
	return result_ok;

}

