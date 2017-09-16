#include <QMetaProperty>

#include "SerializerBase.h"
#include "Array.h"

QJsonArray SerializerBase::serializeArray(const IArray &source) const
{
	const QVariantList &elements = source.toVariantList();

	if (source.isScalar())
	{
		return QJsonArray::fromVariantList(elements);
	}

	QJsonArray array;

	for (const QVariant &element : elements)
	{
		const QObject *object = element.value<QObject *>();

		array.append(serializeObject(object));
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
				const IArray *factory = (IArray *)value.data();

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
