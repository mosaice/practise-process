class MyLogger
  private_class_method :new
  @@logger = nil
  def MyLogger.create
    @@logger = new unless @@logger
    @@logger
  end

  # def logger
  #   @@logger
  # end
end


MyLogger.create

puts MyLogger.create
puts MyLogger.create