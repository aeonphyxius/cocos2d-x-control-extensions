//
//
// Class:		CCProgressTimerMulti
// Green Turtle Games
// Author:		Alejandro Santiago
// Email:		alejandro@aeonphyxius.com
// Description: Extension for CCProgressTimer in order to use different sprites depending
//				on the current percentage. For example use a different progress bar sprite
//				for 0%-25%, 25%-50%, 50%-75% and 75%-100%
//				This class can be used as a normal CCProgressTimer object in Cocos2d-X
//				
//
#ifndef __PROGRESSTIMER_MULTI_H__
#define __PROGRESSTIMER_MULTI_H__

#include "cocos2d.h"
#include "cocos2dx-ext\CCPointer.h"

class ProgressStates;

using namespace std;		
using namespace cocos2d;	

class CCProgressTimerMulti : public CCProgressTimer
{
public:
	
	/**
    * CCProgressTimerMulti	Default constructor. Will initialize the current state values to 
    *						non-usable values, to be overrided when first state is added
    *     
    */
	CCProgressTimerMulti();

	/**
    * CCProgressTimerMulti	clean up the map of states and exit    
    *     
    */
	~CCProgressTimerMulti();
	
	/**
    * addGameTime	Adding a new state, implies defining the upper and lower limits values. Meaning
	*				that when we set the percentage, this should be between those values in order for
	*				this state to be active. 
    * 
    * @param    _lowerLimit - New state's lower limit. Minimum percentage value for this state
	*
	* @param    _upperLimit - New state's upper limit. Maximun percentage value for this state
    *           
    * @param    _spriteName - Sprite's texture name. Image to be used as a progress bar for this state
	*
	*/
	void addState (const float _lowerLimit,const float _upperLimit,const string _spriteName);
	

	/**
    * addGameTime	Adding a new state, implies defining the upper and lower limits values. Meaning
	*				that when we set the percentage, this should be between those values in order for
	*				this state to be active. 
    * 
    * @param    _lowerLimit - New state's lower limit. Minimum percentage value for this state
	*
	* @param    _upperLimit - New state's upper limit. Maximun percentage value for this state
    *           
    * @param    _spriteName - Sprite's texture name. Image to be used as a progress bar for this state
	*
	* @param    _alpha - Sprite's alpha (opacity)
	*
    */
	void addState (const float _lowerLimit,const float _upperLimit,const string _spriteName,const int _alpha);
	

	/**
    * setPercentage	This function hiddes the CCProgressTimer::setPercentage in order to perform the check of
	*				the given percentage. If it is between the limits, we proceed to call CCProgressTimer::setPercentage.
	*				Otherwise, tries to find the correct state, make it as the current state, and call CCProgressTimer::setPercentage.
    * 
    * @param    _percentage - current value to be displayed in this progress bar. Used to check the state    
    *
    */
	void setPercentage (float _percentage);

private:
	/* Collection containing all states for this Progress bar */
	map <int, ProgressStates> * m_states;

	/* The current state. Will be used to monitor if we have to have to change or not*/
	int currState;
	
	/* The current state's lower limit. Below this value, another state should be used */
	float currLowerLimit;
	
	/* The current state's lower limit. Above this value, another state should be used */
	float currUpperLimit;
};

class ProgressStates
{
public:
	/* The sprite to be used in the CCProgressTimer when the current state is active */
	CCPointer <CCSprite> m_stateSprite; 
	
	/* The current state lower limit */
	float lowerLimit; 
	
	/* The current state upper limit */
	float upperLimit; 
};

#endif  // __PROGRESSTIMER_MULTI_H__
