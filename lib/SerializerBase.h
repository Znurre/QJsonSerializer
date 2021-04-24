#ifndef SERIALIZERBASE_H
#define SERIALIZERBASE_H

#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>

class IArray;
class IDictionary;

class Q_DECL_EXPORT SerializerBase
{
	friend class IArray;
	friend class IDictionary;

	protected:
		QJsonArray serializeArray(const IArray &source) const;
		QJsonObject serializeObject(const void *source, const QMetaObject *metaObject) const;
};

#endif // SERIALIZERBASE_H
