#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_
#include <stdint.h>

/*********************************************
@brief: State Machine of flow program
**********************************************/
typedef enum
{
    DEFAULT =0,
    MAIN    =1,
    AUTO_SEARCHING,
    SETUP_MODE,
    SELECT_CHANNEL,
    SAVE_FREQUENCY,
    MUTE_MODE,
    RUN_FREQ_SELECTED
}stateProgram;

/*********************************************
@brief: Mode defaulf
@param: None
@return: State Default
**********************************************/

stateProgram modeDefault();
/*********************************************
@brief: Mode Main
@param: None
@return: State Main
**********************************************/
stateProgram modeMain();

/*********************************************
@brief: Mode auto-searching
@param: None
@return: State auto search
**********************************************/
stateProgram modeAutoSearch();

/*********************************************
@brief: Mode setup frequency
@param: None
@return: State setup
**********************************************/
stateProgram modeSetup();

/*********************************************
@brief: Mode select channel
@param: frequency of channel
@return: State select channel
**********************************************/
stateProgram modeSelectChannel(float freq);

/*********************************************
@brief: Mode run select channel
@param: Point to array of frequencys are saved
@param: Index of array
@return: State 
**********************************************/
stateProgram modeRunFreqSelected(float* freqCurrent,int count);

/*********************************************
@brief: Mode select channel
@param1: frequency current
@param2: Pointer to array of frequencys is saved
@param2: Index of frequency in array
@return: None
**********************************************/
void modeSaveFreqCurrent(float freq,float* freqCurrent,int count);

/*********************************************
@brief: Mode mute
@param1: frequency of channel
@param2: statusMute
@return: None
**********************************************/
void modeMute(float freq,uint32_t statusMute);
#endif /*_STATE_MACHINE_H_*/