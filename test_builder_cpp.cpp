#pragma argsused

#include <fmx.h>
#include <stdio.h>

#include "libximc_load.h"

int main(int argc, char* argv[])
{
	result_t result =  init();
	if (result != result_ok)
		return -1;
	 
	// Reading the library version
	char  ximcversion[32];
	_ximc_version(ximcversion);
	printf("%s\n", ximcversion);

	//  Opening the device
	device_t device = _open_device("xi-com:\\\\.\\COM4");
	if (device == device_undefined) {
		printf( "\nOpening device error\nPress a key to exit." );
		getchar();
		return -1;
	}

	move_settings_t move_settings;
	// Reading Motion settings
	result = _get_move_settings(device, &move_settings);
	if (result != result_ok)
		printf( "\nerror get_move_settings\n" );
	else
		printf("\nSpeed = %d\n", move_settings.Speed);


	// Speed change
	move_settings.Speed = 1000;
	// Recording motion settings
	result = _set_move_settings(device, &move_settings);
	if (result != result_ok)
		printf( "\nerror set_move_settings\n" );
	else
		printf("\nSet Speed = %d\n", move_settings.Speed);

	// Movement offset by DeltaPosition
	int DeltaPosition = 1000;
	int uDeltaPosition = 0;
	result = _command_movr(device, DeltaPosition, uDeltaPosition);
	if (result != result_ok)
		printf( "\nerror command_movr\n" );
	// Waiting for the end of the movement function command_wait_for_stop
	// Frequency of monitoring
	uint32_t time = 50;
	result = _command_wait_for_stop(device, time);
	if (result != result_ok)
		printf( "\nerror command_wait_for_stop\n" );

	// Getting the address and executing the function close_device
	result = _close_device(&device);
	if (result != result_ok)
		printf( "\nerror close device\n" );
	printf("\nThat's all.Press a key to exit.\n");
	getchar();
	deinit();
	
	return result_ok;
}
