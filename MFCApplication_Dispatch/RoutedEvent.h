#pragma once
#include <functional>
using namespace std;

class RoutedEventArgs
{

};

class RoutedEvent
{
public:
	std::function<void(void*, RoutedEventArgs*)> handler;
};



