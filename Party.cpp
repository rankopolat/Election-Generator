#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "newParty.h"
#include "issue.h"
#include "random.h"
using namespace std;

string Human::TraitToString (Trait trait) const{

    switch (trait) {
        case POPULARITY:
            return "Popularity";
        case RELIABILITY:
            return "Reliability";
        case INFLUENCE:
            return "Influence";
        case INTELLIGENCE:
            return "Intelligence";
        case COURAGE:
            return "Courage";
        case LOYALTY:
            return "Loyalty";
        case DEBATE_EXP:
            return "Debate Experience";
        default:
            return "UNKNOWN";
    }
}


void Human::setStance(std::vector<Issue> i,int min, int max){

    for(Issue issue: i){

        Stance stance;
        int range = rndEng.randInt(1,30);
        int signif = rndEng.randInt(min,max);
        int approach = rndEng.randInt(min, max);
        stance.setIssue(issue);
        stance.setApproach(approach);
        stance.setSignificant(signif);
        stance.setRange(range);

        stanceValues.push_back(stance);

    }
}

void Human::printTraits() const {

        for (const auto& trait : traits) {
            cout << TraitToString(trait.first) << " " << trait.second << " | " ;
        }
}



ManagerialTeam::ManagerialTeam(const string& n){

        Human::name = n;
        traits[POPULARITY] = rndEng.randInt(0,100);

}


Leader::Leader(const string& n){

    Human::name = n;

    traits[POPULARITY] = rndEng.randInt(0,100);

    for (int i = 0; i < 2; ++i) {

        int randomIndex = rand() % availableTraits.size();
        Trait randomTrait = availableTraits[randomIndex];
        traits[randomTrait] = rndEng.randInt(0,100);
        availableTraits.erase(availableTraits.begin() + randomIndex);

    }
}

Candidate::Candidate(const string& n):voteCount(0),range(0),currentVote(0) {

    Human::name = n;

    traits[POPULARITY] = rndEng.randInt(0,100);;

    for (int i = 0; i < 2; ++i) {

        int randomIndex = rand() % availableTraits.size();
        Trait randomTrait = availableTraits[randomIndex];
        traits[randomTrait] = rndEng.randInt(0,100);
        availableTraits.erase(availableTraits.begin() + randomIndex);

    }
}

void Party::setPartyName(string n) {name = n;}
void Party::setManagerTeam(ManagerialTeam m) {ManagerTeam = m;}
void Party::setLeader(Leader l){
    leader = l;
}
void Party::addCandidate(Candidate c){candidates.push_back(c);}

void Party::setStance(std::vector<Issue> i,int min, int max){

    RandomEng rndEng;

    for(Issue issue: i){

        Stance stance;
        //int range = rndEng.randInt(1,30);
        int signif = rndEng.randInt(min,max);
        int approach = rndEng.randInt(min, max);
        stance.setIssue(issue);
        stance.setApproach(approach);
        stance.setSignificant(signif);
        //stance.setRange(range);

        stanceValues.push_back(stance);

    }
}

string Party::getPartyName(){return name;}
Leader & Party::getLeader(){return leader;}
ManagerialTeam Party::getTeam(){return ManagerTeam;}
std::vector<Candidate>& Party::getCandidates(){return candidates;}