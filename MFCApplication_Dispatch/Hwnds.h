#pragma once
#include <map>
#include <vector>
using namespace std;

class HwndResource
{
public:
	map<HWND, vector<int>> m_dds;
};

