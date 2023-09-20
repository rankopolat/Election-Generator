#include <iostream>
#include <fstream>
#include "election.h"

class ValueException : public std::exception {
private:
    std::string message;

public:

    ValueException(const char* message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }

};

int main(int argc, char* argv[]) {

    unsigned int eNum;
    unsigned int days;

    if(argc != 3){

        std::cerr << "Please make sure when executing to do it in the correct format \n"
                     "./APE electoralTotal campaignDays Thank you!" << std::endl;
        return 1;
    }

    try {

        eNum = std::stoi(argv[1]);
        if(eNum > 10 || eNum <= 0){
            throw ValueException("Please enter a electorate number less than or equal to 10");
        }

        days = std::stoi(argv[2]);
        if(days > 30 | days <= 0){
            throw ValueException("Please enter a Campaign day number less than or equal to 30 and greater than 0");
        }

    }
    catch (const std::invalid_argument& e){
        std::cerr << "Invalid argument as a parameter " << e.what() << std::endl;
        return 1;
    }
    catch (const ValueException& e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "Welcome to the Electoral Campaign" << std::endl;

    ElectionGenerator eg;

    eg.loadIssues();
    eg.generateParties(eNum);
    eg.generateElectorate(eNum);
    eg.loadEvents();

    eg.outputIssues();
    eg.partyReport();
    eg.elecReport();

    eg.runEvent(days);

    eg.partyReport();
    eg.elecReport();

    eg.generateVotes();
    eg.outputWinner();

    return 0;

}
