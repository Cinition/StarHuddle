#pragma once

#include "UI/Element/Notification.h"

#include <deque>
#include <memory>

class NotificationManager
{
public:

	void update( const float _tick );
	void draw( void );

	static void addNotification( Notification _notification );

private:

	inline static std::deque< Notification > m_notifications;

};
