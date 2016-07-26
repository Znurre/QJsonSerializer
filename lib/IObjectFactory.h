#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

#include <QMetaObject>
#include <QDebug>

class IObjectFactory
{
	public:
		virtual QObject *create(const QMetaObject *metaObject) = 0;
};

class DefaultObjectFactory : public IObjectFactory
{
	public:
		QObject *create(const QMetaObject *metaObject)
		{
			QObject *child = metaObject->newInstance();

			if (!child)
			{
				qCritical() << "Failed to create an instance of type" << metaObject->className();
				qCritical() << "Did you forget to declare a public parameterless Q_INVOKABLE constructor?";
			}

			return child;
		}
};

#endif // IOBJECTFACTORY_H
