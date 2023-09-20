#ifndef ASS2V2_ELECTION_H
#define ASS2V2_ELECTION_H
#include <random>
#include <vector>
#include "newParty.h"
#include "issue.h"
#include "random.h"
#include "entities.h"
#include "events.h"

class ElectionGenerator{

private:

    const static unsigned int partyNumber = 3;
    int totalElectorates;
    RandomEng rndEng;
    std::vector<Event> events;
    std::vector<Issue> issues;
    std::vector<Party> parties;
    std::vector<float> partiesStanceRanges;
    std::vector<Electorate> electorates;
    const std::vector<std::string> area = {"Wollongong","East-Blue","Sydney","New-York","Moruya","Nowra","Bodalla","Bega","Canberra","Figtree"};

public:

    std::vector<Issue> loadIssues();
    std::vector<Issue> getIssues(){return issues;}

    //Generators
    void generateParties(unsigned int n);
    void generateElectorate(unsigned int);
    Leader generateLeader(Party p, std::string name);
    ManagerialTeam generateTeam(Party& p, std::string name);
    Candidate generateCandidate(Party p, std::string name, int count);

    void loadEvents();
    void getEvent(int);
    void debateEvent(int, Event);
    void candidateEvent(int i, Event e);
    void leaderEvent(int i, Event e);
    void runEvent(unsigned int);

    void partyReport();
    void elecReport();
    void outputIssues();

    void generateVotes();
    void outputWinner();


};


#endif //ASS2V2_ELECTION_H
