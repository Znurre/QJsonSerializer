#ifndef DESERIALIZERBASE_H
#define DESERIALIZERBASE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>

class IArray;
class IObjectFactory;
class IDictionary;

class DeserializerBase
{
	protected:
		DeserializerBase(const IObjectFactory &factory);

		void deserializeDictionary(const QJsonObject &object, IDictionary &target) const;
		void deserializeArray(const QJsonArray &array, IArray &target) const;
		void deserializeObject(const QJsonObject &object, void *instance, const QMetaObject *metaObject) const;

		const IObjectFactory &m_factory;
};

#endif // DESERIALIZERBASE_H
