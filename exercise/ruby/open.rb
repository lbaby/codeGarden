open("|-", "r+") do |child| 
    if child
       child.puts "hello  from parent "+ $$.to_s
    else
       $stderr.puts "child " + $$.to_s+ " get msg:" + gets
    end
end
