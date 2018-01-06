#ifndef IDESERIALIZER_H
#define IDESERIALIZER_H

#include <QByteArray>
#include <QJsonDocument>

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
			TReturn value;

			deserialize(data, value);

			return value;
		}

		void deserialize(const QJsonObject &object, TReturn &target) const
		{
			Q_UNUSED(object);
			Q_UNUSED(target);
		}

		void deserialize(const QByteArray &data, TReturn &target) const
		{
			/*
			 * QJsonDocument does not support documents with roots other than objects or arrays,
			 * despite RFC 7159 and ECMA-404 stating that it should be allowed.
			 * Therefore we have to construct a dummy object and deserialize it.
			*/

			QByteArray cloned = data;

			cloned.insert(0, "{ \"dummy\": ");
			cloned.append("}");

			const QJsonDocument &document = QJsonDocument::fromJson(cloned);
			const QJsonObject &object = document.object();

			const QVariant &variant = object
				.value("dummy")
				.toVariant();

			target = variant.value<TReturn>();
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

		void deserialize(const QJsonObject &object, TReturn *target) const
		{
			deserializeObject(object, target);
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

		void deserialize(const QJsonObject &object, Array<TReturn> &target) const
		{
			Q_UNUSED(object);
			Q_UNUSED(target);
		}

		Array<TReturn> deserialize(const QByteArray &data) const
		{
			Array<TReturn> array;

			deserialize(data, array);

			return array;
		}

		void deserialize(const QByteArray &data, Array<TReturn> &target) const
		{
			const QJsonDocument &document = QJsonDocument::fromJson(data);
			const QJsonArray &root = document.array();

			deserializeArray(root, target);
		}
};

#endif // IDESERIALIZER_H
