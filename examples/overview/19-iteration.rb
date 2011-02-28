# size 400, 200
# 
# 5.times do
#   text "Hello!"
# end
# 
# 5.times do |n|
#   text "Hello! #{n}"
# end
# 
# a = [1, 2, "hello", "world", 5.4]
# a.each do |e|
#   text e
# end
# 
# for i in 0..a.length
#   text a[i]
# end
# 
# a.each_pair do |e, f|
#   text "#{e}, #{f}"
# end
# 
# a.select { |e| e.class == String }.each do |e|
#   text e
# end
# 
# a.select! { |e| e.class == String }
# text a
# 
# a << 99
# 
# text a.join "..."
# 
