//
// Created by ranko on 18/09/2023.
//

#ifndef ASS2V2_EVENTS_H
#define ASS2V2_EVENTS_H
#include <string>
#include "newParty.h"
#include "issue.h"

enum eventType{

    DEBATE,
    CANDIDATE,
    LEADER,
    ISSUE
};

class Event{

private:

    std::string content;
    eventType type;
    Trait impact;
    unsigned int iD;
    IssueType relatedIssue;

public:

    Event(std::string, eventType, Trait, IssueType);
    Event(std::string, eventType, Trait, unsigned int);

    std::string getContent(){return content;}
    eventType getType(){return type;}

    void setContent(std::string s){
        content = s;
    }

    Trait getImpact(){
        return impact;
    }

    unsigned int getID(){return iD;}

    std::string printImpact(){

        switch(impact){

            case POPULARITY:
                return "Popularity: ";
            case RELIABILITY:
                return "Reliability: ";
            case INFLUENCE:
                return "Influence: ";
            case INTELLIGENCE:
                return "Intelligence: ";
            case COURAGE:
                return "Courage: ";
            case LOYALTY:
                return "Loyalty: ";
            case DEBATE_EXP:
                return "Debate Experience: ";
            default:
                return "UNKNOWN";

            }
        }

};

#endif //ASS2V2_EVENTS_H
