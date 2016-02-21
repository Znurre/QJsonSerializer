#ifndef QJSONSERIALIZER_H
#define QJSONSERIALIZER_H

#include <QByteArray>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QJsonArray>

#include "Array.h"
#include "IDeserializer.h"
#include "ISerializer.h"

class QJsonSerializer
{
	public:
		template<class TReturn>
		TReturn deserialize(const QByteArray &data)
		{
			Deserializer<TReturn> subject;

			return subject.deserialize(data);
		}

		template<class TReturn>
		TReturn deserialize(QIODevice *device)
		{
			const QByteArray &data = device->readAll();

			return deserialize<TReturn>(data);
		}

		template<class TSource>
		QByteArray serialize(const TSource &source)
		{
			Serializer<TSource> subject;

			return subject.serialize(source);
		}
};

#endif // QJSONSERIALIZER_H
