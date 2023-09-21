#include <fstream>
#include <vector>
#include <random>
#include <iomanip>
#include "issue.h"
#include "newParty.h"
#include "election.h"
#include "random.h"

using namespace std;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine randEng(seed);

int RandomEng::randInt(int min, int max){

    std::uniform_int_distribution<> dist(min, max);
    return dist(randEng);

}

Candidate ElectionGenerator::generateCandidate(Party p, std::string name, unsigned int count){

        std::string _area = area[count];
        vector<Stance> partyStances = p.getStances();
        Candidate candidate(name);
        candidate.setStance(partyStances);
        candidate.setPartyName(p.getPartyName());
        candidate.setArea(_area);

        return candidate;

}

Leader ElectionGenerator::generateLeader(Party p, std::string name) {

        vector<Stance> partyStances = p.getStances();
        Leader leader(name);
        leader.setArea(area[0]);
        leader.setStance(partyStances);
        leader.setPartyName(p.getPartyName());

        return leader;

}


ManagerialTeam ElectionGenerator::generateTeam(Party& p, string name) {

        vector<Stance> partyStances = p.getStances();
        ManagerialTeam mt(name);
        mt.setPartyName(p.getPartyName());
        mt.setStance(partyStances);

        return mt;

}


std::vector<Issue> ElectionGenerator::loadIssues() {

    Issue _issues[5];

    _issues[0] = Issue("Lost City","Citizens report that their GPS navigation app directs them to drive in circles within a city block, causing frustration and traffic jams.",NAVIGATION);
    _issues[1] = Issue("Roaming Roomba","A citizen's Roomba vacuum cleaner becomes self-aware and starts roaming the house like a mischievous pet, creating chaos.",ROAMBA);
    _issues[2] = Issue("Emoji Overload","Citizens report that their text messages are filled with random emojis inserted by their phones, leading to comically confusing conversations.",EMOJI);
    _issues[3] = Issue("Smart Streetlights","Smart streetlights start turning on and off randomly, confusing both citizens and nocturnal animals.",STREETLIGHT);
    _issues[4] = Issue("Toilet Paper","Citizens' smart homes trigger an alarm whenever they run low on toilet paper, leading to awkward notifications during important meetings.",TOILET);

    for(Issue& i: _issues){

        issues.push_back(i);
    }

    return issues;

}


void ElectionGenerator::generateParties(unsigned int n){

    ifstream humans;
    humans.open("Humans.txt");

    string name;

    while(getline(humans,name)){

        if(name.substr(0,6) == "Party:"){

            Party party;
            party.setPartyName(name.substr(7));
            party.setStance(issues,30,80);
            getline(humans,name);
            party.setDescription(name);
            getline(humans,name);

            if(name.substr(0,13) == "Manager Team:"){

                party.setManagerTeam(generateTeam(party,name.substr(14)));
                getline(humans,name);

            }

            if(name.substr(0,7) == "Leader:"){

                party.setLeader(generateLeader(party,name.substr(8)));
                getline(humans,name);

            }

            unsigned int count = 0;
            while(name.substr(0, 10) == "Candidate:") {

                if (count < n) {

                    party.addCandidate(generateCandidate(party,name.substr(11),count));
                    getline(humans,name);
                    count ++;

                }else
                    break;
            }

            parties.push_back(party);

        }
    }
}

void ElectionGenerator::generateElectorate(unsigned int electorateNumber){


    for(unsigned int i = 0; i < electorateNumber; i++){

        Electorate electorate;
        std::string _area = area[i];
        int totalGroups = rndEng.randInt(2,5); // Minimum of 2 groups maximum of 5
        electorate.generateGroups(totalGroups,issues);
        electorate.setData(_area);
        std::vector<Candidate> eCandidates;

        for(Party& p : parties) {
            for (Candidate &c: p.getCandidates()) {
                if (c.getLocation() == area[i]) {
                    eCandidates.push_back(c);
                }
            }
        }

        electorate.setCandidates(eCandidates);

        electorates.push_back(electorate);
    }

    totalElectorates = electorateNumber;

}


void ElectionGenerator::loadEvents() {

    //Debate Events
    Event debate(" are having a debate", DEBATE, POPULARITY,1);

    events.push_back(debate);

    Event candidate1(" was just seen naked on the street", CANDIDATE, POPULARITY,1);
    Event candidate2(" was just seen helping a old man cross the road", CANDIDATE, POPULARITY,2);

    events.push_back(candidate1);
    events.push_back(candidate2);

    Event leader1(" was caught having an affair with a Octopus", LEADER, POPULARITY,1);
    Event leader2(" farted out in public but looked hot doing it.", LEADER, POPULARITY,2);

    events.push_back(leader1);
    events.push_back(leader2);

}

void ElectionGenerator::debateEvent(int i, Event event) {

    std::string c = event.getContent();

    Candidate highestDebate;
    event.setContent(electorates[i].getArea() + " Candidates" + c);
    cout << event.getContent() << endl;

    unsigned int debateValue = 0;

    for(Candidate& cand: electorates[i].getCandidates()){

        unsigned int debate = cand.getTrait(DEBATE_EXP);

        if(debate > debateValue){

            debateValue = debate;
            highestDebate = cand;
        }

        cout << cand.getName() + " - Debate Experience : " << cand.getTrait(DEBATE_EXP);
        cout << endl;

    }

    if(highestDebate.getName().empty()){
        cout << "The Debate was a draw" << endl << endl;
    }
    else {

        int popIncrease = rndEng.randInt(5,15);
        cout << highestDebate.getName() << " won the debate + "<< popIncrease << " " << event.printImpact() << endl << endl;

        for (Party &p: parties) {

            for (Candidate &cD: p.getCandidates()) {
                if (cD.getName() == highestDebate.getName()) {
                    cD.updateTraits(event.getImpact(), popIncrease);
                }
            }
        }

    }
}


void ElectionGenerator::candidateEvent(int i, Event e){

    int cand = rndEng.randInt(0,2);
    Candidate& c = electorates[i].getCandidates()[cand];

    std::string content = e.getContent();
    e.setContent(c.getName() + content);
    cout << e.getContent() << endl;
    int value = rndEng.randInt(5, 15);

    if(e.getID() == 1){

        cout << c.getName() << " was accused of being a sex offender ";
        value *= -1;
        cout << value << " " << e.printImpact()<< endl << endl;

    }
    else if(e.getID() == 2){

        cout << c.getName() << " was acknowledged as a kind candidate + ";
        value = value;
        cout << value << " " << e.printImpact() << endl << endl;

    }

    for(Party& p: parties){
        for(Candidate& can: p.getCandidates()){
            if(can.getName() == c.getName()){
                can.updateTraits(e.getImpact(), value);
                c.updateTraits(e.getImpact(),value);
            }
        }
    }
}

void ElectionGenerator::leaderEvent(int i, Event e){

    int rParty = rndEng.randInt(1,2);
    Leader& leader = parties[rParty].getLeader();

    std::string content = e.getContent();
    e.setContent("Leader of party " + parties[rParty].getPartyName() + " "  + leader.getName() + content);
    cout << e.getContent() << endl;
    int value = rndEng.randInt(5, 15);

    if(e.getID() == 1){

        value *= -1;
        cout << leader.getName() << " was labeled a terrible human and was a threat to all citizens "<< endl;
        cout << leader.getName() << " popularity took a hit " << value << " " << e.printImpact() << endl << endl;

    }
    else if(e.getID() == 2){

        cout << leader.getName() << " was now considered a legend that people should aspire to become"<< endl;
        cout << leader.getName() << " popularity rose in accordance +" << value << " " << e.printImpact() << endl << endl;

    }

    leader.updateTraits(e.getImpact(),value);

}

void ElectionGenerator::getEvent(int i) {

    int eventRnd = rndEng.randInt(0,4);
    Event event = events[eventRnd];

    std::string c = event.getContent();

    switch(event.getType()){

        case DEBATE:

            debateEvent(i, event);
            break;

        case LEADER:

            leaderEvent(i,event);
            break;

        case CANDIDATE:

            candidateEvent(i,event);
            break;

        case ISSUE:
            cout << "ISSUE EVENT STILL IN PROGRESS" << endl << endl;
            break;

    }

}

void ElectionGenerator::outputIssues(){

    std::cout << std::string(150,'~') << std::endl;
    std::cout << std::right << std::setw(80) << " -=+ | ISSUES | +=-" << std::endl;
    std::cout << "There are 5 main issues to Cybetron: \n" << std::endl;

    for(Issue& _issue: issues){

        cout << "Issue " << _issue.getType() + 1 << ": " << _issue.getCode() << endl;
        cout << _issue.getStatement() << "\n\n";

    }
}

void ElectionGenerator::elecReport() {

    cout << endl << right << setw(82)<<" ---=+ELECTORATES+=---" << endl;
    cout << "Total numbmer of Electorates: " << totalElectorates << endl << endl;

    for(unsigned int i = 0; i < totalElectorates; i++){

        cout <<"Area of Location: " << electorates[i].getArea() << "  |  Total Population (";
        cout << electorates[i].getPop() <<  "):" << endl;
        cout << string(150,'~') << endl;
        cout <<left << setw(35) << "STANCES(Sig/Appr)";

        for(Issue i: issues) {

            std::cout << std::left << std::setfill(' ') << std::setw(25) << i.getCode();
        }

        cout << endl << string(150,'~') << endl;

        for(Group g: electorates[i].getGroups()){

            cout<< left << setw(35) << " Group " + to_string(g.getID()) + ":  Population (" + to_string(g.getPopulation())  + ")";

            for(Stance s: g.getStance()) {

                std::cout << std::left << std::setfill(' ') << std::setw(25) << std::to_string(s.getSignificant())+"/"+ std::to_string(s.getApproach());
            }

            cout << endl;

        }

        cout << endl << "Candidates: " << endl;
        cout << string(150,'~') << endl;
        for(Candidate& c: electorates[i].getCandidates()){

            cout << c.getName() << " | Party: (" << c.getPartyName() << ") | ";
            cout << "Stances (Sig/Appr) | ";
            for(auto& s: c.getStance()){
                cout << s.getSignificant() << "/" << s.getApproach() << "\t";
            }
            cout << endl;

        }

        cout << string(150,'=') << endl << endl;

    }

}

void ElectionGenerator::partyReport() {

    // Header row
    cout << string(150, '~') << endl;
    cout << string(65, ' ') << " -=+ PARTIES +==   \n";
    cout << string(150, '~') << endl << endl;

    cout<< "There are a total of 3 parties:" << endl;

    for (Party& p : parties) {

        std::cout << "\nParty : " << p.getPartyName() << std::endl;
        std::cout  << "Description: " << p.getDiscription() << std::endl ;
        std::cout << "Managerial Team: " << p.getTeam().getName() << std::endl << std::endl;
        std::cout << std::string(150,'~') << std::endl;

        std::cout << std::left << std::setw(35) << "Name";
        std::cout << std::left << std::setw(25) << "Role";
        std::cout << std::left << std::setw(25) << "Location";
        std::cout << std::left << std::setw(25) << "Traits" << std::endl;
        std::cout << std::string(150,'~') << std::endl;

        std::cout << std::setw(35) << p.getLeader().getName();
        std::cout << std::left << std::setw(25) << "Leader";
        std::cout << std::left << std::setw(25) << p.getLeader().getLocation();
        p.getLeader().printTraits();
        std::cout << std::endl;

        std::cout << std::left << std::setw(35) << p.getTeam().getName();
        std::cout << std::left << std::setw(25) << "Managerial Team";
        std::cout << std::left << std::setw(25) << "Everywhere";
        p.getTeam().printTraits();
        cout << endl;

        for(Candidate c : p.getCandidates()){

            cout << std::left << std::setw(35) << c.getName();
            std::cout << std::left << std::setw(25) << "Candidate";
            std::cout << std::left << std::setw(25) << c.getLocation();
            c.printTraits();
            cout << endl;

        }

        std::cout << std::endl;
        std::cout << string(150,'~') << endl;
        std::cout << std::left << std::setw(35) << "STANCES(Sig/Appr)";

        for(Issue i: issues) {

            std::cout << std::left << std::setfill(' ') << std::setw(25) << i.getCode();
        }

        cout << endl << string(150,'~') << endl;
        vector<Stance> stances = p.getStances();
        cout << left << setw(30) << "Leader & Candidates" << left << setw(5)  << "|" ;

        // Variables for parties
        for (auto& l : stances) {
            cout  << left << std::setfill(' ') << setw(25) << to_string(l.getApproach()) + "/" + to_string(l.getSignificant());
        }

        cout << endl;
        cout << string(150, '~') << endl;
        cout << string(150, '=') << endl;
    }
}


void ElectionGenerator::runEvent(unsigned int days) {

    while(days != 0) {

        cout << days << " Days out from Voting " << endl << endl;

        for (unsigned int i = 0; i < totalElectorates; i++) {

            int chance = rndEng.randInt(1, 100);

            if (chance < 50) {
                cout << "No Event For " << electorates[i].getArea() << endl << endl;
            }
            else if(chance > 50)
            {
                getEvent(i);

            }
        }

        cout << string(150, '~') << endl;
        days -= 1;

    }

}

void ElectionGenerator::generateVotes(){

    cout << string(150,'~') << endl;
    cout << right << std::setw(70) << "Voting Begins" << endl;
    cout << string(150,'~') << endl;
    for(unsigned int i = 0; i < totalElectorates; i++){

        cout << string(150,'=') << endl;
        cout << "Vote for Electorate : " << electorates[i].getArea() << endl;
        cout << string(150,'=') << endl;
        cout << left << std::setw(30) << "Group ID";
        cout << left << std::setw(30) << "Candidate";
        cout << left << std::setw(30) << "Votes";
        cout << left << std::setw(30) << "Total Votes" << endl;
        cout << string(150,'-') << endl;

        unsigned int totalGroups = electorates[i].getTotalGroups();
        std::vector<Group> groups = electorates[i].getGroups();

        for(unsigned int j = 0; j < totalGroups; j++){


            cout << left << setw(30) << "Group " + to_string(j+1) + " (" + to_string(groups[j].getPopulation()) + ")" << endl;

            std::vector<Stance> groupStance = groups[j].getStance();

            std::string cPName;
            unsigned int popCounter = 0;

            for(Candidate& c: electorates[i].getCandidates()){

                unsigned int canPop = c.getTrait(POPULARITY);
                if(canPop > popCounter){
                    popCounter = canPop;
                    cPName = c.getPartyName();
                }

                c.setVotes(0);
                std::vector<Stance> canStance = c.getStance();
                double totalRange = 0;

                for(unsigned int m = 0; m < 4; m++) {

                    //Euclidean Distance Formula I think?
                    double range = std::sqrt(std::pow(groupStance[m].getApproach() - canStance[m].getApproach(), 2) + std::pow(groupStance[m].getSignificant() - canStance[m].getSignificant(), 2));
                    totalRange += range;

                }

                c.addRange(totalRange);

            }

            std::string partyName;
            unsigned int pop = 0;

            for(Party& p :parties){
                unsigned int leaderPop = p.getLeader().getTrait(POPULARITY);
                if(leaderPop > pop){
                    pop = leaderPop;
                    partyName = p.getPartyName();
                }
            }

            Candidate* min;
            double minRange = 1000;

            for(Candidate& _can: electorates[i].getCandidates()){

                double canRange = _can.getRange();

                if(canRange < minRange){
                    minRange = canRange;
                    min = &_can;
                }

                if(_can.getPartyName() == partyName){
                    _can.setVotes(groups[j].getPopulation()/4);
                }

                if(_can.getPartyName() == cPName){
                    _can.setVotes(groups[j].getPopulation()/4);
                }

            }

            min->setVotes(groups[j].getPopulation()/2);

            for(Candidate& _c: electorates[i].getCandidates()){

                std::cout << std::left << std::setw(30) << '-' ;
                cout << left << setw(30) << _c.getName();
                cout << left << setw(30) << _c.getVote();
                cout << left << setw(30) << _c.getVotes();
                cout << endl;

            }
            cout << string(150,'-') << endl;

        }

        Candidate winner;
        unsigned int totalVotes = 0;

        for(Candidate& can: electorates[i].getCandidates()){

            unsigned int votes = can.getVotes();

            if(votes > totalVotes){
                totalVotes = votes;
                winner = can;
            }

        }

        for(Party& _party: parties){
            if(_party.getPartyName() == winner.getPartyName()){
                _party.addWin(1);
            }
        }
        cout << "Winner is : " << winner.getName() << " | Total Votes: " << winner.getVotes() << endl;
        cout << string(150,'-') << endl;
        cout << endl;

    }

}

void ElectionGenerator::outputWinner(){

    int mostWins = -1;
    Party winner;
    int draw = 0;

    cout << string(150,'~') << endl;
    cout << std::right << std::setw(70) << "-=+ RESULTS +=-" << endl;
    cout << string(150,'=') << endl;
    cout << "The Results are in! , Here is how the parties done " << endl;
    cout << string(150,'=') << endl;
    for(Party party: parties){

        int wins = party.getWins();
        cout << party.getPartyName() << " Has a total electoral wins of : " << party.getWins() << endl;

        if(wins > mostWins){
            mostWins = wins;
            winner = party;
        }
        else if(wins == mostWins){
            draw = -1;
        }

    }
    cout << string(150,'-') << endl << endl;
    cout << string(150,'~') << endl;

    if(draw == -1){
        cout << "The CybeTron Election Ended With A Draw! " << endl;
    }
    else {
        cout << "The Winner of the CybeTron Election with " << mostWins << " Electoral wins is the party: "
             << winner.getPartyName() << endl;
    }
    cout << string(150,'~') << endl << endl;

    if(mostWins > totalElectorates/2) {
        std::cout << winner.getPartyName() << " won more than 50% of the electorates." << std::endl;
        std::cout << winner.getPartyName() << " form a government." << std::endl;
        std::cout << winner.getLeader().getName() << " is the new leader of the country" << std::endl << endl;
    }
    else{
        std::cout << "No party has won more than 50% of the total electorates. \nThus, There is a hung parliament." << std::endl << endl;
    }
    cout << string(150,'~') << endl << endl;
    cout << "Thankyou for enjoying my simulation to get a new random output \nPlease just run the program again.\nGoodbye!" << endl;

}
