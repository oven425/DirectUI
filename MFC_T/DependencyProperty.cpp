#include "pch.h"
#include "DependencyProperty.h"
template <typename T>
map<std::size_t, void*> DependencyProperty<T>::m_Saves;

//template <typename T>
//map<int, int> dp<T>::m_Saves;
//template <typename T>
//int dp<T>::m_pp;

template <typename T>
int dp<T>::m_Count = 0;