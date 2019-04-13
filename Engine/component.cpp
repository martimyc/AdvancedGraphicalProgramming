#include "component.h"

#include "entity.h"

Component::Component(Entity* entity): entity(entity)
{}

Component::~Component()
{}
