#ifndef ASS2V2_ISSUE_H
#define ASS2V2_ISSUE_H
#include <string>

enum IssueType{

    NAVIGATION,
    ROAMBA,
    EMOJI,
    STREETLIGHT,
    TOILET

};

class Issue{

private:

    std::string code;
    std::string statement;
    IssueType type;

public:

    Issue(){};
    Issue(std::string c,std::string s,IssueType t)
        :code(c),statement(s),type(t){}

    std::string getCode(){return code;}
    std::string getStatement(){return statement;}
    IssueType getType(){return type;}

};

class Stance{

private:

    int approach;
    int significant;
    int range;
    Issue issue;

public:

    void setApproach(int a);
    void setSignificant(int s);
    void setIssue(Issue& i);
    void setRange(int rad);
    int getApproach() const;
    int getSignificant() const;
    int getRange() const;
    Issue getIssue();

};

#endif //ASS2V2_ISSUE_H
