#include "CCProgressTimerMulti.h"

CCProgressTimerMulti::CCProgressTimerMulti()
{	
	currState = -1.0;			// In order to indicate that the states queue is empty
	currLowerLimit = -1.0;		// In order to indicate that the states queue is empty
	currUpperLimit = -1.0;		// In order to indicate that the states queue is empty
	
	m_states = new map <int, ProgressStates>();
}

CCProgressTimerMulti::~CCProgressTimerMulti()
{

}


void CCProgressTimerMulti::addState (const float _lowerLimit,const float _upperLimit,const string _spriteName)
{
	addState(_lowerLimit,_upperLimit,_spriteName,255);  // 255 For a non opacity value
}

void CCProgressTimerMulti::addState (const float _lowerLimit,const float _upperLimit,const string _spriteName,const int _alpha)
{
	// State initialization
	ProgressStates temp = ProgressStates();
	temp.lowerLimit = _lowerLimit;
	temp.upperLimit = _upperLimit;
	temp.m_stateSprite = CCSprite::createWithSpriteFrameName (_spriteName.c_str());
	temp.m_stateSprite->setOpacity(_alpha);
	
	// First state added to this control, will be always the default current state
	if (currState == -1)
	{
		currState  = 0;
		currLowerLimit = _lowerLimit;
		currUpperLimit = _upperLimit;
		this->initWithSprite(CCSprite::createWithSpriteFrameName (_spriteName.c_str()));		
	}	

	// Add the state to our states list
	m_states->insert(make_pair(m_states->size(),temp));
}

void CCProgressTimerMulti::setPercentage (float _percentage)
{
	// Check if the new percentage is NOT between the current limits (upper and lower)
	if ((_percentage < currLowerLimit) || (_percentage > currUpperLimit))
	{
		map<int, ProgressStates>::iterator states;
		ProgressStates tempState;
		
		// Iterate thow all states in order to find the new correct state
		for (states = m_states->begin(); states != m_states->end(); states++) 
		{			
			tempState = states->second;

			// If the new percentage is between the current iterated state limits
			if (tempState.lowerLimit <= _percentage && tempState.upperLimit >= _percentage)
			{
				// Exchange the current state information and CCPorgresTimer sprite
				currState = states->first;	
				currLowerLimit = tempState.lowerLimit;
				currUpperLimit = tempState.upperLimit;
				this->setSprite (tempState.m_stateSprite);				
			}  
		}
	}
	this->CCProgressTimer::setPercentage(_percentage); // Call CCPorgresTimer what we hidde using this metod
}
