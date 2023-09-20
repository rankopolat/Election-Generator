#include <vector>
#include "issue.h"
#include "random.h"

//float Stance::difference(Stance stance);
void Stance::setApproach(int a){approach = a;}
void Stance::setSignificant(int s){significant = s;}
void Stance::setIssue(Issue& i){issue = i;}
void Stance::setRange(int rad){range = rad;}

int Stance::getApproach() const{return approach;}
int Stance::getSignificant() const{return significant;}
int Stance::getRange() const{return range;}
Issue Stance::getIssue(){return issue;}



