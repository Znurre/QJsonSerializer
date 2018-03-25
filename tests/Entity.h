#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QDateTime>

#include "Child.h"

class Entity : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Child *child READ child WRITE setChild)
	Q_PROPERTY(Array<Child *> children READ children WRITE setChildren)

	Q_PROPERTY(QString stringProperty READ stringProperty WRITE setStringProperty)
	Q_PROPERTY(QDateTime dateTimeProperty READ dateTimeProperty WRITE setDateTimeProperty)
	Q_PROPERTY(Array<int> intCollection READ intCollection WRITE setIntCollection)
	Q_PROPERTY(Array<QString> stringCollection READ stringCollection WRITE setStringCollection)

	Q_PROPERTY(int intProperty READ intProperty WRITE setIntProperty)
	Q_PROPERTY(float floatProperty READ floatProperty WRITE setFloatProperty)

	public:
		Q_INVOKABLE Entity();

		Child *child() const;
		void setChild(Child *child);

		Array<Child *> children() const;
		void setChildren(const Array<Child *> &children);

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
		Child *m_child;
		Array<Child *> m_children;

		QString m_stringProperty;
		QDateTime m_dateTimeProperty;
		Array<int> m_intCollection;
		Array<QString> m_stringCollection;

		int m_intProperty;
		float m_floatProperty;
};

Q_DECLARE_METATYPE(Entity *)

#endif // ENTITY_H
