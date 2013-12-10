#include "CCTimerControl.h"

CCTimerControl::CCTimerControl()
{	
	current_state_id = -1;	// -1 to know that have not been initialized any state
	m_states = new map <int, TimerControlStates*>();
	// Default indicators
	minutes_indicator = DEFAULT_MINUTES_CHAR;
	seconds_indicator = DEFAULT_SECONDS_CHAR;
	minutes_seconds_indicator = DEFAULT_BETWEEN_CHAR;
}

CCTimerControl::CCTimerControl(const CCString _font, const float _font_size)
{
	create(_font,_font_size);
	// Default indicators
	minutes_indicator = DEFAULT_MINUTES_CHAR;
	seconds_indicator = DEFAULT_SECONDS_CHAR;
	minutes_seconds_indicator = DEFAULT_BETWEEN_CHAR;
}

CCTimerControl::~CCTimerControl()
{
	if (m_states != NULL)
	{
		m_states->clear();
		delete m_states;
	}

	delete m_current_state;
}

void CCTimerControl::create (const CCString _font, const float _font_size)
{
	// Step 1, create the minutes' font object 
	minutes_txt = CCLabelTTF::create("0'", _font.getCString() ,_font_size);
	minutes_txt->setAnchorPoint(ccp(0,0));
	minutes_txt->setPosition(ccp(0,0));
	
	// Step 2, create the seconds' font object, and located just after the
	// minutes label
	float pos = minutes_txt->boundingBox().size.width;
	seconds_txt = CCLabelTTF::create(":00''", _font.getCString() ,_font_size);		
	seconds_txt->setAnchorPoint(ccp(0,0));
	seconds_txt->setPosition(ccp(pos,0));
		
	// Step 3, add both new components to our node (Timer)
	this->addChild(minutes_txt);
	this->addChild(seconds_txt);
}


void CCTimerControl::addState(const float _lowerLimit,const float _upperLimit,const ccColor3B _texture_color)
{
	// When blinking is not assigened, just assume that this state is not going to blink
	addState(_lowerLimit,_upperLimit,_texture_color,false);
}

void CCTimerControl::addState(const float _lowerLimit,const float _upperLimit,const ccColor3B _texture_color,const bool _isBlinking)
{
	// Create a temp state
	TimerControlStates * temp = new TimerControlStates();
	temp->lowerLimit = _lowerLimit;
	temp->upperLimit = _upperLimit;
	temp->textColor = _texture_color;
	temp->isBlinking = _isBlinking;
	
	// Is it the first state?
	if (current_state_id == -1)
	{
		current_state_id  = 0;
		m_current_state = temp;				
	}	

	// add state to our states list
	m_states->insert(make_pair(m_states->size(),temp));
}

void CCTimerControl::updateTime (const float _seconds)
{
    // Check if the current time, is between the current state limits
	if ((_seconds < m_current_state->lowerLimit) || (_seconds > m_current_state->upperLimit))
	{
		map<int, TimerControlStates*>::iterator states;
		TimerControlStates * tempState;

        // This iteration is assuming we have 1-2 maybe 3 states. Otherwise should considere
        // Ordering this list
		for (states = m_states->begin(); states != m_states->end(); states++) 
		{			
			tempState = states->second;
			if (tempState->lowerLimit <= _seconds && tempState->upperLimit >= _seconds)
			{
                // When we have found the new state
				if (current_state_id != (int)states->first)
				{				
                    // Save the new state, set color and blinkin properties
					current_state_id = states->first;	
					m_current_state = states->second;
					minutes_txt->setColor(tempState->textColor);
					seconds_txt->setColor(tempState->textColor);
                    // If is it blinkin, create the action to make this effect, 
                    // otherwise, stop all actions. 
					if (m_current_state->isBlinking)
					{
						this->runAction(CCRepeatForever::create( CCBlink::create (30,30)));
					}
					else
					{
						this->stopAllActions();
					}
				}
			}  
		}
	}

	// Update the text controls
	updateTextControls(_seconds);

}

void CCTimerControl::updateTextControls(const float _seconds)
{
	string textToBuildTime = "";
	char addNumber [250];
	
	// Calculate minutes and seconds
	unsigned int minutes = (int) (_seconds / 60) % 60;
	unsigned int seconds = (int)  _seconds  % 60;

	// Create minutes text and update control
	sprintf(addNumber, "%d",minutes);
	textToBuildTime += addNumber;
	textToBuildTime += minutes_indicator;
	minutes_txt->setString(textToBuildTime.c_str());
	
	// Create seconds text and update control
	textToBuildTime = "";
	sprintf(addNumber, " %d",seconds);
	textToBuildTime += minutes_seconds_indicator;
	textToBuildTime += addNumber;
	textToBuildTime += seconds_indicator;
	seconds_txt->setString(textToBuildTime.c_str());

}
