#include "component.h"

#include "entity.h"

Component::Component(Entity* entity, bool draw): entity(entity), draw(draw)
{}

Component::~Component()
{}
