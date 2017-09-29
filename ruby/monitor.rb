

class Counter
  attr_reader :count

  def initialize
    @count = 0
  end

  def tick
    @count = @count + 1
  end
end

c = Counter.new

t1 = Thread.new { 100_000.times { c.tick }}
t2 = Thread.new { 100_000.times { c.tick }}

t1.join
t2.join

puts c.count
