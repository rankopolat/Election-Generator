#include "entities.h"
#include "random.h"

std::vector<Stance> Entity::getStance(){
    return stanceValues;
}

Group::Group(unsigned int id,unsigned int pop)
        :population(pop), groupNumber(id){};

unsigned int Group::getPopulation(){return population;}

unsigned int Group::getID(){return groupNumber;}


void Group::setGroupStance(std::vector<Issue> issues,int min,int max){

    int significant;
    int approach;

    RandomEng r;

    for(Issue& i: issues){

        Stance s;
        significant = r.randInt(min,max);
        approach = r.randInt(min,max);
        s.setApproach(approach);
        s.setSignificant(significant);
        s.setIssue(i);

        Entity::stanceValues.push_back(s);

    }
}

void Electorate::setData(std::string a){
    area = a;
}

void Electorate::setCandidates(std::vector<Candidate> c){
    candidates = c;
}
unsigned int Electorate::getPop(){
    return population;
}

std::string Electorate::getArea(){
    return area;
}

std::vector<Group> Electorate::getGroups(){
    return groups;
}

std::vector<Candidate> & Electorate::getCandidates(){
    return candidates;
}

unsigned int Electorate::getTotalGroups(){
    return totalGroups;
}

void Electorate::generateGroups(unsigned int groupCount, std::vector<Issue> issues){

    RandomEng rndEng;
    int electoratePopulation = 0;

    for(unsigned int i = 0; i < groupCount; i++){

        Group group;
        int groupPopulation = rndEng.randInt(700,1200);
        electoratePopulation += groupPopulation;
        group = Group(i+1,groupPopulation);
        int min = rndEng.randInt(30,50);
        int max = rndEng.randInt(70,90);
        group.setGroupStance(issues,min,max);

        groups.push_back(group);

    }

    totalGroups = groupCount;
    population = electoratePopulation;

}
