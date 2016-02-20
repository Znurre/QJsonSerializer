#ifndef DESERIALIZERBASE_H
#define DESERIALIZERBASE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>

class IElementFactory;

class DeserializerBase
{
	protected:
		void deserializeArray(const QJsonArray &array, IElementFactory &target) const;
		void deserializeObject(const QJsonObject &object, QObject *instance) const;
};

#endif // DESERIALIZERBASE_H
