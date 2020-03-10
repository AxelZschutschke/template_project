#include <deque>

namespace valgrind
{

  class EventQueue
  {
    private:
      std::deque<int> m_events;

    public:
      void addEvent( int const & event ) 
      { 
        m_events.push_back( event ); 
      }
      int getNext( )
      {
        int result = m_events.front();
        m_events.pop_front();
        return result;
      }
      void removeDuplicates( int const & searchFor ) 
      { 
        for( auto i = m_events.begin(); i != m_events.end(); ++i )
        {
          if( *i == searchFor ) m_events.erase( i );
        }
      }
  };
}
