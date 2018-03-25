#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

#include <QMetaObject>
#include <QDebug>

class IObjectFactory
{
	public:
		virtual void *create(const QMetaObject *metaObject) const = 0;

		template<class T>
		T *create() const
		{
			return (T* )create(&T::staticMetaObject);
		}
};

class DefaultObjectFactory : public IObjectFactory
{
	public:
		DefaultObjectFactory()
		{

		}

		void *create(const QMetaObject *metaObject) const override
		{
			void *child = metaObject->newInstance();

			if (!child)
			{
				qCritical() << "Failed to create an instance of type" << metaObject->className();
				qCritical() << "Did you forget to declare a public parameterless Q_INVOKABLE constructor?";
			}

			return child;
		}
};

#endif // IOBJECTFACTORY_H
