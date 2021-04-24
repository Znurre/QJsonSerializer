#include "Dictionary.h"
#include "SerializerBase.h"

QJsonValue IDictionary::serialize(const SerializerBase &serializer) const
{
	auto elements = toVariantMap();

	QJsonObject target;

	for (const auto &element : elements)
	{
		auto key = elements.key(element);
		auto object = *reinterpret_cast<void *const*>(element.constData());

		target[key] = serializer.serializeObject(object, metaObject());
	}

	return target;
}
