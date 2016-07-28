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
		virtual void deserialize(const QByteArray &data, TReturn target) const = 0;
};

template<class TReturn>
class Deserializer
	: public DeserializerBase
	, public IDeserializer<TReturn>
{
	public:
		Deserializer(const IObjectFactory &factory)
			: DeserializerBase(factory)
		{

		}

		TReturn deserialize(const QByteArray &data) const override
		{
			Q_UNUSED(data);

			return TReturn();
		}

		void deserialize(const QByteArray &data, TReturn target) const override
		{
			Q_UNUSED(data);
			Q_UNUSED(target);
		}
};

template<class TReturn>
class Deserializer<TReturn *>
	: public DeserializerBase
	, public IDeserializer<TReturn *>
{
	public:
		Deserializer(const IObjectFactory &factory)
			: DeserializerBase(factory)
		{

		}

		TReturn *deserialize(const QByteArray &data) const override
		{
			TReturn *instance = m_factory.create<TReturn>();

			deserialize(data, instance);

			return instance;
		}

		void deserialize(const QByteArray &data, TReturn *target) const override
		{
			const QJsonDocument &document = QJsonDocument::fromJson(data);
			const QJsonObject &root = document.object();

			deserializeObject(root, target);
		}
};

template<class TReturn>
class Deserializer<Array<TReturn>>
	: public DeserializerBase
	, public IDeserializer<Array<TReturn>>
{
	public:
		Deserializer(const IObjectFactory &factory)
			: DeserializerBase(factory)
		{

		}

		Array<TReturn> deserialize(const QByteArray &data) const override
		{
			Array<TReturn> array;

			const QJsonDocument &document = QJsonDocument::fromJson(data);
			const QJsonArray &root = document.array();

			deserializeArray(root, array);

			return array;
		}

		void deserialize(const QByteArray &data, Array<TReturn> target) const override
		{
			Q_UNUSED(data);
			Q_UNUSED(target);
		}
};

#endif // IDESERIALIZER_H
