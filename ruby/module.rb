require "./test"

class TestModule
  include Test
  attr :name
  @name = 'xixi'
  def initialize(name)
    @name = name
  end
end


t = TestModule.new("wo")
Test.echo
t.instance_echo

puts Test.to_s