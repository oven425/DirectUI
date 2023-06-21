#pragma once
#include <functional>
#include <vector>
#include <map>
using namespace std;

class INotitfyChanged
{
public:
	std::function<void(void*, char* name)> PropertyChanged;
};

class NodeContext
{
public:
	map<Node*, Node*> m_NodeMap;
};


class Node
{
public:
	void Add(Node* data)
	{

	}
};


