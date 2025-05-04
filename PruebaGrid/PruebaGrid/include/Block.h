#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <set>
#include <string>

class Block: public IGameEntity {
private:
	string texture;

public:
	virtual void process();
	virtual set<int> getThingsToDraw();
};

#endif