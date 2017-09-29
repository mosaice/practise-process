count = 0
threads = []
Thread.abort_on_exception = true
10.times do |i|
  threads[i] = Thread.new do
    raise "test" if i == 5
    sleep(rand(0.1))
    Thread.current["mycount"] = count
    count += 1
  end
end


threads.each do |t|
  # begin
    t.join
    puts t["mycount"]
  # rescue => exception
  #   puts "rescue #{exception}"
  # end
end