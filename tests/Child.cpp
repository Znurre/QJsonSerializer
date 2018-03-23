#include "Child.h"

Child::Child()
	: m_intProperty(0)
{
}

int Child::intProperty() const
{
	return m_intProperty;
}

void Child::setIntProperty(int intProperty)
{
	m_intProperty = intProperty;
}
