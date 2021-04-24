#include <QMetaProperty>

#include "SerializerBase.h"
#include "Array.h"

QJsonArray SerializerBase::serializeArray(const IArray &source) const
{
	const QVariantList &elements = source.toVariantList();
	const QMetaObject *metaObject = source.metaObject();

	if (source.isScalar())
	{
		return QJsonArray::fromVariantList(elements);
	}

	QJsonArray array;

	for (const QVariant &element : elements)
	{
		const void *object = *reinterpret_cast<void *const*>(element.constData());

		array.append(serializeObject(object, metaObject));
	}

	return array;
}

QJsonObject SerializerBase::serializeObject(const void *source, const QMetaObject *metaObject) const
{
	QJsonObject target;

	for (int i = metaObject->propertyOffset()
		; i < metaObject->propertyCount()
		; i++)
	{
		const QMetaProperty &property = metaObject->property(i);
		const QByteArray &name = property.name();

		const QVariant &value = property.readOnGadget(source);
		const QVariant::Type type = value.type();

		if (type == QVariant::UserType)
		{
			const int userType = property.userType();
			const int flags = QMetaType::typeFlags(userType);

			if (flags & QMetaType::PointerToQObject || flags & QMetaType::PointerToGadget)
			{
				const void *object = *reinterpret_cast<void *const*>(value.constData());

				if (object)
				{
					const QMetaObject *childMetaObject = QMetaType::metaObjectForType(userType);

					target[name] = serializeObject(object, childMetaObject);
				}
			}
			else
			{
				const ISerializable *serializable = (ISerializable *)value.data();

				target[name] = serializable->serialize(*this);
			}
		}
		else
		{
			target[name] = QJsonValue::fromVariant(value);
		}
	}

	return target;
}
