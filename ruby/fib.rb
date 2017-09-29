def fib_to_max max
  i0, i1 = 1, 1
  while i0 < max
    yield i0
    i0, i1 = i1, i0 + i1
  end
end

fib_to_max(1000) {|f| print f, " "}