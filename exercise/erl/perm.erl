perms([]) -> [[]];
perms(L)  -> [[H|T] || H <- L, T <- perms(L--[H])].

"123"
H="1"  | perm("23")
	H="2" | perm("3")
		H="3" | perm([])
	H="3" | perm("2")
		H="2" | perm([])
H="2"  | perm("13")
	H="1" | perm("3")
		H="3" | perm([]) 
	H="3" | perm("1")
		H="1" | perm([])
H="3"  | perm("12")
	H="1" | perm("2")
		H="2" | perm([])
	H="2" | perm("1")
		H="1" | perm([])
	
["123","132","213","231","312","321"]


 case c(lib_misc) of 
 { ok, Val } ->
 {work,Val};
 {error, Why} ->
 {error,Why};
 end.
		
       

