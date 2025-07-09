/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: ExitFunc */
#define  PANEL_CANVAS                     2       /* control type: canvas, callback function: CanvasFunc */
#define  PANEL_TIMER                      3       /* control type: timer, callback function: TimerFunc */

#define  PANEL_2                          2       /* callback function: ExitFunc2 */
#define  PANEL_2_PICTURE                  2       /* control type: picture, callback function: (none) */
#define  PANEL_2_START                    3       /* control type: pictButton, callback function: StartNew */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CanvasFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ExitFunc(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ExitFunc2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartNew(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif