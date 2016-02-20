#ifndef ARRAY_H
#define ARRAY_H

#include <QList>
#include <QObject>
#include <QVariant>

class IElementFactory
{
	public:
		virtual QObject *createElement() = 0;
		virtual QList<QObject *> toObjectList() const = 0;
};

template<class T>
class Array
	: public QList<T *>
	, public IElementFactory
{
	public:
		Q_INVOKABLE Array()
			: m_pointer(this)
		{

		}

		QObject *createElement() override
		{
			T *element = new T();

			m_pointer->append(element);

			return element;
		}

		QList<QObject *> toObjectList() const override
		{
			QList<QObject *> list;

			for (T *element : *this)
			{
				list << element;
			}

			return list;
		}

	private:
		Array<T> *m_pointer;
};

#endif // ARRAY_H
