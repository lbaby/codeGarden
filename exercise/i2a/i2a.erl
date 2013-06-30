-module(i2a).
-export([insert_sort/1]).

insert(Fun,  K, []) -> [K];

% insert  K into [H,T]
insert(Fun,  K, [H|T]) ->
    case Fun(K,H) of
        true -> [K,H|T];
	false -> [ H | insert(Fun, K,T)]
    end.


insert_sort([],S) -> S;

insert_sort([H|T],S) ->
     insert_sort(T,insert(fun(K, X)-> K =< X end, H, S) ).

insert_sort(L) ->
     insert_sort(L,[]).


