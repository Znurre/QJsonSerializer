#include "GadgetChild.h"

GadgetChild::GadgetChild()
	: m_intProperty(0)
{
}

int GadgetChild::intProperty() const
{
	return m_intProperty;
}

void GadgetChild::setIntProperty(int intProperty)
{
	m_intProperty = intProperty;
}
