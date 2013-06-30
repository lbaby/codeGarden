class Proc
def memoize
  cache = {}
  lambda { |*args| 
    unless cache.has_key?(args)
      cache[args] = self[*args]
    end
    cache [args]
  }
end

end
factorial =  lambda {|x| return 1 if x== 0; x*factorial[x-1];}.memoize

puts factorial 10



