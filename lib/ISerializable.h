#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QJsonValue>

class SerializerBase;

class ISerializable
{
	public:
		virtual QJsonValue serialize(const SerializerBase &serializer) const = 0;
};

#endif // ISERIALIZABLE_H
