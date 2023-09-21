#ifndef ASS2V2_NEWPARTY_H
#define ASS2V2_NEWPARTY_H
#include <string>
#include <map>
#include <vector>
#include "issue.h"
#include "random.h"

enum Trait {

    POPULARITY,
    RELIABILITY,
    INFLUENCE,
    INTELLIGENCE,
    COURAGE,
    LOYALTY,
    DEBATE_EXP

};

class Human {

protected:

    std::map<Trait, unsigned int> traits;
    std::string name;
    std::vector<Stance> stanceValues;
    std::string location;
    RandomEng rndEng;
    std::string partyName;
    std::vector<Trait> availableTraits = {RELIABILITY, INFLUENCE, INTELLIGENCE, COURAGE, LOYALTY, DEBATE_EXP};


public:

     void updateTraits(Trait t, unsigned int value) {

         int current = traits[t];

         if(current + value >= 100){
             traits[t] = 100;
         }
         else if(current + value <= 0) {
             traits[t] = 0;
         }
         else if(current == 0 || current == 100){
             return;
         }
         else{
             traits[t] = current + value;
         }

     }

     void setPartyName(std::string p){partyName = p;}
    std::string getPartyName(){return partyName;}
    std::string getName() const{return name;}
    std::string TraitToString(Trait trait) const;
    void printTraits() const;
    std::string getLocation(){return location;}

    void setStance(std::vector<Stance> pStance){stanceValues = pStance;}
    std::vector<Stance> getStance(){return stanceValues;}
    void setStance(std::vector<Issue> i, int min, int max);
    void setArea(std::string s){location = s;}

    unsigned int getTrait(Trait trait) const {
        auto it = traits.find(trait);
        if (it != traits.end()) {
            return it->second;
        }
        return 0; // Default value if the trait is not found
    }


};

class ManagerialTeam : public Human {

public:

    ManagerialTeam(){}
    ManagerialTeam(const std::string &n);

};


class Leader : public Human {

public:

    Leader(){}
    Leader(const std::string&);

};


class Candidate : public Human {

private:
    unsigned int currentVote;
    unsigned int voteCount;
    double range;

public:

    Candidate(){};
    Candidate(const std::string &n);

    void setVotes(unsigned int votes){
        voteCount += votes;
        if(votes == 0){
            currentVote =0;
            return;
        }
        currentVote += votes;
    }


    unsigned int getVote() {return currentVote;}
    unsigned int getVotes(){return voteCount;}
    void addRange(double r){range += r;}
    double getRange(){return range;}

};


class Party{

private:

    ManagerialTeam ManagerTeam;
    Leader leader;
    std::vector<Candidate> candidates;
    std::string name;
    std::vector<Stance> stanceValues;
    std::string description;
    int wins;

public:

    Party() : wins(0){}

    //Setters
    void setPartyName(std::string n);
    void setManagerTeam(ManagerialTeam);
    void setLeader(Leader);
    void addCandidate(Candidate c);
    void setDescription(std::string s){description = s;}
    void addWin(unsigned int w){wins += w;}

    //Getters
    int getWins(){return wins;}
    std::string getPartyName();
    Leader & getLeader();
    ManagerialTeam getTeam();
    std::vector<Candidate> & getCandidates();
    std::vector<Stance> getStances(){return stanceValues;}
    void setStance(std::vector<Issue> i, int min, int max);
    std::string getDiscription(){return description;}

};
#endif //ASS2V2_NEWPARTY_H
