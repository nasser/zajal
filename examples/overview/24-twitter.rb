# twitter
require "json"

q = "thesis"
results = []

setup do
  size 800, 300
  title "Twitter"
  
  results = twitter_search(q)
end

update do
  once_every 5 do
    results = twitter_search(q)
  end
end

draw do
  results.each do |result|
    line = "#{result['from_user']} : #{result['text']}"
    text line.length > 97 ? line[0..94] + "..." : line
  end
end

def twitter_search query
  JSON::parse(open("http://search.twitter.com/search.json?q=#{query}").read)["results"]
end