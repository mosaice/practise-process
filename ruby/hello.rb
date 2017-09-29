class Song
  @@plays = 0
  attr_reader :name, :artist, :duration
  def initialize(name, artist, duration)
    @name = name
    @artist = artist
    @duration = duration
    @plays = 0
  end

  # def to_s
  #   "song: #@name #@artist #@duration"
  # end
  def play
    @plays += 1
    @@plays += 1
  end
end


song = Song.new('xixi', 'haha', 123)

puts song.to_s

puts "#{song.name} #song.artist #song.duration"