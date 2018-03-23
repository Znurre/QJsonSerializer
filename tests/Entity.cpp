#include "Entity.h"

Entity::Entity()
	: m_child(nullptr)
	, m_intProperty(0)
	, m_floatProperty(0)
{
}

Child *Entity::child() const
{
	return m_child;
}

void Entity::setChild(Child *child)
{
	m_child = child;
}

Array<Child *> Entity::children() const
{
	return m_children;
}

void Entity::setChildren(const Array<Child *> &children)
{
	m_children = children;
}

QString Entity::stringProperty() const
{
	return m_stringProperty;
}

void Entity::setStringProperty(const QString &property1)
{
	m_stringProperty = property1;
}

QDateTime Entity::dateTimeProperty() const
{
	return m_dateTimeProperty;
}

void Entity::setDateTimeProperty(const QDateTime &dateTimeProperty)
{
	m_dateTimeProperty = dateTimeProperty;
}

Array<int> Entity::intCollection() const
{
	return m_intCollection;
}

void Entity::setIntCollection(const Array<int> &intCollection)
{
	m_intCollection = intCollection;
}

Array<QString> Entity::stringCollection() const
{
	return m_stringCollection;
}

void Entity::setStringCollection(const Array<QString> &stringCollection)
{
	m_stringCollection = stringCollection;
}

int Entity::intProperty() const
{
	return m_intProperty;
}

void Entity::setIntProperty(int intProperty)
{
	m_intProperty = intProperty;
}

float Entity::floatProperty() const
{
	return m_floatProperty;
}

void Entity::setFloatProperty(float floatProperty)
{
	m_floatProperty = floatProperty;
}
