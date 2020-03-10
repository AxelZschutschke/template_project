#include "database.h"
#include <iostream>

int main()
{
  auto eventQueue = valgrind::EventQueue{};
  for( int i = 0; i < 100; ++i ) 
    for( int j = 0; j < 10; ++j ) eventQueue.addEvent( j );
  for( int j = 8; j > 0; --j) 
  {
    std::cout << j << std::endl;
    eventQueue.removeDuplicates(j);
  }

  std::cout << eventQueue.getNext() << std::endl;
  std::cout << eventQueue.getNext() << std::endl;
  return 0;
}
