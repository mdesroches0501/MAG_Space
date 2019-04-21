/**
 *  @file   Actions.h
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#ifndef INC_UTILITIES_ACTIONS_H_
#define INC_UTILITIES_ACTIONS_H_

#include <map>
#include <string>

enum Actions
{
	SHOOT,
	BLOCK,
	EJECT,

	PITCH_UP,
	PITCH_DOWN,
	YAW_LEFT,
	YAW_RIGHT,
	ROLL_LEFT,
	ROLL_RIGHT,

	SLOW_DOWN,
	SPEED_UP,
	
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,

	QUIT_GAME,
	TOGGLE_PAUSE,
	TOGGLE_DEBUG,
};

extern std::map<std::string, Actions> ActionMap;


#endif /* INC_UTILITIES_ACTIONS_H_ */
