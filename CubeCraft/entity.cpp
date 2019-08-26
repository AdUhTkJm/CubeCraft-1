#include"entity.h"
#include"block.h"

cc::entity::entity(glm::vec3 pos, glm::vec3 rot) noexcept: pos(pos), fr(rot) {
}

cc::player::player() noexcept: entity(glm::vec3(0, 2, 0)) {
}

glm::vec3 cc::entity::position() const noexcept {
	return pos;
}

glm::vec3 cc::entity::front() const noexcept {
	return fr;
}

void cc::entity::front(glm::vec3 x) noexcept {
	fr = x;
}

glm::vec3 cc::player::move(glm::vec3 delta) {
	return pos += delta;
}

cc::player cc::ent_player;