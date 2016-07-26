#ifndef ARRAY_H
#define ARRAY_H

#include <QList>
#include <QObject>
#include <QVariant>
#include <QDateTime>

#include "IObjectFactory.h"

class IArray
{
	public:
		virtual bool isScalar() const = 0;

		virtual QObject *createElement(IObjectFactory &factory) = 0;
		virtual QVariantList toVariantList() const = 0;

		virtual void addElement(const QVariant &variant) = 0;
};

template<class T>
class Array
	: public QList<T>
	, public IArray
{
	public:
		Q_INVOKABLE Array()
			: m_pointer(this)
		{

		}

		bool isScalar() const override
		{
			return true;
		}

		QObject *createElement(IObjectFactory &factory) override
		{
			Q_UNUSED(factory);

			return nullptr;
		}

		QVariantList toVariantList() const override
		{
			QVariantList list;

			for (const T &element : *m_pointer)
			{
				list << QVariant::fromValue(element);
			}

			return list;
		}

		void addElement(const QVariant &variant) override
		{
			*m_pointer << variant.value<T>();
		}

	private:
		Array<T> *m_pointer;
};

Q_DECLARE_METATYPE(Array<int>)
Q_DECLARE_METATYPE(Array<long>)
Q_DECLARE_METATYPE(Array<float>)
Q_DECLARE_METATYPE(Array<QDateTime>)
Q_DECLARE_METATYPE(Array<QString>)

template<class T>
class Array<T *>
	: public QList<T *>
	, public IArray
{
	public:
		Q_INVOKABLE Array()
			: m_pointer(this)
		{

		}

		bool isScalar() const override
		{
			return false;
		}

		QObject *createElement(IObjectFactory &factory) override
		{
			T *element = (T *)factory.create(&T::staticMetaObject);

			m_pointer->append(element);

			return element;
		}

		QVariantList toVariantList() const override
		{
			QVariantList list;

			for (T *element : *m_pointer)
			{
				list << QVariant::fromValue(element);
			}

			return list;
		}

		void addElement(const QVariant &variant) override
		{
			Q_UNUSED(variant);
		}

	private:
		Array<T *> *m_pointer;
};

#endif // ARRAY_H
