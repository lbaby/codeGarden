-module(myasc).
-export([asc/1]).
 asc(255) ->[255];
 asc(N) -> [N | asc(N+1)].
