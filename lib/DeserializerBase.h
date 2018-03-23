#ifndef DESERIALIZERBASE_H
#define DESERIALIZERBASE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>

class IArray;
class IObjectFactory;

class Q_DECL_EXPORT DeserializerBase
{
	protected:
		DeserializerBase(const IObjectFactory &factory);

		void deserializeArray(const QJsonArray &array, IArray &target) const;
		void deserializeObject(const QJsonObject &object, void *instance, const QMetaObject *metaObject) const;

		const IObjectFactory &m_factory;
};

#endif // DESERIALIZERBASE_H
