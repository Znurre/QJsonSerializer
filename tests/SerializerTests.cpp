#include <QString>
#include <QtTest>

#include "QJsonSerializer.h"
#include "Entity.h"
#include "Child.h"

class SerializerTests : public QObject
{
	Q_OBJECT

	public:
		SerializerTests()
		{
			qRegisterMetaType<Child *>();
		}

	private Q_SLOTS:
		void shouldBeAbleToDeserializeStringProperties()
		{
			const QByteArray json = R"({ "stringProperty": "foo" })";

			const Entity *entity = m_serializer.deserialize<Entity *>(json);

			QVERIFY(entity->stringProperty() == "foo");
		}

		void shouldBeAbleToDeserializeIntProperties()
		{
			const QByteArray json = R"({ "intProperty": 42 })";

			const Entity *entity = m_serializer.deserialize<Entity *>(json);

			QVERIFY(entity->intProperty() == 42);
		}

		void shouldBeAbleToDeserializeFloatProperties()
		{
			const QByteArray json = R"({ "floatProperty": 42.5 })";

			const Entity *entity = m_serializer.deserialize<Entity *>(json);

			QVERIFY(entity->floatProperty() == 42.5);
		}

		void shouldBeAbleToDeserializeDateTimeProperties()
		{
			const QByteArray json = R"({ "dateTimeProperty": "2016-02-20T13:37:00" })";

			const Entity *entity = m_serializer.deserialize<Entity *>(json);

			QVERIFY(entity->dateTimeProperty() == QDateTime::fromString("2016-02-20 13:37", "yyyy-MM-dd hh:mm"));
		}

		void shouldBeAbleToDeserializeComplexProperties()
		{
			const QByteArray json = R"({ "child": { "intProperty": 6 }})";

			const Entity *entity = m_serializer.deserialize<Entity *>(json);
			const Child *child = entity->child();

			QVERIFY(child);
			QVERIFY(child->intProperty() == 6);
		}

		void shouldBeAbleToDeserializeArrayProperties()
		{
			const QByteArray json = R"({ "children": [ { "intProperty": 1 }, { "intProperty": 2 } ]})";

			const Entity *entity = m_serializer.deserialize<Entity *>(json);
			const Array<Child> &children = entity->children();

			QVERIFY(children.count() == 2);
			QVERIFY(children[0]->intProperty() == 1);
			QVERIFY(children[1]->intProperty() == 2);
		}

		void shouldBeAbleToDeserializeArrayDocument()
		{
			const QByteArray json = R"([{ "intProperty": 1 }, { "intProperty": 2 }])";

			const Array<Entity> &entities = m_serializer.deserialize<Array<Entity>>(json);

			QVERIFY(entities.count() == 2);
			QVERIFY(entities[0]->intProperty() == 1);
			QVERIFY(entities[1]->intProperty() == 2);
		}

		void shouldBeAbleToSerializeStringProperties()
		{
			Entity entity;
			entity.setStringProperty("foo");

			const QByteArray &json = m_serializer.serialize(&entity);

			QVERIFY2(json == R"({"children":[],"dateTimeProperty":null,"floatProperty":0,"intProperty":0,"stringProperty":"foo"})", json);
		}

		void shouldBeAbleToSerializeIntProperties()
		{
			Entity entity;
			entity.setIntProperty(42);

			const QByteArray &json = m_serializer.serialize(&entity);

			QVERIFY2(json == R"({"children":[],"dateTimeProperty":null,"floatProperty":0,"intProperty":42,"stringProperty":""})", json);
		}

		void shouldBeAbleToSerializeFloatProperties()
		{
			Entity entity;
			entity.setFloatProperty(42.5);

			const QByteArray &json = m_serializer.serialize(&entity);

			QVERIFY2(json == R"({"children":[],"dateTimeProperty":null,"floatProperty":42.5,"intProperty":0,"stringProperty":""})", json);
		}

		void shouldBeAbleToSerializeDateTimeProperties()
		{
			Entity entity;
			entity.setDateTimeProperty(QDateTime::fromString("2016-02-20 13:37", "yyyy-MM-dd hh:mm"));

			const QByteArray &json = m_serializer.serialize(&entity);

			QVERIFY2(json == R"({"children":[],"dateTimeProperty":"2016-02-20T13:37:00","floatProperty":0,"intProperty":0,"stringProperty":""})", json);
		}

		void shouldBeAbleToSerializeComplexProperties()
		{
			Child child;
			child.setIntProperty(6);

			Entity entity;
			entity.setChild(&child);

			const QByteArray &json = m_serializer.serialize(&entity);

			QVERIFY2(json == R"({"child":{"intProperty":6},"children":[],"dateTimeProperty":null,"floatProperty":0,"intProperty":0,"stringProperty":""})", json);
		}

		void shouldBeAbleToSerializeArrayProperties()
		{
			Child child1;
			child1.setIntProperty(1);

			Child child2;
			child2.setIntProperty(2);

			Array<Child> array;
			array << &child1;
			array << &child2;

			Entity entity;
			entity.setChildren(array);

			const QByteArray &json = m_serializer.serialize(&entity);

			QVERIFY2(json == R"({"children":[{"intProperty":1},{"intProperty":2}],"dateTimeProperty":null,"floatProperty":0,"intProperty":0,"stringProperty":""})", json);
		}

	private:
		QJsonSerializer m_serializer;
};

QTEST_APPLESS_MAIN(SerializerTests)

#include "SerializerTests.moc"
