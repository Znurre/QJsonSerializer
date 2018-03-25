#include <QString>
#include <QtTest>

#include "QJsonSerializer.h"
#include "Entity.h"
#include "Child.h"
#include "GadgetEntity.h"

class SerializerTests : public QObject
{
	Q_OBJECT

	public:
		SerializerTests()
		{
			qRegisterMetaType<Child *>();
			qRegisterMetaType<GadgetChild *>();
			qRegisterMetaType<GadgetChild>();
			qRegisterMetaType<Entity *>();
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
			const Array<Child *> &children = entity->children();

			QVERIFY(children.count() == 2);
			QVERIFY(children[0]->intProperty() == 1);
			QVERIFY(children[1]->intProperty() == 2);
		}

		void shouldBeAbleToDeserializeArrayDocument()
		{
			const QByteArray json = R"([{ "intProperty": 1 }, { "intProperty": 2 }])";

			const Array<Entity *> &entities = m_serializer.deserialize<Array<Entity *>>(json);

			QVERIFY(entities.count() == 2);
			QVERIFY(entities[0]->intProperty() == 1);
			QVERIFY(entities[1]->intProperty() == 2);
		}

		void shouldBeAbleToDeserializeArrayOfIntProperties()
		{
			const QByteArray json = R"({ "intCollection": [1, 2, 3] })";

			const Entity *entity = m_serializer.deserialize<Entity *>(json);
			const Array<int> &intCollection = entity->intCollection();

			QCOMPARE(intCollection.count(), 3);
			QCOMPARE(intCollection[0], 1);
			QCOMPARE(intCollection[1], 2);
			QCOMPARE(intCollection[2], 3);
		}

		void shouldBeAbleToDeserializeArrayOfStringProperties()
		{
			const QByteArray json = R"({ "stringCollection": ["hi", "hello", "good bye"] })";

			const Entity *entity = m_serializer.deserialize<Entity *>(json);
			const Array<QString> &intCollection = entity->stringCollection();

			QCOMPARE(intCollection.count(), 3);
			QCOMPARE(intCollection[0], QStringLiteral("hi"));
			QCOMPARE(intCollection[1], QStringLiteral("hello"));
			QCOMPARE(intCollection[2], QStringLiteral("good bye"));
		}

		void shouldBeAbleToDeserializeOntoInstance()
		{
			const QByteArray json = R"({ "intProperty": 42 })";

			Entity entity;

			m_serializer.deserialize(json, &entity);

			QCOMPARE(entity.intProperty(), 42);
		}

		void shouldBeAbleToSerializeStringProperties()
		{
			Entity entity;
			entity.setStringProperty("foo");

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":null,"floatProperty":0,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":"foo"})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeIntProperties()
		{
			Entity entity;
			entity.setIntProperty(42);

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":null,"floatProperty":0,"intCollection":[],"intProperty":42,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeFloatProperties()
		{
			Entity entity;
			entity.setFloatProperty(42.5);

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":null,"floatProperty":42.5,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeDateTimeProperties()
		{
			Entity entity;
			entity.setDateTimeProperty(QDateTime::fromString("2016-02-20 13:37", "yyyy-MM-dd hh:mm"));

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":"2016-02-20T13:37:00","floatProperty":0,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeComplexProperties()
		{
			Child child;
			child.setIntProperty(6);

			Entity entity;
			entity.setChild(&child);

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"child":{"intProperty":6},"children":[],"dateTimeProperty":null,"floatProperty":0,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeArrayProperties()
		{
			Child child1;
			child1.setIntProperty(1);

			Child child2;
			child2.setIntProperty(2);

			Array<Child *> array;
			array << &child1;
			array << &child2;

			Entity entity;
			entity.setChildren(array);

			const QByteArray &actual = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[{"intProperty":1},{"intProperty":2}],"dateTimeProperty":null,"floatProperty":0,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(actual, expected);
		}

		void shouldBeAbleToSerializeArrayDocument()
		{
			Child entity1;
			entity1.setIntProperty(1);

			Child entity2;
			entity2.setIntProperty(2);

			Array<Child *> entities;
			entities << &entity1;
			entities << &entity2;

			const QByteArray &actual = m_serializer.serialize(entities);
			const QByteArray expected(R"([{"intProperty":1},{"intProperty":2}])");

			QCOMPARE(actual, expected);
		}

		void shouldBeAbleToSerializeArrayOfIntProperties()
		{
			Array<int> scalars;
			scalars << 1;
			scalars << 2;

			Entity entity;
			entity.setIntCollection(scalars);

			const QByteArray &actual = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":null,"floatProperty":0,"intCollection":[1,2],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(actual, expected);
		}

		void shouldBeAbleToDeserializeArrayOfStringWithTarget()
		{
			Array<QString> target;

			const QByteArray json = R"([ "foo", "bar" ])";

			m_serializer.deserialize(json, target);

			QCOMPARE(target[0], QStringLiteral("foo"));
			QCOMPARE(target[1], QStringLiteral("bar"));
		}

		void shouldBeAbleToDeserializePrimitiveDocuments()
		{
			const QByteArray json = R"("foo")";
			const QString &target = m_serializer.deserialize<QString>(json);

			QCOMPARE(target, QStringLiteral("foo"));
		}

		void shouldBeAbleToDeserializeFromJSonObject()
		{
			QJsonObject child;
			child["intProperty"] = 22;

			QJsonArray children;
			children.append(child);

			QJsonObject object;
			object["floatProperty"] = 10.5f;
			object["intProperty"] = 2;
			object["children"] = children;

			Entity entity;

			m_serializer.deserialize(object, &entity);

			QCOMPARE(entity.floatProperty(), 10.5f);
			QCOMPARE(entity.intProperty(), 2);

			const Array<Child *> &childArray = entity.children();

			QCOMPARE(childArray.count(), 1);
			QCOMPARE(childArray[0]->intProperty(), 22);
		}

		void shouldBeAbleToDeserializeStringProperties_Gadget()
		{
			const QByteArray json = R"({ "stringProperty": "foo" })";

			const GadgetEntity *entity = m_serializer.deserialize<GadgetEntity *>(json);

			QVERIFY(entity->stringProperty() == "foo");
		}

		void shouldBeAbleToDeserializeIntProperties_Gadget()
		{
			const QByteArray json = R"({ "intProperty": 42 })";

			const GadgetEntity *entity = m_serializer.deserialize<GadgetEntity *>(json);

			QVERIFY(entity->intProperty() == 42);
		}

		void shouldBeAbleToDeserializeFloatProperties_Gadget()
		{
			const QByteArray json = R"({ "floatProperty": 42.5 })";

			const GadgetEntity *entity = m_serializer.deserialize<GadgetEntity *>(json);

			QVERIFY(entity->floatProperty() == 42.5);
		}

		void shouldBeAbleToDeserializeDateTimeProperties_Gadget()
		{
			const QByteArray json = R"({ "dateTimeProperty": "2016-02-20T13:37:00" })";

			const GadgetEntity *entity = m_serializer.deserialize<GadgetEntity *>(json);

			QVERIFY(entity->dateTimeProperty() == QDateTime::fromString("2016-02-20 13:37", "yyyy-MM-dd hh:mm"));
		}

		void shouldBeAbleToDeserializeComplexProperties_Gadget()
		{
			const QByteArray json = R"({ "child": { "intProperty": 6 }})";

			const GadgetEntity *entity = m_serializer.deserialize<GadgetEntity *>(json);
			const GadgetChild *child = entity->child();

			QVERIFY(child);
			QVERIFY(child->intProperty() == 6);
		}

		void shouldBeAbleToDeserializeArrayProperties_Gadget()
		{
			const QByteArray json = R"({ "children": [ { "intProperty": 1 }, { "intProperty": 2 } ]})";

			const GadgetEntity *entity = m_serializer.deserialize<GadgetEntity *>(json);
			const Array<GadgetChild *> &children = entity->children();

			QVERIFY(children.count() == 2);
			QVERIFY(children[0]->intProperty() == 1);
			QVERIFY(children[1]->intProperty() == 2);
		}

		void shouldBeAbleToDeserializeArrayDocument_Gadget()
		{
			const QByteArray json = R"([{ "intProperty": 1 }, { "intProperty": 2 }])";

			const Array<GadgetEntity *> &entities = m_serializer.deserialize<Array<GadgetEntity *>>(json);

			QVERIFY(entities.count() == 2);
			QVERIFY(entities[0]->intProperty() == 1);
			QVERIFY(entities[1]->intProperty() == 2);
		}

		void shouldBeAbleToDeserializeArrayOfIntProperties_Gadget()
		{
			const QByteArray json = R"({ "intCollection": [1, 2, 3] })";

			const GadgetEntity *entity = m_serializer.deserialize<GadgetEntity *>(json);
			const Array<int> &intCollection = entity->intCollection();

			QCOMPARE(intCollection.count(), 3);
			QCOMPARE(intCollection[0], 1);
			QCOMPARE(intCollection[1], 2);
			QCOMPARE(intCollection[2], 3);
		}

		void shouldBeAbleToDeserializeArrayOfStringProperties_Gadget()
		{
			const QByteArray json = R"({ "stringCollection": ["hi", "hello", "good bye"] })";

			const GadgetEntity *entity = m_serializer.deserialize<GadgetEntity *>(json);
			const Array<QString> &intCollection = entity->stringCollection();

			QCOMPARE(intCollection.count(), 3);
			QCOMPARE(intCollection[0], QStringLiteral("hi"));
			QCOMPARE(intCollection[1], QStringLiteral("hello"));
			QCOMPARE(intCollection[2], QStringLiteral("good bye"));
		}

		void shouldBeAbleToDeserializeOntoInstance_Gadget()
		{
			const QByteArray json = R"({ "intProperty": 42 })";

			GadgetEntity entity;

			m_serializer.deserialize(json, &entity);

			QCOMPARE(entity.intProperty(), 42);
		}

		void shouldBeAbleToSerializeStringProperties_Gadget()
		{
			GadgetEntity entity;
			entity.setStringProperty("foo");

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":null,"floatProperty":0,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":"foo"})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeIntProperties_Gadget()
		{
			GadgetEntity entity;
			entity.setIntProperty(42);

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":null,"floatProperty":0,"intCollection":[],"intProperty":42,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeFloatProperties_Gadget()
		{
			GadgetEntity entity;
			entity.setFloatProperty(42.5);

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":null,"floatProperty":42.5,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeDateTimeProperties_Gadget()
		{
			GadgetEntity entity;
			entity.setDateTimeProperty(QDateTime::fromString("2016-02-20 13:37", "yyyy-MM-dd hh:mm"));

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":"2016-02-20T13:37:00","floatProperty":0,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeComplexProperties_Gadget()
		{
			GadgetChild child;
			child.setIntProperty(6);

			GadgetEntity entity;
			entity.setChild(&child);

			const QByteArray &json = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"child":{"intProperty":6},"children":[],"dateTimeProperty":null,"floatProperty":0,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(json, expected);
		}

		void shouldBeAbleToSerializeArrayProperties_Gadget()
		{
			GadgetChild child1;
			child1.setIntProperty(1);

			GadgetChild child2;
			child2.setIntProperty(2);

			Array<GadgetChild *> array;
			array << &child1;
			array << &child2;

			GadgetEntity entity;
			entity.setChildren(array);

			const QByteArray &actual = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[{"intProperty":1},{"intProperty":2}],"dateTimeProperty":null,"floatProperty":0,"intCollection":[],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(actual, expected);
		}

		void shouldBeAbleToSerializeArrayDocument_Gadget()
		{
			GadgetChild entity1;
			entity1.setIntProperty(1);

			GadgetChild entity2;
			entity2.setIntProperty(2);

			Array<GadgetChild *> entities;
			entities << &entity1;
			entities << &entity2;

			const QByteArray &actual = m_serializer.serialize(entities);
			const QByteArray expected(R"([{"intProperty":1},{"intProperty":2}])");

			QCOMPARE(actual, expected);
		}

		void shouldBeAbleToSerializeArrayOfIntProperties_Gadget()
		{
			Array<int> scalars;
			scalars << 1;
			scalars << 2;

			GadgetEntity entity;
			entity.setIntCollection(scalars);

			const QByteArray &actual = m_serializer.serialize(&entity);
			const QByteArray expected(R"({"children":[],"dateTimeProperty":null,"floatProperty":0,"intCollection":[1,2],"intProperty":0,"stringCollection":[],"stringProperty":""})");

			QCOMPARE(actual, expected);
		}

		void shouldBeAbleToDeserializeArrayOfStringWithTarget_Gadget()
		{
			Array<QString> target;

			const QByteArray json = R"([ "foo", "bar" ])";

			m_serializer.deserialize(json, target);

			QCOMPARE(target[0], QStringLiteral("foo"));
			QCOMPARE(target[1], QStringLiteral("bar"));
		}

		void shouldBeAbleToDeserializePrimitiveDocuments_Gadget()
		{
			const QByteArray json = R"("foo")";
			const QString &target = m_serializer.deserialize<QString>(json);

			QCOMPARE(target, QStringLiteral("foo"));
		}

		void shouldBeAbleToDeserializeFromJSonObject_Gadget()
		{
			QJsonObject child;
			child["intProperty"] = 22;

			QJsonArray children;
			children.append(child);

			QJsonObject object;
			object["floatProperty"] = 10.5f;
			object["intProperty"] = 2;
			object["children"] = children;

			GadgetEntity entity;

			m_serializer.deserialize(object, &entity);

			QCOMPARE(entity.floatProperty(), 10.5f);
			QCOMPARE(entity.intProperty(), 2);

			const Array<GadgetChild *> &childArray = entity.children();

			QCOMPARE(childArray.count(), 1);
			QCOMPARE(childArray[0]->intProperty(), 22);
		}

	private:
		QJsonSerializer m_serializer;
};

QTEST_APPLESS_MAIN(SerializerTests)

#include "SerializerTests.moc"
