OBJS = SongRating.o main.o UserRatings.o misc.o FileIO.o Cluster.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -O2 $(DEBUG)
LFLAGS = -I. -Wall $(DEBUG)

exec1:$(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o exec8
UserRatings.o: UserRatings.cpp UserRatings.h
	$(CC) $(CFLAGS) UserRatings.cpp
SongRating.o: SongRating.cpp SongRating.h
	$(CC) $(CFLAGS) SongRating.cpp
misc.o: misc.cpp misc.h UserRatings.h 
	$(CC) $(CFLAGS) misc.cpp
FileIO.o: FileIO.cpp FileIO.h UserRatings.h SongRating.h
	$(CC) $(CFLAGS) FileIO.cpp
Cluster.o: Cluster.cpp Cluster.h SongRating.h
	$(CC) $(CFLAGS) Cluster.cpp
main.o: UserRatings.h UserRatings.cpp main.cpp SongRating.h misc.h misc.cpp FileIO.cpp FileIO.h Cluster.h Cluster.cpp
	$(CC) $(CFLAGS) main.cpp UserRatings.h misc.h FileIO.h Cluster.h
clean:
	rm -rf *o exec8
tar:  
	tar -cvf PA8.tar SongRating.cpp SongRating.h UserRatings.cpp UserRatings.h main.cpp misc.h misc.cpp FileIO.cpp FileIO.h Cluster.cpp Cluster.h Makefile songs.txt ratings 

