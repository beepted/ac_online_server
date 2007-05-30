#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <iostream>

#include "SDL.h"
#include "Location.h"



//Objects types
#define GO_INVALID  (0)     /**< Invalid game object. */
#define GO_PLAYER   (1)     /**< A player. */

/**
 * This abstract interface represents a generic game object. It is
 * used as a base class for all the items, obects and beings of the game.
 *
 * Setters are thread safe (at least they _should be_!)
 */
class IGameObject
{
public:
    /**
     * Creates a new objects given its serial number (unique) and its type.
     */
    IGameObject(Uint32 serial, Uint16 type);

    /**
     * Virtual destructor.
     */
    virtual ~IGameObject();

    /**
     * Returns object's serial.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Object's serial unique number.
     */
    Uint32 getSerial() {return mSerial;}

    /**
     * Returns object type.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Object type.
     */
    Uint16 getType() {return mType;}

    /**
     * Returns object's owner.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Object's owner serial.
     */
    Uint32 getOwner() {return mOwner;}

    /**
     * Sets current object's owner. Thread safe.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newOwner The serial of the new owner.
     */
    void setOwner(Uint32 newOwner);

    /**
     * Returns object's name. Derived classes may implement more
     * specializated names categories.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Object's standard name.
     */
    std::string getName() {return mName;}

    /**
     * Sets a new name for the object. Thread safe.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newName The string containing the new object's name.
     */
    void setName(std::string newName);

    /**
     * Returns a reference to the current position of the object in the
     * form of a Location instance.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Object position.
     * @see Location
     * @todo See if we can make this const for safety.
     * @todo See if mutexes are necessary.
     */
    Location& getPosition() {   SDL_LockMutex(mxPos);   //Locks the mutex...
                                return mPos;
                                SDL_UnlockMutex(mxPos);}//...unlocks it

    /**
     * Sets the current position of the object with a Location object reference. Thread safe.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newPos Object's new position.
     */
    void setPosition(const Location& newPos) {  SDL_LockMutex(mxPos);   //Locks the mutex...
                                                mPos = newPos;
                                                SDL_UnlockMutex(mxPos);}//...unlocks it

    /**
     * Sets the current position of the object with a Location object pointer. Thread safe.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newPos Object's new position.
     */
    void setPosition(Location * newPos) {   SDL_LockMutex(mxPos);   //Locks the mutex...
                                            mPos = *newPos;
                                            SDL_UnlockMutex(mxPos);}//...unlocks it

    /**
     * Updates the object properties. Each derivate class must
     * implement it in order to be usable.
     */
    virtual void update() = 0;

protected:

    Uint32 mSerial;     /**< Unique object's serial. */
    Uint16 mType;       /**< Object type. */
    Uint32 mOwner;      /**< If != 0 is the owner's serial. */
    std::string mName;  /**< Standard object's name. */
    Location mPos;      /**< Object's location (position). */
    SDL_mutex* mxPos;   /**< Mutex for thread safetyness when setting the Position. */
    SDL_mutex* mxOwner; /**< Mutex for thread safetynell when setting the Owner. */
    SDL_mutex* mxName;  /**< Mutex for threas safetyness when setting the name. */

};



#endif // IGAMEOBJECT_H
