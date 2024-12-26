//---------------------------------------------------------------------------

#ifndef libximc_loadH
#define libximc_loadH
//---------------------------------------------------------------------------
#include "ximc.h"

extern HINSTANCE ximcdll;   //dll handle declaration

/* dll function pointer types and declartion of corresponding
   function pointer variables
*/
typedef  void __stdcall (*pfximc_version)(char*);
extern pfximc_version _ximc_version;
typedef device_t __stdcall (*pfopen_device)(const char*);
extern pfopen_device _open_device;
typedef result_t __stdcall (*pfclose_device)(device_t*);
extern pfclose_device _close_device;
typedef result_t __stdcall (*pfcommand_movr)(device_t, int, int);
extern  pfcommand_movr _command_movr;
typedef result_t __stdcall (*pfcommand_wait_for_stop)(device_t, uint32_t);
extern pfcommand_wait_for_stop _command_wait_for_stop;
typedef result_t __stdcall (*pfget_move_settings) (device_t, move_settings_t*);
extern pfget_move_settings _get_move_settings;
typedef result_t __stdcall (*pfset_move_settings) (device_t, move_settings_t*);
extern pfset_move_settings _set_move_settings;

extern result_t init();
extern result_t deinit();



#endif
