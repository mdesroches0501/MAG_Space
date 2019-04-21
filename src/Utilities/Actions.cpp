/**
 *  @file   Actions.cpp
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */
#include <Utilities/Actions.h>

std::map<std::string, Actions> ActionMap = 
{
    {"SHOOT", Actions::SHOOT},
    {"BLOCK", Actions::BLOCK},
    {"EJECT", Actions::EJECT},

    {"PITCH_UP", Actions::PITCH_UP},
    {"PITCH_DOWN", Actions::PITCH_DOWN},
    {"YAW_LEFT", Actions::YAW_LEFT},
    {"YAW_RIGHT", Actions::YAW_RIGHT},
    {"ROLL_LEFT", Actions::ROLL_LEFT},
    {"ROLL_RIGHT", Actions::ROLL_RIGHT},

    {"SLOW_DOWN", Actions::SLOW_DOWN},
    {"SPEED_UP", Actions::SPEED_UP},

    {"MOVE_FORWARD", Actions::MOVE_FORWARD},
    {"MOVE_BACKWARD", Actions::MOVE_BACKWARD},
    {"MOVE_LEFT", Actions::MOVE_LEFT},
    {"MOVE_RIGHT", Actions::MOVE_RIGHT},
    {"MOVE_UP", Actions::MOVE_UP},
    {"MOVE_DOWN", Actions::MOVE_DOWN},

    {"QUIT_GAME", Actions::QUIT_GAME},
    {"TOGGLE_PAUSE", Actions::TOGGLE_PAUSE},
    {"TOGGLE_DEBUG", Actions::TOGGLE_DEBUG},
};


