require 'open-uri'


open('https://qlear.build/welcome') do |f|
  reg = /app-(\w+).bundle.js/
  reg.match f.read
  p $1
end