#ifndef CHILD_H
#define CHILD_H

#include <QObject>

#include "Array.h"

class Child : public QObject
{
	Q_OBJECT

	Q_PROPERTY(int intProperty READ intProperty WRITE setIntProperty)

	public:
		Q_INVOKABLE Child();

		int intProperty() const;
		void setIntProperty(int intProperty);

	private:
		int m_intProperty;
};

Q_DECLARE_METATYPE(Child *)
Q_DECLARE_METATYPE(Array<Child>)

#endif // CHILD_H
