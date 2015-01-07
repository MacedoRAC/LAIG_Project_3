:-use_module(library(sockets)).

:-consult(plogcode).

port(60070).

server:-
	port(Port),
	socket_server_open(Port,Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('Accepted connection'), nl,
	server_loop(Stream),
	socket_server_close(Socket).

server_loop(Stream) :-
	repeat,
	read(Stream, ClientMsg),
	write('Received: '), write(ClientMsg), nl,
	parse_input(ClientMsg, MyReply),
	format(Stream, '~q.~n', [MyReply]),
	write('Wrote: '), write(MyReply), nl,
	flush_output(Stream),
	(ClientMsg == quit; ClientMsg == end_of_file), !.

parse_input([addPiece, Board, Player, Column, Row, Size], Ans):-
	placeNewPiece(Row, Column, Player, Board, NewBoard, Size), !,
	Ans is 1.
parse_input([addPiece, Board, Player, Column, Row, Size], Ans):- !,
	Ans is 0.

parse_input([addFence, Xi, Yi, Xf, Yf, FenceDir, Board, Player], Ans):-
	placeBarrier(Xi,Yi,Xf,Yf,FenceDir,Board,NewBoard,Player),!,
	Ans is 1.
parse_input([addFence, Xi, Yi, Xf, Yf, FenceDir, Board, Player], Ans):- !,
	Ans is 0.

parse_input([gameOver, Board], 1):-
	gameOver(Board), !.
parse_input([gameOver, Board], 0):- !.

parse_input([calculatePontuations, Board], [Pp1, Pp2]):-
	calculatePontuations(Board, Pp1, Pp2), !.
parse_input([calculatePontuations, Board], 0):- !.

parse_input(quit, ok-bye):- !.
parse_input(end_of_file, ok-bye):- !.

/*

server_input([getPontuations, Board], [P1, P2]) :-
	calculatePoints(Board, P1, P2), !.

server_input([getPontuations, Board], 0) :- !.
*/