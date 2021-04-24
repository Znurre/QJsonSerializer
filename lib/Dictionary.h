#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QMetaObject>
#include <QVariantList>
#include <QHash>

#include "IObjectFactory.h"
#include "ISerializable.h"

class IDictionary : public ISerializable
{
	public:
		QJsonValue serialize(const SerializerBase &serializer) const override;

		virtual bool isScalar() const = 0;

		virtual const QMetaObject *metaObject() const = 0;

		virtual void *createElement(const QString &key, const IObjectFactory &factory) = 0;

		virtual QVariantMap toVariantMap() const = 0;

		virtual void addElement(const QString &key, const QVariant &variant) = 0;
		virtual void initialize() = 0;
};

template<typename T>
class Dictionary
	: public QHash<QString, T>
	, public IDictionary
{
	public:
		Q_INVOKABLE Dictionary()
			: m_pointer(this)
		{
		}

		const QMetaObject *metaObject() const override
		{
			return nullptr;
		}

		void *createElement(const QString &key, const IObjectFactory &factory) override
		{
			Q_UNUSED(key);
			Q_UNUSED(factory);

			return nullptr;
		}

		QVariantMap toVariantMap() const override
		{
			QVariantMap map;

			for (const T &value : *m_pointer)
			{
				auto key = m_pointer->key(value);

				map[key] = QVariant::fromValue(value);
			}

			return map;
		}

		void addElement(const QString &key, const QVariant &variant) override
		{
			auto value = variant.value<T>();

			m_pointer->insert(key, value);
		}

		void initialize() override
		{
			m_pointer->clear();
		}

	private:
		Dictionary<T> *m_pointer;
};

template<class T>
class Dictionary<T *>
	: public QHash<QString, T *>
	, public IDictionary
{
	public:
		Q_INVOKABLE Dictionary()
			: m_pointer(this)
		{

		}

		bool isScalar() const override
		{
			return false;
		}

		const QMetaObject *metaObject() const override
		{
			return &T::staticMetaObject;
		}

		void *createElement(const QString &key, const IObjectFactory &factory) override
		{
			T *element = factory.create<T>();

			m_pointer->insert(key, element);

			return element;
		}

		QVariantMap toVariantMap() const override
		{
			QVariantMap map;

			for (T *value : *m_pointer)
			{
				auto key = m_pointer->key(value);

				map[key] = QVariant::fromValue(value);
			}

			return map;
		}

		void addElement(const QString &key, const QVariant &variant) override
		{
			Q_UNUSED(key);
			Q_UNUSED(variant);
		}

		void initialize() override
		{
			m_pointer->clear();
		}

	private:
		Dictionary<T *> *m_pointer;
};

#endif // DICTIONARY_H
