//
// Created by ranko on 18/09/2023.
//
#include "events.h"

Event::Event(std::string c, eventType eT, Trait impact, IssueType rI)
      :content(c), type(eT), impact(impact), relatedIssue(rI){}

Event::Event(std::string c, eventType eT, Trait impact,unsigned int i)
        :content(c), type(eT), impact(impact),iD(i){}