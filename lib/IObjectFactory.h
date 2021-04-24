#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

#include <QMetaObject>
#include <QMetaMethod>
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
			auto child = newInstance(metaObject);

			if (!child)
			{
				qCritical() << "Failed to create an instance of type" << metaObject->className();
				qCritical() << "Did you forget to declare a public parameterless Q_INVOKABLE constructor?";
			}

			return child;
		}

	private:
		// Works around QTBUG-76663
		void *newInstance(const QMetaObject *mo) const
		{
			QByteArray constructorName = mo->className();

			{
				int idx = constructorName.lastIndexOf(':');

				if (idx != -1)
				{
					constructorName.remove(0, idx + 1); // remove qualified part
				}
			}

			QVarLengthArray<char, 512> sig;
			sig.append(constructorName.constData(), constructorName.length());
			sig.append('(');
			sig.append(')');
			sig.append('\0');

			int idx = mo->indexOfConstructor(sig.constData());

			if (idx < 0)
			{
				QByteArray norm = QMetaObject::normalizedSignature(sig.constData());
				idx = mo->indexOfConstructor(norm.constData());
			}

			if (idx < 0)
			{
				return 0;
			}

			void *returnValue = 0;
			void *param[] = { &returnValue };

			if (mo->static_metacall(QMetaObject::CreateInstance, idx, param) >= 0)
			{
				return 0;
			}

			return returnValue;
		}
};

#endif // IOBJECTFACTORY_H
