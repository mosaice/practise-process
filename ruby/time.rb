print "(p) or (t)"
times = gets
print "number: "
number = Integer(gets)

calc = lambda {|n| n * number} if times =~ /t/
calc = lambda {|n| n + number} if times =~ /p/

puts (1..10).collect(&calc).to_s

