/**
 *  @file   InputAspect.cpp
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#include <Aspects/InputAspect.h>
#include <Managers/InputMgr.h>

const float InputAspect::KEY_TIME = 0.5f;

InputAspect::InputAspect(PlayerEntity381* ent, AspectType aspectType) : Aspect((Entity381*) ent, aspectType)
{
    m_KeyboardReference = ent->m_Engine->m_InputMgr->GetKeyboardReference();
    m_PlayerEntity = ent;
    m_KeyboardTimer = KEY_TIME;
}

InputAspect::~InputAspect()
{
    
}


void InputAspect::Tick(float dt)
{
    m_KeyboardTimer -= dt;
    
    if(m_KeyboardTimer < 0)
    {
        m_KeyboardTimer = KEY_TIME;
        for(auto iter = m_PlayerEntity->m_MappedInputs.begin(); iter != m_PlayerEntity->m_MappedInputs.end(); iter++)
        {
            if(m_KeyboardReference->isKeyDown(iter->first))
            {
                switch(iter->second)
                {
                case SHOOT:
                    break;
                case BLOCK:
                    break;
                case EJECT:
                    break;
                    
                case PITCH_UP:
                    m_PlayerEntity->m_DesiredPitch += m_PlayerEntity->m_PitchRate;
                    break;
                case PITCH_DOWN:
                    m_PlayerEntity->m_DesiredPitch -= m_PlayerEntity->m_PitchRate;
                    break;
                case YAW_LEFT:
                    m_PlayerEntity->m_DesiredYaw -= m_PlayerEntity->m_YawRate;
                    break;
                case YAW_RIGHT:
                    m_PlayerEntity->m_DesiredYaw += m_PlayerEntity->m_YawRate;
                    break;
                case ROLL_LEFT:
                    m_PlayerEntity->m_DesiredRoll -= m_PlayerEntity->m_RollRate;
                    break;
                case ROLL_RIGHT:
                    m_PlayerEntity->m_DesiredRoll += m_PlayerEntity->m_RollRate;
                    break;
                    
                case SLOW_DOWN:
                    m_PlayerEntity->m_DesiredSpeed -= m_PlayerEntity->m_Acceleration;
                    break;
                    
                case SPEED_UP:
                    m_PlayerEntity->m_DesiredSpeed += m_PlayerEntity->m_Acceleration;
                    break;
    
                case MOVE_FORWARD:
                    break;
                case MOVE_BACKWARD:
                    break;
                case MOVE_LEFT:
                    break;
                case MOVE_RIGHT:
                    break;
                case MOVE_UP:
                    break;
                case MOVE_DOWN:
                    break;
    
                case QUIT_GAME:
                    break;
                case TOGGLE_PAUSE:
                    break;
                case TOGGLE_DEBUG:
                    break;
                    
                default:
                    std::cerr << "WARNING: ACTION NOT DEFINIED FOR ENTITY: " << m_PlayerEntity->m_Name << std::endl;
                }
            }
        }
    }
}
