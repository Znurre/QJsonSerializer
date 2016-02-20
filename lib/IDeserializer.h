#ifndef IDESERIALIZER_H
#define IDESERIALIZER_H

#include <QByteArray>

#include "Array.h"
#include "DeserializerBase.h"

template<class TReturn>
class IDeserializer
{
	public:
		virtual TReturn deserialize(const QByteArray &data) const = 0;
};

template<class TReturn>
class Deserializer : public DeserializerBase, public IDeserializer<TReturn>
{
	public:
		TReturn deserialize(const QByteArray &data) const override
		{
			Q_UNUSED(data);

			TReturn instance;

			return instance;
		}
};

template<class TReturn>
class Deserializer<TReturn *> : public DeserializerBase, public IDeserializer<TReturn *>
{
	public:
		TReturn *deserialize(const QByteArray &data) const override
		{
			TReturn *instance = new TReturn();

			const QJsonDocument &document = QJsonDocument::fromJson(data);
			const QJsonObject &root = document.object();

			deserializeObject(root, instance);

			return instance;
		}
};

template<class TReturn>
class Deserializer<Array<TReturn>> : public DeserializerBase, public IDeserializer<Array<TReturn>>
{
	public:
		Array<TReturn> deserialize(const QByteArray &data) const override
		{
			Array<TReturn> array;

			const QJsonDocument &document = QJsonDocument::fromJson(data);
			const QJsonArray &root = document.array();

			deserializeArray(root, array);

			return array;
		}
};

#endif // IDESERIALIZER_H
