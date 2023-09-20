#ifndef ASS2V2_ENTITIES_H
#define ASS2V2_ENTITIES_H
#include "issue.h"
#include "newParty.h"
#include <vector>

class Entity{

protected:
    std::string name;
    std::vector<Stance> stanceValues;

public:
    std::vector<Stance> getStance();

};

class Group : public Entity{

private:
    unsigned int population;
    unsigned int groupNumber;

public:

    Group(){};
    Group(unsigned int, unsigned int);

    void setGroupStance(std::vector<Issue>, int, int);
    unsigned int getPopulation();
    unsigned int getID();

};

class Electorate : public Group{

private:
    std::string area;
    std::vector<Group> groups;
    unsigned int population;
    unsigned int totalGroups;
    std::vector<Candidate> candidates;

public:
    void setData(std::string);
    void generateGroups(unsigned int, std::vector<Issue>);

    unsigned int getPop();
    std::string getArea();
    std::vector<Group> getGroups();
    std::vector<Candidate> &getCandidates();
    unsigned int getTotalGroups();
    void setCandidates(std::vector<Candidate>);

};

#endif //ASS2V2_ENTITIES_H
