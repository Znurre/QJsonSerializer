#include "Array.h"
#include "SerializerBase.h"

QJsonValue IArray::serialize(const SerializerBase &serializer) const
{
	return serializer.serializeArray(*this);
}
