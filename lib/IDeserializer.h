#ifndef IDESERIALIZER_H
#define IDESERIALIZER_H

#include <QByteArray>

#include "Array.h"
#include "DeserializerBase.h"

template<class TReturn>
class Deserializer : public DeserializerBase
{
	public:
		Deserializer(const IObjectFactory &factory)
			: DeserializerBase(factory)
		{

		}

		TReturn deserialize(const QByteArray &data) const
		{
			Q_UNUSED(data);

			return TReturn();
		}

		void deserialize(const QByteArray &data, TReturn target) const
		{
			Q_UNUSED(data);
			Q_UNUSED(target);
		}
};

template<class TReturn>
class Deserializer<TReturn *> : public DeserializerBase
{
	public:
		Deserializer(const IObjectFactory &factory)
			: DeserializerBase(factory)
		{

		}

		TReturn *deserialize(const QByteArray &data) const
		{
			TReturn *instance = m_factory.create<TReturn>();

			deserialize(data, instance);

			return instance;
		}

		void deserialize(const QByteArray &data, TReturn *target) const
		{
			const QJsonDocument &document = QJsonDocument::fromJson(data);
			const QJsonObject &root = document.object();

			deserializeObject(root, target);
		}
};

template<class TReturn>
class Deserializer<Array<TReturn>> : public DeserializerBase
{
	public:
		Deserializer(const IObjectFactory &factory)
			: DeserializerBase(factory)
		{

		}

		Array<TReturn> deserialize(const QByteArray &data) const
		{
			Array<TReturn> array;

			deserialize(data, array);

			return array;
		}

		void deserialize(const QByteArray &data, Array<TReturn>& target) const
		{
			const QJsonDocument &document = QJsonDocument::fromJson(data);
			const QJsonArray &root = document.array();

			deserializeArray(root, target);
		}
};

#endif // IDESERIALIZER_H
