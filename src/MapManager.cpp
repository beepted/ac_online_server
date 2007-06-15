#include "MapManager.h"
#include "xmlParser.h"

MapManager* MapManager::pUniqueInstance = NULL; // Reference to the unique instance.
SDL_mutex* MapManager::mxInstance = SDL_CreateMutex();	// Reference to instance mutex.

MapManager* MapManager::getInstance(){
	SDL_LockMutex(mxInstance);	// Locks the mutex...
	if (pUniqueInstance == NULL){ // No instance, create one.
		pUniqueInstance = new MapManager;
	}
	SDL_UnlockMutex(mxInstance);	// Locks the mutex...
	return pUniqueInstance;
}

void MapManager::freeInstance(){
	SDL_LockMutex(mxInstance);	// Locks the mutex...
	if (pUniqueInstance != NULL) {
		delete pUniqueInstance;
		pUniqueInstance = NULL;
	}
	SDL_LockMutex(mxInstance);	// Locks the mutex...
}

MapManager::MapManager()
{
    //ctor
}

MapManager::~MapManager()
{
    //dtor
}

bool MapManager::loadXMLMap(const std::string& filename){
	std::string tmp = filename+".xml";
	// Test map loading.
	XMLNode xMainNode=XMLNode::openFileHelper(tmp.c_str(),"map");
	//XMLNode xNode=xMainNode.getChildNode("region").getChildNode("zone",1);
	//std::cout << xNode.getAttribute("name");
	return true;
}

bool MapManager::validateMove(Location& orig,Location& dest){
	Uint32 ox,oy,oz,dx,dy,dz;
	Uint32 deltax, deltay, deltaz;

	orig.getXYZ(ox, oy, oz);
	dest.getXYZ(dx,dy,dz);
	deltax = abs(ox-dx);
	deltay = abs(oy-dy);
	deltaz = abs(oz-dz);
	
// Compares absolute value of the three dimensions. We can also evaluate the distance calculated with
// Pitagora's theoreme (and to require it to lower sqrt(2)), but it could be not good computationally.
/*
#include <math.h>
Uint32 distance = sqrt(pow((ox-dx),2)+pow((oy-dy),2))
deltaz = abs(oz-dz);// This should always be < 1
if (deltaz <= sqrt(2)) //This could be arcoded for performance improvement < 1.5 for example should be safe.
*/

	// We allow only a 1-square movement in every 8 directions and up or down.
	if ( deltax <= 1 && deltay <= 1 && deltaz <=1 )
		return true;
	else
		return false;
}


