#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QDateTime>

#include "Child.h"

class Entity : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Child *child READ child WRITE setChild)
	Q_PROPERTY(Array<Child> children READ children WRITE setChildren)

	Q_PROPERTY(QString stringProperty READ stringProperty WRITE setStringProperty)
	Q_PROPERTY(QDateTime dateTimeProperty READ dateTimeProperty WRITE setDateTimeProperty)

	Q_PROPERTY(int intProperty READ intProperty WRITE setIntProperty)
	Q_PROPERTY(float floatProperty READ floatProperty WRITE setFloatProperty)

	public:
		Entity();

		Child *child() const;
		void setChild(Child *child);

		Array<Child> children() const;
		void setChildren(const Array<Child> &children);

		QString stringProperty() const;
		void setStringProperty(const QString &stringProperty);

		int intProperty() const;
		void setIntProperty(int intProperty);

		float floatProperty() const;
		void setFloatProperty(float floatProperty);

		QDateTime dateTimeProperty() const;
		void setDateTimeProperty(const QDateTime &dateTimeProperty);

	private:
		Child *m_child;
		Array<Child> m_children;

		QString m_stringProperty;
		QDateTime m_dateTimeProperty;

		int m_intProperty;
		float m_floatProperty;
};

#endif // ENTITY_H
