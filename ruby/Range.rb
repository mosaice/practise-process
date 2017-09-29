class VU
  include Comparable
  attr :volume
  
  def initialize(volume)
    @volume = volume
  end

  def inspect
    '#' * @volume
  end

  def <=> other
    self.volume <=> other.volume
  end

  def succ
    puts @volume.succ
    VU.new(@volume.succ)
  end
end


volum = VU.new(1)..VU.new(9)
volum.to_a.inspect

