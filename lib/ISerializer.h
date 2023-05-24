#ifndef ISERIALIZER_H
#define ISERIALIZER_H

#include <QByteArray>
#include <QJsonDocument>

#include "Array.h"
#include "SerializerBase.h"
#include "Library.h"

template<class TSource>
class ISerializer
{
	public:
		virtual QByteArray serialize(const TSource &source) const = 0;
};

template<class TSource>
class QJSONSERIALIZER_EXPORT Serializer
	: public SerializerBase
	, public ISerializer<TSource>
{
	public:
		QByteArray serialize(const TSource &source) const override
		{
			Q_UNUSED(source);

			return QByteArray();
		}
};

template<class TSource>
class QJSONSERIALIZER_EXPORT Serializer<TSource *>
	: public SerializerBase
	, public ISerializer<TSource *>
{
	public:
		QByteArray serialize(TSource *const &source) const override
		{
			const QMetaObject &metaObject = TSource::staticMetaObject;
			const QJsonObject &object = serializeObject(source, &metaObject);

			QJsonDocument document;
			document.setObject(object);

			return document.toJson(QJsonDocument::Compact);
		}
};

template<class TReturn>
class QJSONSERIALIZER_EXPORT Serializer<Array<TReturn>>
	: public SerializerBase
	, public ISerializer<Array<TReturn>>
{
	public:
		QByteArray serialize(const Array<TReturn> &source) const override
		{
			const QJsonArray &array = serializeArray(source);

			QJsonDocument document;
			document.setArray(array);

			return document.toJson(QJsonDocument::Compact);
		}
};

#endif // ISERIALIZER_H
