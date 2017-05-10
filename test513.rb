#!/usr/bin/ruby
N = 100000

100.times do |n|
  x = rand(N + 1)
  y = rand(N + 1)
  puts "### [TEST NO.#{n + 1}]: (x, y) = (#{x}, #{y}) ###"
  result = `./prob513.exe #{x} #{y}`
  if result.index("OK!") == nil
    puts "RESULT: ERROR"
    exit 1
  else
    puts "RESULT: OK"
  end
end

