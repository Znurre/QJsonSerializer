#include <QMetaProperty>
#include <QDebug>

#include "DeserializerBase.h"
#include "Array.h"

void DeserializerBase::deserializeArray(const QJsonArray &array, IArray &target) const
{
	for (int j = 0; j < array.count(); j++)
	{
		const QJsonValue &element = array[j];

		if (target.isScalar())
		{
			const QVariant &variant = element.toVariant();

			target.addElement(variant);
		}
		else
		{
			QObject *child = target.createElement();

			const QJsonObject &elementObject = element.toObject();

			deserializeObject(elementObject, child);
		}
	}
}

void DeserializerBase::deserializeObject(const QJsonObject &object, QObject *instance) const
{
	if (!instance)
	{
		return;
	}

	const QMetaObject *metaObject = instance->metaObject();

	for (int i = metaObject->propertyOffset()
		 ; i < metaObject->propertyCount()
		 ; i++)
	{
		const QMetaProperty &property = metaObject->property(i);
		const QByteArray &name = property.name();

		const QJsonValue &value = object.value(name);
		const QJsonValue::Type type = value.type();

		switch (type)
		{
			case QJsonValue::Object:
			{
				const int userType = property.userType();

				if (userType != QMetaType::UnknownType)
				{
					const QMetaType type(userType);
					const QMetaObject *childMetaObject = type.metaObject();

					QObject *child = childMetaObject->newInstance();

					if (!child)
					{
						qCritical() << "Failed to create an instance of type" << childMetaObject->className();
						qCritical() << "Did you forget to declare a public parameterless Q_INVOKABLE constructor?";
					}

					const QJsonObject &childObject = value.toObject();
					const QVariant &variant = QVariant::fromValue(child);

					deserializeObject(childObject, child);

					property.write(instance, variant);
				}
				else
				{
					qCritical() << "Unknown user type for property" << name;
				}

				break;
			}

			case QJsonValue::Array:
			{
				const QVariant &variant = property.read(instance);
				const QJsonArray &array = value.toArray();

				IArray &factory = *(IArray *)variant.data();

				deserializeArray(array, factory);

				break;
			}

			case QJsonValue::Undefined:
			{
				break;
			}

			default:
			{
				const QVariant &variant = value.toVariant();

				property.write(instance, variant);

				break;
			}
		}
	}
}
