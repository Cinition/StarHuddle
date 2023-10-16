#include "NotificationManager.h"

#include "UI/Style.h"

constexpr size_t MAX_NOTIFICATIONS = 5;

void NotificationManager::update( void )
{
	for( auto notif_it = m_notifications.begin(); notif_it != m_notifications.end(); notif_it++ )
	{
		if( !notif_it->alive )
		{
			m_notifications.erase( notif_it );
			break;
		}
	}

	for( auto& notification : m_notifications )
		notification.update();
}

void NotificationManager::draw( void )
{
	auto cursor_position = Vector2( UI::MARGIN * 1.5f, UI::SCREEN_SIZE.y - UI::MARGIN * 1.5f );

	for( auto& notifications : m_notifications )
		notifications.draw( cursor_position );
}

void NotificationManager::addNotification( Notification _notification)
{
	if( m_notifications.size() > MAX_NOTIFICATIONS )
		m_notifications.pop_front();

	m_notifications.push_back( std::move( _notification ) );
}
