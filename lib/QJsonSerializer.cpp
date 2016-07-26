#include "QJsonSerializer.h"

QJsonSerializer::QJsonSerializer()
	: m_factory(&m_defaultFactory)
{

}

void QJsonSerializer::setObjectFactory(IObjectFactory *factory)
{
	m_factory = factory;
}
