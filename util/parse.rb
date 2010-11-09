#!/usr/bin/env ruby
# Zajal Documentation Generator
# Ramsey Nasser, November 2010
require "util/tomdoc"
include TomDoc

source = open(ARGV[0]).read

# get category name from source file
category = ARGV[0].scan(/ofrb_([^\.]+).c/).first.first

# category comment is the second comment in the file
category_comment = source.scan(/\/\*(.*?)\*\//m)[1].first.strip.gsub!(/[^a-zA-Z\n]*\*[^a-zA-Z\n]*/m, "")

# remove one line comments
source.gsub! /\/\*.*\*\//, ""
# slice everything above the first include
source.slice! 0, source.index("#include")

# documentation coverage
documented_methods = []
total_methods = source.scan("rb_define_method").length

# scan for function comments, parse
source.scan(/\s+\/\*(.*?)\*+\/\s+?VALUE\s+([^(]+)/m).each do |s|
  comment, c_name = s
  
  comment.gsub! /^\s*/, ""
  rb_name = source.scan(/rb_define_method\([^,]+,\s*"([^"]+)"\s*,\s*[^(]*\(?\b#{c_name}\b\)?/).first.first
  
  d = TomDoc::TomDoc.new rb_name, comment

  documented_methods << d
end

# output
print "#{category}\n#{'='*category.length}\n\n"
print "#{category_comment}\n\n"
documented_methods.each do |m|
  print "#{m.name}\n"
  print "#{'-'*m.name.length}\n"
  print "#{m.description}\n\n"
  
  print "**Usage**: `#{m.name} #{m.args.map {|a| a.name}.join(", ")}`\n\n"
  m.args.each { |a| print " * `#{a.name}` : #{a.description}\n" }
  
  print "\n**Examples**:\n\n"
  m.examples.each { |e| print "<pre><code>#{e}</code></pre>\n\n" }
  
  print "\n#{m.returns}\n\n\n"
end

$stderr.puts "#{documented_methods.length}/#{total_methods} = #{(100*documented_methods.length.to_f/total_methods).round}% documented"