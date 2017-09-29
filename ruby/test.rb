module Test
  name = "test module"
  def Test.echo
    puts name
  end
  
  def instance_echo
    puts @name
  end

end