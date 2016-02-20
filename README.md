QJsonSerializer
===============

Summary
-------
A library for serializing and deserializing complex Qt object graphs to and from JSON

Installation
-----------

Linux:

```
qmake
make
sudo make install
```

Windows (MSVC):

```
qmake
nmake
nmake install
```

Windows (MinGW):

```
qmake
mingw32-make
mingw32-make install
```

Getting started
------------

```
CONFIG += jsonserializer
```

```C++
#include <QJsonSerializer>
```

See the test cases for code examples.

What works
----------

* Serialization and deserialization of complex object graphs, including nested objects and collections 

What does not work
------------------

* Serialization and deserialization of scalar collections (QList<int> etc) is currently untested.
* Serialization and deserialization of polymorphic objects is currently untested.
* Serialization of Array<T> as root object is currently unsupported, deserialization works though.
