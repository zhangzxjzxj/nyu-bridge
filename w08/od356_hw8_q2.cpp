#include <iostream>
#include <ctime>
#include <vector>
#include <unistd.h>
using namespace std;

// Settings for program.
const bool SHOULD_DISPLAY_STATS = true; // Displays population info below board
const bool AUTOPLAY = true;  // Runs program automatically without pressing enter

// Initial board settings
const int INITIAL_ANTS = 100;
const int INITIAL_DOODLEBUGS = 5;
const int DOODLEBUG_STARVATION_PERIOD = 3;
const int STEP = 10000; // Number of nanoseconds between each step in AUTOPLAY mode.
const int BOARD_SIZE = 20;  // number of rows and columns on board

// Constantized directions, types for more readable code below
const char ENTER = '\n';
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;
const int MAX_DIRECTION = RIGHT;
const int ORGANISM_TYPE = 0;
const int ANT_TYPE = 1;
const int DOODLEBUG_TYPE = 2;

// Forward delcarations
class Board;
class Location;
class Organism;
class OrganismList;

// Utility functions
int getRandomDirection();
int getRandomCell();

// An abstract class for different types of critters.
class Organism {
  public:
    // Constructor
    Organism(char newDisplayChar, int newOrganismType, int newBreedCycleLength) {
      displayChar = newDisplayChar;
      location = nullptr;
      organismType = newOrganismType;
      breedCycleLength = newBreedCycleLength;
      isDead = false;
      index = -1;
    };
    Organism(): displayChar('-'), location(nullptr), organismType(ORGANISM_TYPE), breedCycleLength(1), isDead(false), index(-1) {};
    Organism(const Organism& rhs) {};
    ~Organism() {};
    Organism& operator=(const Organism* rhs) { return *this; }
    // Property accessors
    Location* getLocation() const;
    void setBirthtime(int timestamp);
    void setLocation(Location* newLocation);
    void setId(int newId);
    int getBirthtime() const;
    int getAge(int timestamp) const;
    int getBreedCycleLength() const;
    int getType() const;
    int getId() const;
    void setIndex(int newIndex) { index = newIndex; }
    int getIndex() const { return index; }
    bool getIsDead() const;
    // Sets a death state
    void die();
    // Returns true if the organism should breed at the given timestamp
    bool shouldBreed(int timestamp);

    // Prints text representations of organisms
    ostream& print(ostream& outs);
    string getDisplay();
    friend ostream& operator <<(ostream& outs, const Organism& organism);
    // A function that triggers a movement action of an organism.  Returns true of successful.
    virtual bool move(int timestamp, OrganismList* organisms) { return true; };
    // A function that triggers a breeding action of an organism by returning a valid spawn Location.
    virtual Location* breed(int timestamp, OrganismList* organisms) { return nullptr; };
  private:
    int id; // A globally unique identifier for the organism across all runs of the application.
    int index; // Index in OrganismsList
    char displayChar; // Which character to show on the board
    int birthtime; // A time stamp denoting when the organism was born
    int breedCycleLength; // How long before the organism breeds
    int organismType;  // a type constant to quickly resolve branching behavior in polymorphic functions
    bool isDead;  // records whether organism as died and can be removed.
    Location* location; // a pointer to the Location of the organism
};

// A container for keeping track of all organisms in memory and managing their creation/destruction
class OrganismList {
  public:
    // Constructor
    OrganismList(): ids(1), size(BOARD_SIZE * BOARD_SIZE), deaths(0) {
      for (int i = 0; i < size; i++)
        data[i] = nullptr;
    };
    // Instantiates a new Organism object of a given type, at a given time and in a given location.
    Organism* createOrganism(int organismType, int timestamp, Location* location);
    // Adds the organism to the list.
    void addOrganism(Organism* newOrganismPtr);
    // Removes organism from memory and list.
    void destroyOrganism(Organism* newOrganismPtr);
    // Returns the next unique ID for orgnaism creation
    int getLastId() const { return ids; };
    // Returns the total number of organisms in the population
    int getSize();
    // Returns the total number of organisms of a given type in the population
    int countOfType(int organismType);
    // Triggers a move action on all organisms of a given type
    void moveAll(int timestamp, int orgType);
    // Triggers a breed action on all organisms
    void breedAll(int timestamp);
    // Cleans up dead organisms during the last round.
    void removeAllDead();
    // Prints a row of stats about the population
    void displayStats(int timestamp);
  private:
    int ids; // Holds the current unique ID
    int size; // Keeps track of max allowable size
    int deaths; // Total amounts of organisms destroyed
    Organism* data[BOARD_SIZE * BOARD_SIZE]; // Holds a list of all organisms in memory
};

// An Organism subtype for Ant critters
class Ant :public Organism {
  public:
    // Default constructor
    Ant(): Organism('o', ANT_TYPE, 3) {};
    // overrides default move() function
    bool move(int timestamp, OrganismList* organisms);
    // Overrides breed() function
    Location* breed(int timestamp, OrganismList* organisms);
};

// An Organism subtype for Doodlebug critters
class Doodlebug :public Organism {
  public:
    // Default constructor
    Doodlebug(): Organism('X', DOODLEBUG_TYPE, 8), lastMeal(0) {};
    // overrides default move() function
    bool move(int timestamp, OrganismList* organisms);
    // Casuses death of target organism
    void eat(Organism* foodPtr);
    // Accessor for lastMeal
    int getTimeSinceMeal(int timestamp);
    // Overrides breed() function
    Location* breed(int timestamp, OrganismList* organisms);
  private:
    int lastMeal; // Keeps track of when the last meal took place.
};

// An abstraction with pointers to the board and organism that keeps track
// of an organism's relationship with the board and eliminates need for
// organisms to maintain references/awareness of the Board
class Location {
  public:
    // Constructors
    Location(): x(0), y(0), board(nullptr), organism(nullptr) {};
    Location(int newX, int newY, Board* newBoard, Organism* newOrganismPtr);
    // Returns a pointer to an adjacent location in the given direction
    Location* nextMove(int direction);
    // Accessors for coordinates, organism pointer
    int getX() const { return x; };
    int getY() const { return y; };
    void setOrganism(Organism* newOrganism);
    Organism* getOrganism();
    // Returns pointer to a random, nearby empty location
    Location* getNearbyEmptyLocation();
    // Returns pointer to a nearby ant (or nullptr if none is available)
    Organism* getNearbyAnt();
    // Returns true of the given location is unoccupied by an organism
    bool isEmpty();
    // Override operators for printing, comparison, etc.
    ostream& print(ostream& outs);
    friend ostream& operator <<(ostream& outs, Location* location);
    bool operator==(const Location& rhs);
    Location& operator=(const Location& rhs) { return *this; }
  private:
    Organism* organism;
    Board* board;
    // [x,y] relative to a grid on Board.data
    int x;
    int y;
};

// A container to keep track of all locations and initialize state
class Board {
  public:
    // Constructor
    Board();
    // Destructor
    ~Board();
    // Initializes state of all organisms at a given time
    void initialize(OrganismList* organisms, int timestamp);
    Location* getLocation(int x, int y);
    Location* findRandomEmptyLocation(int numChecked);
    ostream& print(ostream& outs);
    friend ostream& operator <<(ostream& outs, Board& board);
  private:
    Location* state[BOARD_SIZE][BOARD_SIZE]; // A 2D array to store Location pointers
};

// Main function for the program
int main() {
  char userInput = ENTER;
  int timestamp = 1;
  OrganismList organisms;
  // Init random seed
  srand(time(nullptr));

  // Creates a new board object and initializes
  Board* board = new Board();
  board->initialize(&organisms, timestamp);

  cout << *board << endl;
  organisms.displayStats(timestamp);

  // Main loop
  while ((AUTOPLAY || userInput == ENTER) && (organisms.getSize() < (BOARD_SIZE * BOARD_SIZE))) {
    // Prompt user
    cout << "press enter key to continue..." << endl;

    // Autoplay or get user input
    if (AUTOPLAY)
      usleep(STEP);
    else
      userInput = cin.get();

    // Update organisms
    organisms.moveAll(timestamp, DOODLEBUG_TYPE);
    organisms.removeAllDead();
    organisms.moveAll(timestamp, ANT_TYPE);
    organisms.breedAll(timestamp);

    // Render board
    cout << *board << endl;

    // Show stats
    organisms.displayStats(timestamp);

    // Increment timestamp
    timestamp++;
  }

  // Cleanup
  delete board;

  // Exit
  return 0;
}

// ------------------------------------
//        Class Implementations
// ------------------------------------

/*
 *
 * Organism Implementation
 *
 */

string Organism::getDisplay() {
  return string(1, displayChar);
}

void Organism::die() {
  isDead = true;
  location = nullptr;
}

bool Organism::getIsDead() const {
  return isDead;
}

int Organism::getBreedCycleLength() const {
  return breedCycleLength;
}

void Organism::setBirthtime(int timestamp) {
  birthtime = timestamp;
}

int Organism::getBirthtime() const {
  return birthtime;
}

int Organism::getType() const {
  return organismType;
}

void Organism::setId(int newId) {
  id = newId;
}

int Organism::getId() const {
  return id;
};

Location* Organism::getLocation() const {
  return location;
}

void Organism::setLocation(Location* newLocation) {
  location = newLocation;
}

int Organism::getAge(int timestamp) const {
  return timestamp - getBirthtime();
}

bool Organism::shouldBreed(int timestamp) {
  int age = getAge(timestamp);
  return (age > 0) && ((age % getBreedCycleLength()) == 0);
}

ostream& Organism::print(ostream& outs) {
  outs << displayChar;
  return outs;
}

ostream& operator <<(ostream& outs, Organism* organism) {
  organism->print(outs);
  return outs;
}

/**
 *
 * Ant implementation
 *
 */

bool Ant::move(int timestamp, OrganismList* organisms) {
  int direction = getRandomDirection();
  Location* currentLocation = getLocation();
  Location* newLocation;
  newLocation = currentLocation->nextMove(direction);

  // Not a valid move.
  if (newLocation == nullptr) return false;

  if (newLocation->isEmpty()) {
    currentLocation->setOrganism(nullptr);
    newLocation->setOrganism(this);
    setLocation(newLocation);
    return true;
  } else {
    // An illegal move as attempted to an occupied spot.
    return false;
  }
};

Location* Ant::breed(int timestamp, OrganismList* organisms) {
  Location* currentLocation = getLocation();
  Location* newLocation;
  Organism* newAnt;
  // Check nearby locations
  Location* nearbyLocation = currentLocation->getNearbyEmptyLocation();
  if (nearbyLocation != nullptr) {
    return nearbyLocation;
  } else {
    return nullptr;
  }
}

/*
 *
 * Doodlebug implementation
 *
 */

bool Doodlebug::move(int timestamp, OrganismList* organisms) {
  int direction = getRandomDirection();
  int timeSinceMeal;
  Location* currentLocation = getLocation();
  Location* newLocation;
  Location* nearbyAntLocation;
  Organism* orgPtr;
  // Check for nearby ant here.
  orgPtr = currentLocation->getNearbyAnt();
  // Found a nearby ant
  if (orgPtr != nullptr) {
    nearbyAntLocation = orgPtr->getLocation();
    eat(orgPtr); // Registers as dead.
    setLocation(nearbyAntLocation);
    nearbyAntLocation->setOrganism(this);
    currentLocation->setOrganism(nullptr);
    lastMeal = timestamp;
    return true;
  } else { // Move to a random spot if there is no ant to eat
    // Starve instead of moving
    timeSinceMeal = getTimeSinceMeal(timestamp);
    if (timeSinceMeal > DOODLEBUG_STARVATION_PERIOD) {
      die();
      currentLocation->setOrganism(nullptr);
      setLocation(nullptr);
      return false;
    }

    // Find new location to move to
    newLocation = currentLocation->nextMove(direction);

    // Not a valid move.  Try again next turn.
    if (newLocation == nullptr) return false;

    // If empty, initiate move.
    if (newLocation->isEmpty()) {
      currentLocation->setOrganism(nullptr);
      newLocation->setOrganism(this);
      setLocation(newLocation);
      return true;
    // Otherwise, something is occupying the location. (Another Doodlebug perhaps...?)
    } else {
      return false;
    }
  }
};

void Doodlebug::eat(Organism* foodPtr) {
  foodPtr->die();
}

int Doodlebug::getTimeSinceMeal(int timestamp) {
  return timestamp - lastMeal;
}

Location* Doodlebug::breed(int timestamp, OrganismList* organisms) {
  Location* currentLocation = getLocation();
  Location* newLocation;
  Organism* newAnt;
  // Check nearby locations
  Location* nearbyLocation = currentLocation->getNearbyEmptyLocation();
  if (nearbyLocation != nullptr) {
    return nearbyLocation;
  } else {
    return nullptr;
  }
}

/**
 *
 * Board implementation
 *
 */

// Constructor
Board::Board() {
  Location* currentLocation;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      state[i][j] = new Location(i,j,this,nullptr);
    }
  }
};

// Destructor
Board::~Board() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      delete state[i][j];
    }
  }
}

void Board::initialize(OrganismList* organisms, int timestamp) {
  int numAnts = INITIAL_ANTS;
  int numDoodlebugs = INITIAL_DOODLEBUGS;
  Organism* currentOrganismPtr = nullptr;
  Location* location;

  while (numAnts > 0) {
    location = findRandomEmptyLocation(0);
    currentOrganismPtr = organisms->createOrganism(ANT_TYPE, timestamp, location);
    numAnts--;
  }

  while (numDoodlebugs > 0) {
    location = findRandomEmptyLocation(0);
    currentOrganismPtr = organisms->createOrganism(DOODLEBUG_TYPE, timestamp, location);
    numDoodlebugs--;
  }

  // Prints heading with initialization info
  cout << "Board(";
  cout << "t: " << timestamp << ", ";
  cout << "board: " << BOARD_SIZE << "x" << BOARD_SIZE << ", ";
  cout << "o: " << INITIAL_ANTS << ", ";
  cout << "x: " << INITIAL_DOODLEBUGS << ")" << endl;

  return;
}

Location* Board::getLocation(int x, int y) {
  return state[x][y];
};

Location* Board::findRandomEmptyLocation(int numChecked) {
  // Base case: no empty locations
  if (numChecked >= (BOARD_SIZE * BOARD_SIZE))
    return nullptr;
  else {
    Location* location = getLocation(getRandomCell(), getRandomCell());
    if (location->isEmpty()) {
      return location;
    } else {
      return findRandomEmptyLocation(numChecked + 1);
    }
  }
}

ostream& Board::print(ostream& outs) {
  string row;
  string displayStr;
  Location* currentLocationPtr;
  Organism* currentOrganismPtr;
  for (int i = 0; i < BOARD_SIZE; i++) {
    row = "";
    for (int j = 0; j < BOARD_SIZE; j++) {
      currentLocationPtr = state[i][j];
      currentOrganismPtr = currentLocationPtr->getOrganism();
      if (currentOrganismPtr != nullptr)
        displayStr = currentOrganismPtr->getDisplay();
      else
        displayStr = "-";
      row = row + displayStr + " ";
    }
    outs << row << endl;
  }
  return outs;
}

ostream& operator <<(ostream& outs, Board& board) {
  board.print(outs);
  return outs;
}

// Utility functions
int getRandomCell () {
  return rand() % BOARD_SIZE;
}

int getRandomDirection() {
  return rand() % 4 + 1;
}

/*
 *
 *  Location Implementation
 *
 */

Location::Location(int newX, int newY, Board* newBoard, Organism* newOrganismPtr) {
  if (newX > BOARD_SIZE || newY > BOARD_SIZE) {
    x = 0;
    y = 0;
  } else {
    x = newX;
    y = newY;
  }
  organism = newOrganismPtr;
  board = newBoard;
};

void Location::setOrganism(Organism* newOrganism) {
  organism = newOrganism;
}

Organism* Location::getOrganism() {
  Organism* currentOrganism = nullptr;
  if (organism != nullptr)
    currentOrganism = organism;
  return currentOrganism;
}

bool Location::isEmpty() {
  if (getOrganism() == nullptr)
    return true;
  else
    return false;
}

Location* Location::getNearbyEmptyLocation() {
  int randomIdx; // stores a random index.
  vector<Location*> locations;
  Location* nextLocation = nullptr;
  for (int i = 1; i < (MAX_DIRECTION + 1); i++) {
    nextLocation = nextMove(i);
    if (nextLocation != nullptr) {
      if (nextLocation->isEmpty())
        locations.push_back(nextLocation);
    }
  }

  if (locations.size() == 0) { // no empty locations
    nextLocation = nullptr;
  } else if (locations.size() == 1) { // 1 empty location
    nextLocation = locations[0];
  } else { // > 1 empty locations
    randomIdx = rand() % locations.size();
    nextLocation = locations[randomIdx];
  }

  // Returns a location pointer or nullptr
  return nextLocation;
}

Organism* Location::getNearbyAnt() {
  Organism* orgPtr = nullptr;
  Location* nextLocation = nullptr;
  for (int i = 1; i < (MAX_DIRECTION + 1); i++) {
    nextLocation = nextMove(i);
    if (nextLocation != nullptr) {
      if (!(nextLocation->isEmpty())) {
        orgPtr = nextLocation->getOrganism();
        if (orgPtr != nullptr) {
          if (orgPtr->getType() == ANT_TYPE) {
            return orgPtr;
          } else {
            orgPtr = nullptr;
          }
        }
      }
    }
  }

  // Returns nullptr
  return orgPtr;
}

bool Location::operator==(const Location& rhs) {
  // Checks if locations are equal in value
  return (getX() == rhs.getX()) && (getY() == rhs.getY());
}

ostream& Location::print(ostream& outs) {
  return outs << "(" << getX() << "," << getY() << ", organism: (" << getOrganism() << "))";
};

ostream& operator <<(ostream& outs, Location* location) {
  location->print(outs);
  return outs;
}

Location* Location::nextMove(int direction) {
  Location* newLocationPtr = nullptr;
  Location* allNearby;
  int arr[2];
  switch (direction) {
    case UP:
      arr[0] = getX();
      arr[1] = getY() - 1;
      break;
    case DOWN:
      arr[0] = getX();
      arr[1] = getY() + 1;
      break;
    case LEFT:
      arr[0] = getX() - 1;
      arr[1] = getY();
      break;
    case RIGHT:
      arr[0] = getX() + 1;
      arr[1] = getY();
      break;
    default:
      return nullptr;
  }

  // Check if the new location is valid
  if ((arr[0] >= 0) && (arr[0] < BOARD_SIZE) && (arr[1] >= 0) && (arr[1] < BOARD_SIZE)) {
    newLocationPtr = board->getLocation(arr[0], arr[1]);
  }
  // When its not, it returns nullptr
  return newLocationPtr;
};

/**
 *
 * OrganismList
 *
 */

void OrganismList::displayStats(int timestamp) {
  int numAnts = countOfType(ANT_TYPE);
  if (numAnts == 0) {
    cout << "Error: no ants!" << endl;
    exit(1);
  }
  if (SHOULD_DISPLAY_STATS)
    cout << "time: " << timestamp << ", population(o: " << countOfType(ANT_TYPE) << ", x: " << countOfType(DOODLEBUG_TYPE) << "), births: " << getLastId() << ", deaths:" << deaths << endl;
}

int OrganismList::countOfType(int organismType) {
  int counter = 0;
  for (int i = 0; i < size; i++) {
    if (data[i] != nullptr) {
      if (data[i]->getType() == organismType)
        counter++;
    }
  }
  return counter;
}

int OrganismList::getSize() {
  int counter = 0;
  for (int i = 0; i < size; i++) {
    if (data[i] != nullptr)
      counter++;
  }
  return counter;
}

void OrganismList::addOrganism(Organism* newOrganismPtr) {
  for (int i = 0; i < size; i++) {
    if (data[i] == nullptr) {
      data[i] = newOrganismPtr;
      newOrganismPtr->setIndex(i); // Sets the index of the organism
      return;
    }
  }

  // If this fires, there's most likely a memory leak.
  cout << "Error: OrganismList full.  Unable to add more organisms." << endl;
  exit(1);
}

void OrganismList::destroyOrganism(Organism* newOrganismPtr) {
  if (newOrganismPtr == nullptr) return;
  int idx = newOrganismPtr->getIndex();
  int id = newOrganismPtr->getId();
  Location* currentLocation;

  // Exit when index is invalid, since this means there's likely a memory leak.
  if (idx == -1) {
    cout << "Error: Organism(id: " << id << ") has no index and could not remove.  Possible memory leak." << endl;
    exit(1);
  }


  // Set position to nullptr
  if (data[idx] != nullptr) {
    data[idx] = nullptr;
  }

  // Clear pointer on location to the organism
  currentLocation = newOrganismPtr->getLocation();
  if (currentLocation != nullptr)
    currentLocation->setOrganism(nullptr);

  // Deallocate memory used by organism
  delete newOrganismPtr;
  newOrganismPtr = nullptr;
}

void OrganismList::moveAll(int timestamp, int orgType) {
  Organism* currOrgPtr = nullptr;
  bool isNotNull, isOfType, isNotDead;
  for (int i = 0; i < size; i++) {
    currOrgPtr = data[i];
    isNotNull = (currOrgPtr != nullptr);
    if (isNotNull) {
      isOfType = (orgType == currOrgPtr->getType());
      isNotDead = (!currOrgPtr->getIsDead());
      if (isOfType && isNotDead) {
        currOrgPtr->move(timestamp, this);
      }
    }
  }
}

void OrganismList::breedAll(int timestamp) {
  Organism* currOrgPtr = nullptr;
  vector<Location*> spawnSites;
  vector<int> spawnSiteTypes;
  Location* spawnSite = nullptr;
  int spawnType;
  int birthtime;
  int breedCycleLength;

  // First find all the places where breeding should occur.
  for (int i = 0; i < size; i++) {
    currOrgPtr = data[i];
    if (currOrgPtr != nullptr) {
      if (currOrgPtr->shouldBreed(timestamp)) {
        spawnSite = currOrgPtr->breed(timestamp, this);
        // Found a spawn site!
        if (spawnSite != nullptr) {
          spawnType = currOrgPtr->getType();
          spawnSites.push_back(spawnSite);
          spawnSiteTypes.push_back(spawnType);
        }
      }
    }
  }

  int counter = 0;
  // Second, add all the organisms one by one to their new locations to prevent organism list
  // size changes during the looping
  if (spawnSites.size() > 0) {
    for (int i = 0; i < spawnSites.size(); i++){
      // Check if site is still empty. (Sometimes two spawn will claim same site)
      if (spawnSites[i]->isEmpty()) {
        createOrganism(spawnSiteTypes[i], timestamp, spawnSites[i]);
        counter++;
      }
    }
  }
}

void OrganismList::removeAllDead() {
  Organism* currOrgPtr = nullptr;
  bool isDead;
  int counter = 0;
  for (int i = 0; i < size; i++) {
    currOrgPtr = data[i];
    if ((currOrgPtr != nullptr) && currOrgPtr->getIsDead()) {
      destroyOrganism(currOrgPtr);
      counter++;
    }
  }
  deaths += counter;
}

Organism* OrganismList::createOrganism(int organismType, int timestamp, Location* location) {
  Organism* orgPtr = nullptr;
  if (organismType == ANT_TYPE) {
    orgPtr = new Ant;
  } else if (organismType == DOODLEBUG_TYPE){
    orgPtr = new Doodlebug;
  } else {
    cout << "Unable to create organism of type: " << organismType << endl;
    exit(1);
  }

  // Assign id
  orgPtr->setId(ids);
  orgPtr->setBirthtime(timestamp);
  addOrganism(orgPtr);
  ids++;
  orgPtr->setLocation(location);
  location->setOrganism(orgPtr);
  return orgPtr;
}
