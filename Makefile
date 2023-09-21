APE:	main.o election.o entities.o electorates.o events.o Party.o
	g++ -o APE main.o election.o entities.o electorates.o events.o Party.o

main.o: main.cpp election.h
	g++ -c main.cpp

election.o:	election.cpp newParty.h election.h random.h
	g++ -c election.cpp

entities.o:	entities.cpp entities.h random.h
	g++ -c entities.cpp

electorates.o:	electorates.cpp issue.h random.h
	g++ -c electorates.cpp

events.o: events.cpp events.h
	g++ -c events.cpp

Party.o:	Party.cpp newParty.h issue.h random.h
	g++ -c Party.cpp