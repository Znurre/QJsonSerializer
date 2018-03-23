#include "GadgetEntity.h"

GadgetEntity::GadgetEntity()
	: m_child(nullptr)
	, m_intProperty(0)
	, m_floatProperty(0)
{
}

GadgetChild *GadgetEntity::child() const
{
	return m_child;
}

void GadgetEntity::setChild(GadgetChild *child)
{
	m_child = child;
}

Array<GadgetChild *> GadgetEntity::children() const
{
	return m_children;
}

void GadgetEntity::setChildren(const Array<GadgetChild *> &children)
{
	m_children = children;
}

QString GadgetEntity::stringProperty() const
{
	return m_stringProperty;
}

void GadgetEntity::setStringProperty(const QString &property1)
{
	m_stringProperty = property1;
}

QDateTime GadgetEntity::dateTimeProperty() const
{
	return m_dateTimeProperty;
}

void GadgetEntity::setDateTimeProperty(const QDateTime &dateTimeProperty)
{
	m_dateTimeProperty = dateTimeProperty;
}

Array<int> GadgetEntity::intCollection() const
{
	return m_intCollection;
}

void GadgetEntity::setIntCollection(const Array<int> &intCollection)
{
	m_intCollection = intCollection;
}

Array<QString> GadgetEntity::stringCollection() const
{
	return m_stringCollection;
}

void GadgetEntity::setStringCollection(const Array<QString> &stringCollection)
{
	m_stringCollection = stringCollection;
}

int GadgetEntity::intProperty() const
{
	return m_intProperty;
}

void GadgetEntity::setIntProperty(int intProperty)
{
	m_intProperty = intProperty;
}

float GadgetEntity::floatProperty() const
{
	return m_floatProperty;
}

void GadgetEntity::setFloatProperty(float floatProperty)
{
	m_floatProperty = floatProperty;
}
