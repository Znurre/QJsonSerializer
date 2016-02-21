#ifndef DESERIALIZERBASE_H
#define DESERIALIZERBASE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>

class IArray;

class DeserializerBase
{
	protected:
		void deserializeArray(const QJsonArray &array, IArray &target) const;
		void deserializeObject(const QJsonObject &object, QObject *instance) const;
};

#endif // DESERIALIZERBASE_H
