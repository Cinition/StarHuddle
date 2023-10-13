#pragma once

#include "Notification.h"

#include <deque>
#include <memory>

class NotificationManager
{

public:

	void update( void );
	void draw( void );

	static void addNotification( Notification _notification );

private:

	inline static std::deque< Notification > m_notifications;

};
