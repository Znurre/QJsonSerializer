#ifndef GADGETENTITY_H
#define GADGETENTITY_H

#include <QObject>
#include <QDateTime>

#include "GadgetChild.h"

class GadgetEntity : public QObject
{
	Q_OBJECT

	Q_PROPERTY(GadgetChild *child READ child WRITE setChild)
	Q_PROPERTY(Array<GadgetChild *> children READ children WRITE setChildren)

	Q_PROPERTY(QString stringProperty READ stringProperty WRITE setStringProperty)
	Q_PROPERTY(QDateTime dateTimeProperty READ dateTimeProperty WRITE setDateTimeProperty)
	Q_PROPERTY(Array<int> intCollection READ intCollection WRITE setIntCollection)
	Q_PROPERTY(Array<QString> stringCollection READ stringCollection WRITE setStringCollection)

	Q_PROPERTY(int intProperty READ intProperty WRITE setIntProperty)
	Q_PROPERTY(float floatProperty READ floatProperty WRITE setFloatProperty)

	public:
		Q_INVOKABLE GadgetEntity();

		GadgetChild *child() const;
		void setChild(GadgetChild *child);

		Array<GadgetChild *> children() const;
		void setChildren(const Array<GadgetChild *> &children);

		QString stringProperty() const;
		void setStringProperty(const QString &stringProperty);

		QDateTime dateTimeProperty() const;
		void setDateTimeProperty(const QDateTime &dateTimeProperty);

		Array<int> intCollection() const;
		void setIntCollection(const Array<int> &intCollection);

		Array<QString> stringCollection() const;
		void setStringCollection(const Array<QString> &stringCollection);

		int intProperty() const;
		void setIntProperty(int intProperty);

		float floatProperty() const;
		void setFloatProperty(float floatProperty);

	private:
		GadgetChild *m_child;
		Array<GadgetChild *> m_children;

		QString m_stringProperty;
		QDateTime m_dateTimeProperty;
		Array<int> m_intCollection;
		Array<QString> m_stringCollection;

		int m_intProperty;
		float m_floatProperty;
};

#endif // GADGETENTITY_H
