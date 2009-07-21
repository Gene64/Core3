/*
 *	server/zone/objects/tangible/Container.h generated by engine3 IDL compiler 0.60
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "engine/orb/DistributedObjectBroker.h"

#include "server/zone/objects/tangible/TangibleObject.h"

#include "server/zone/objects/scene/SceneObject.h"

#include "engine/lua/LuaObject.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {

class Container : public TangibleObject {
public:
	Container(LuaObject* templateData, SceneObject* par = NULL);

	bool addObject(SceneObject* obj);

	bool removeObject(SceneObject* obj);

protected:
	Container(DummyConstructorParameter* param);

	virtual ~Container();

	friend class ContainerHelper;
};

} // namespace tangible
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::tangible;

namespace server {
namespace zone {
namespace objects {
namespace tangible {

class ContainerImplementation : public TangibleObjectImplementation {

public:
	ContainerImplementation(LuaObject* templateData, SceneObject* par = NULL);

	bool addObject(SceneObject* obj);

	bool removeObject(SceneObject* obj);

	Container* _this;

	operator Container*();
protected:
	virtual ~ContainerImplementation();

	void _setStub(DistributedObjectStub* stub);
	DistributedObjectStub* _getStub();

	void _serializationHelperMethod();

	friend class Container;
};

class ContainerAdapter : public TangibleObjectAdapter {
public:
	ContainerAdapter(ContainerImplementation* impl);

	Packet* invokeMethod(sys::uint32 methid, DistributedMethod* method);

	bool addObject(SceneObject* obj);

	bool removeObject(SceneObject* obj);

};

class ContainerHelper : public DistributedObjectClassHelper, public Singleton<ContainerHelper> {
	static ContainerHelper* staticInitializer;

public:
	ContainerHelper();

	void finalizeHelper();

	DistributedObject* instantiateObject();

	DistributedObjectAdapter* createAdapter(DistributedObjectStub* obj);

	friend class Singleton<ContainerHelper>;
};

} // namespace tangible
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::tangible;

#endif /*CONTAINER_H_*/
