test/testinho : test/testezinho.cpp obj/Coordinates.o obj/Match.o obj/History.o obj/Player.o obj/Piece.o obj/Rook.o obj/King.o obj/Pawn.o obj/Move.o obj/Color.o obj/GameState.o 
	g++ $^ -c -I include -o $*

obj/Coordinates.o : chess/model/util/Coordinates.cpp
	g++ $^ -c -I include -o $*.o

obj/Match.o : chess/model/Match.cpp obj/Board.o
	g++ $^ -c -I include -o $*.o

obj/Piece.o : chess/model/Pieces/Piece.cpp
	g++ $^ -c -I include -o $*.o

obj/Board.o :  obj/Piece.o obj/Rook.o obj/Knight.o obj/Bishop.o obj/Queen.o obj/King.o obj/Pawn.o chess/model/Board.cpp
	g++ $^ -c -I include -o $*.o

obj/History.o : chess/model/History.cpp
	g++ $^ -c -I include -o $*.o

obj/Player.o : chess/model/Player.cpp
	g++ $^ -c -I include -o $*.o

obj/Rook.o : chess/model/Pieces/Rook.cpp
	g++ $^ -c -I include -o $*.o

obj/King.o : chess/model/Pieces/King.cpp
	g++ $^ -c -I include -o $*.o

obj/Knight.o : chess/model/Pieces/Knight.cpp
	g++ $^ -c -I include -o $*.o

obj/Bishop.o : chess/model/Pieces/Bishop.cpp
	g++ $^ -c -I include -o $*.o

obj/Queen.o : chess/model/Pieces/Queen.cpp
	g++ $^ -c -I include -o $*.o

obj/Pawn.o : chess/model/Pieces/Pawn.cpp
	g++ $^ -c -I include -o $*.o

obj/Move.o : chess/include/Move.hpp
	g++ $^ -c -I include -o $*.o

obj/Color.o : chess/include/Color.hpp
	g++ $^ -c -I include -o $*.o

obj/GameState.o : chess/include/GameState.hpp
	g++ $^ -c -I include -o $*.o

clean:
	rm obj/*.o test/testinho
