all: app
app: app.o Admin.o User.o Hotel.o hotel_manager.o
	g++ -o app app.o Admin.o User.o Hotel.o hotel_manager.o
	rm -f *.o

app.o: app.cpp Admin.h User.h Hotel.h
	g++ -c app.cpp

Admin.o: Admin.cpp Admin.h
	g++ -c Admin.cpp 

User.o: User.cpp User.h Hotel.h
	g++ -c User.cpp

Hotel.o: Hotel.cpp Hotel.h
	g++ -c Hotel.cpp	

hotel_manager.o : hotel_manager.cpp hotel_manager.h
	g++ -c hotel_manager.cpp



clean:
	rm -f *.o app