#include <QMetaProperty>

#include "SerializerBase.h"
#include "Array.h"

QJsonArray SerializerBase::serializeArray(const IElementFactory &source) const
{
	QJsonArray array;

	const QList<QObject *> &objects = source.toObjectList();

	for (QObject *element : objects)
	{
		array << serializeObject(element);
	}

	return array;
}

QJsonObject SerializerBase::serializeObject(const QObject *source) const
{
	QJsonObject target;

	const QMetaObject *metaObject = source->metaObject();

	for (int i = metaObject->propertyOffset()
		; i < metaObject->propertyCount()
		; i++)
	{
		const QMetaProperty &property = metaObject->property(i);
		const QByteArray &name = property.name();

		const QVariant &value = property.read(source);
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
					target[name] = serializeObject(object);
				}
			}
			else
			{
				const IElementFactory *factory = (IElementFactory *)value.data();

				target[name] = serializeArray(*factory);
			}
		}
		else
		{
			target[name] = QJsonValue::fromVariant(value);
		}
	}

	return target;
}
