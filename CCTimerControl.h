
//
//
// Class:		CCTimerControl
// Green Turtle Games
// Author:		Alejandro Santiago
// Email:		alejandro@aeonphyxius.com
// Description: 	This class creates a Timer control (Minutes and Secods).
//			Using a CCNode as a grouping object and 2 CCLabelTTF components
//			for Minutes and Seconds display as a child.
//				
//
#ifndef __CC_TIMER_CONTROL_H__
#define __CC_TIMER_CONTROL_H__

#include "cocos2d.h"
#include "cocos2dx-ext\CCPointer.h"


#define DEFAULT_MINUTES_CHAR '\''
#define DEFAULT_SECONDS_CHAR "''"
#define DEFAULT_BETWEEN_CHAR ":"

class TimerControlStates;

using namespace std;
using namespace cocos2d;

class CCTimerControl : public CCNode
{
	/* Minutes label  */
	CC_SYNTHESIZE(CCPointer<CCLabelTTF>, minutes_txt, MinutesTxt); 

	/* Seconds label */
	CC_SYNTHESIZE(CCPointer<CCLabelTTF>, seconds_txt, SecondsTxt); 

	/* Indicator to use after the minutes number (' by default) */
	CC_SYNTHESIZE(string, minutes_indicator,MinutesIndicator);

	/* Indicator to show between the minutes and seconds indicators. ( : by default) */
	CC_SYNTHESIZE(string, minutes_seconds_indicator,MinutesSecondsIndicator);

	/* Indicator to use after the seconds number ('' by default) */
	CC_SYNTHESIZE(string, seconds_indicator, SecondsIndicator);

public:
	
	/**
    	* CCTimerControl		Default constructor, initializing the states std::map and current state
	*				Create() function must be called afterwards
	*
    	*/
	CCTimerControl();

	/**
    	* CCTimerControl		Constructor, initializing the states std::map and current state
	*				Create() function does not to be called afterwards. Everything is
	*				initialized within this constructor
	*
	* @param    CCString		- Font to be used to display the text
	* @param    float		- Font size
    	*/
	CCTimerControl(const CCString _font, const float _font_size);


	/**
    	* ~CCTimerControl		Default destructor. Clean up before exiting
	*
    	*/
	~CCTimerControl();


	/**
    	* addState			Add a color state for this control. If we want to display different 
	*				text colors depending on the time, we shall create this indicating the 
	*				lower limit and the upper limit (both in seconds) and the color
	*				we want to display while the time is between this limits
	*
	* @param    float		- Lower limit in secods for this state
	* @param    float		- Upper limit in seconds for this state
	* @param    ccColor3B		- Color to display the TimerControl within this state
	*
    	*/
	void addState (const float _lowerLimit,const float _upperLimit,const ccColor3B _texture_color);	
	

	/**
    	* addState			Add a color state for this control. If we want to display different 
	*				text colors depending on the time, we shall create this indicating the 
	*				lower limit and the upper limit (both in seconds) and the color
	*				we want to display while the time is between this limits
	*
	* @param    float		- Lower limit in secods for this state
	* @param    float		- Upper limit in seconds for this state
	* @param    ccColor3B		- Color to display the TimerControl within this state
	* @param    bool		- Is it going to blink while in this state?
	*
    	*/
	void addState(const float _lowerLimit,const float _upperLimit,const ccColor3B _texture_color,const bool _isBlinking);	


	/**
    	* create			Create the control initializing the text components and add them to the 
	*				current CCNode object
	*
	* @param    CCString		- Font to be used to display the text
	* @param    float		- Font size
	*
    	*/
	void create (const CCString _font, const float _font_size);


	/**
    	* updateTime			Every update we should call this function to update the time in 
	*				our display. this function first will check if the time is between the 
	*				current limits and then update the font, size, color etc if needed. 
	*				Afterwards will update the Timer's text
	*
	* @param    float		- Total seconds to display in our Timer Control
	*
    	*/
	void updateTime (const float _seconds);

private:

	/**
    	* CCTimerControl		After checking the state we are in, we should just update the text of our
	*				timer indicator
	*
	* @param    float		- Total seconds to display in our Timer Control
	*
    	*/
	void updateTextControls(const float _seconds);

private:

	/* collection of all Timer states */
	map <int, TimerControlStates*> * m_states;

	/* Current state. Used to check upper and lower limits */
	TimerControlStates * m_current_state;

	/* Current status id*/
	int current_state_id;
		
};

class TimerControlStates
{
public:	
	/* Color to display on this Timer state*/
	ccColor3B  textColor;
	/* Lower limit in secods for this state */
	float lowerLimit; 
	/* Upper limit in secods for this state */
	float upperLimit; 
	/* Is it going to be blinking the Timer when in this state? */
	bool isBlinking;
};

#endif  // __CC_TIMER_CONTROL_H__
