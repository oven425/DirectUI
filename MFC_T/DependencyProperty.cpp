#include "pch.h"
#include "DependencyProperty.h"
template <typename T>
map<std::size_t, void*> DependencyProperty<T>::m_Saves;