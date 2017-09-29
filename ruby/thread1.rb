class Chaster
  attr_reader :count
  def initialize(name)
    @name = name
    @count = 0
  end

  def chase(other)
    while @count < 5
      while @count - other.count > 1
        puts "self #@count other #{other.count}"
        Thread.pass
        puts "#@name pass"
      end
      @count += 1
      print "#@name #@count \n"
    end
  end
end


c1 = Chaster.new("A")
c2 = Chaster.new("B")

threads = [
  Thread.new { Thread.stop; c1.chase(c2)},
  Thread.new { Thread.stop; c2.chase(c1)},
]

# start_index = rand(2)
# puts start_index
# threads[start_index].run
# threads[1 - start_index].run
# puts 1
threads[1].run
threads[0].run

threads.each {|t| t.join}