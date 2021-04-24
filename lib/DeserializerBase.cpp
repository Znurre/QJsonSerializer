#include <QMetaProperty>
#include <QDebug>

#include "IObjectFactory.h"
#include "DeserializerBase.h"
#include "Array.h"
#include "Dictionary.h"

DeserializerBase::DeserializerBase(const IObjectFactory &factory)
	: m_factory(factory)
{

}

void DeserializerBase::deserializeDictionary(const QJsonObject &object, IDictionary &target) const
{
	target.initialize();

	for (const QString &key : object.keys())
	{
		auto value = object[key];

		if (target.isScalar())
		{
			auto variant = value.toVariant();

			target.addElement(key, variant);
		}
		else
		{
			void *child = target.createElement(key, m_factory);

			const QMetaObject *metaObject = target.metaObject();
			const QJsonObject &elementObject = value.toObject();

			deserializeObject(elementObject, child, metaObject);
		}
	}
}

void DeserializerBase::deserializeArray(const QJsonArray &array, IArray &target) const
{
	target.initialize();

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
			void *child = target.createElement(m_factory);

			const QMetaObject *metaObject = target.metaObject();
			const QJsonObject &elementObject = element.toObject();

			deserializeObject(elementObject, child, metaObject);
		}
	}
}

void DeserializerBase::deserializeObject(const QJsonObject &object, void *instance, const QMetaObject *metaObject) const
{
	if (!instance)
	{
		return;
	}

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
					const QJsonObject &childObject = value.toObject();

					if (childMetaObject)
					{
						void *child = m_factory.create(childMetaObject);

						const QVariant variant(userType, &child);

						deserializeObject(childObject, child, childMetaObject);

						property.writeOnGadget(instance, variant);
					}
					else
					{
						auto variant = property.readOnGadget(instance);
						auto &factory = *(IDictionary *)variant.data();

						deserializeDictionary(childObject, factory);
					}
				}
				else
				{
					qCritical() << "Unknown user type for property" << name;
				}

				break;
			}

			case QJsonValue::Array:
			{
				const QVariant &variant = property.readOnGadget(instance);
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

				property.writeOnGadget(instance, variant);

				break;
			}
		}
	}
}
