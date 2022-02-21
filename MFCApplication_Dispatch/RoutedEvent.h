#pragma once
#include <functional>
using namespace std;

class RoutedEventArgs
{

};

template<class T>
class RoutedEvent
{
public:
	//std::function<void(void*, RoutedEventArgs*)> handler;
	T handler;
};



