#ifndef GADGETCHILD_H
#define GADGETCHILD_H

#include <QObject>

#include "Array.h"

class GadgetChild : public QObject
{
	Q_OBJECT

	Q_PROPERTY(int intProperty READ intProperty WRITE setIntProperty)

	public:
		Q_INVOKABLE GadgetChild();

		int intProperty() const;
		void setIntProperty(int intProperty);

	private:
		int m_intProperty;
};

Q_DECLARE_METATYPE(GadgetChild *)
Q_DECLARE_METATYPE(Array<GadgetChild *>)

#endif // GADGETCHILD_H
