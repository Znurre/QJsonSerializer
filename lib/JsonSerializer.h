#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QByteArray>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QJsonArray>

#include "Array.h"
#include "IDeserializer.h"

class JsonSerializer
{
	public:
		template<class TReturn>
		TReturn deserialize(const QByteArray &data)
		{
			const Deserializer<TReturn> subject;

			return subject.deserialize(data);
		}

		template<class TReturn>
		TReturn deserialize(QIODevice *device)
		{
			const QByteArray &data = device->readAll();
			const Deserializer<TReturn> subject;

			return subject.deserialize(data);
		}

		QJsonObject serializeObject(const QObject &instance)
		{
			QJsonObject root;

			const QMetaObject *metaObject = instance.metaObject();

			for (int i = metaObject->propertyOffset()
				; i < metaObject->propertyCount()
				; i++)
			{
				const QMetaProperty &property = metaObject->property(i);
				const QByteArray &name = property.name();

				const QVariant &value = property.read(&instance);
				const QVariant::Type type = value.type();

				if (type == QVariant::UserType)
				{
					const int userType = property.userType();
					const int flags = QMetaType::typeFlags(userType);

					if (flags & QMetaType::PointerToQObject)
					{
						QObject *object = value.value<QObject *>();

						if (object)
						{
							root[name] = serializeObject(*object);
						}
					}
					else
					{
						const IElementFactory *factory = (IElementFactory *)value.data();
						const QList<QObject *> &objects = factory->toObjectList();

						QJsonArray array;

						for (QObject *element : objects)
						{
							array << serializeObject(*element);
						}

						root[name] = array;
					}
				}
				else
				{
					root[name] = QJsonValue::fromVariant(value);
				}
			}

			return root;
		}

		QByteArray serialize(const QObject &object)
		{
			const QJsonObject &root = serializeObject(object);

			const QJsonDocument document(root);
			const QByteArray &json = document.toJson(QJsonDocument::Compact);

			return json;
		}
};

#endif // JSONSERIALIZER_H
