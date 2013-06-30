-module(myfor).
-export([for/3,
	 mysum/1,
	 perms/1
	]
        ).

for(Max, Max, F) -> [F(Max)];
for(I, Max, F)   -> [F(I)|for(I+1, Max, F)].

mysum([Head|Tail]) -> Head + mysum(Tail);
mysum([])  -> 0.

perms([]) -> [[]];
      perms(L)  -> [[H|T] || H <- L, T <- perms(L--[H])].

