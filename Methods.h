#pragma once
#include "Entity.h"
#include <vector>
using namespace std;
namespace Methods {
	inline void increaseBar(vector<Entity>& p_v,Entity& p_e) {
		p_e.setX(p_e.getX() + p_e.getCurrentFrame().w + 1);
		p_v.push_back(p_e);
	}
	inline void decreaseBar(vector<Entity>& p_v, Entity& p_e) {
		p_e.setX(p_e.getX() - p_e.getCurrentFrame().w - 1);
		p_v.pop_back();
	}
	inline void increaseInventory(vector<Placeholder>& p_v, Placeholder&p_e) {
		p_e.setX(p_e.getX() + p_e.getCurrentFrame().w/2);
		p_v.push_back(p_e);
	}
	inline void decreaseInventory(vector<Placeholder>& p_v, Placeholder& p_e) {
		p_e.setX(p_e.getX() - p_e.getCurrentFrame().w/2);
		p_v.pop_back();
	}
};