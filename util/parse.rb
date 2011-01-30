#!/usr/bin/env ruby
# Zajal Documentation Generator
# Ramsey Nasser, January 2011
require "erb"

require "util/tomdoc"
include TomDoc

source = open(ARGV[0]).read

# get module name from source file
module_name = ARGV[0].scan(/([^\.]+).c/).first.first

# module comment is the second comment in the file
module_comment = source.scan(/\/\*(.*?)\*\//m)[0].first.strip.gsub!(/[^a-zA-Z\n]*\*[^a-zA-Z\n]*/m, "")

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
  
  documented_methods << TomDoc::TomDoc.new(rb_name, comment)
end

# output
# print "#{module_name}\n#{'='*module_name.length}\n\n"
# print "#{module_comment}\n\n"
# documented_methods.each do |m|
#   print "#{m.name}\n"
#   print "#{'-'*m.name.length}\n"
#   print "#{m.description}\n\n"
#   
#   print "**Usage**:\n\n"
#   m.signatures.each do |args|
#     print "`#{m.name} #{args.reject {|a| a.name =~ /^&/ }.map {|a| a.name}.join(", ")}#{args.takes_block? ? " { ... }" : ""}`\n\n"
#     args.reject {|a| a.name =~ /^&/ }.each { |a| print " * `#{a.name}` : #{a.description}\n" }
#     print "\n"
#   end
#   
#   if m.examples? then
#     print "\n**Examples**:\n\n"
#     m.examples.each { |e| print e.gsub /^/, "    " }
#   end
#   
#   print "\n\n#{m.returns}\n\n\n"
# end

print ERB.new(DATA.read).result
# File.open(ARGV[0].gsub("yaml", "html"), 'w') { |f| f.write ERB.new(DATA.read).result }
$stderr.puts "#{documented_methods.length}/#{total_methods} = #{(100*documented_methods.length.to_f/total_methods).round}% documented"

__END__
<!DOCTYPE html>
<html>
    <head>
        <title>Zajal Documentation : <%= module_name %></title>
        <meta http-equiv="Content-type" content="text/html; charset=utf-8"/>
    </head>
    <body>
        <h1><%= module_name %></h1>
        <p><%= module_comment %></p>
        
        <% documented_methods.each do |m| %>
          <h2><%= m.name %></h2>
          <p><%= m.description %></p>
          <h3>Usage</h3>
          <% m.signatures.each do |args| %>
            <p><code><%= m.name %> <%= args.reject {|a| a.name =~ /^&/ }.map {|a| a.name}.join(", ") + (args.takes_block? ? " { ... }" : "") %></code></p>
            <ul>
            <% args.reject {|a| a.name =~ /^&/ }.each do |arg| %>
              <li><code><%= arg.name %></code> <%= arg.description %></li>
            <% end %>
            </ul>
          <% end %>
          <h3>Examples</h3>
          <% m.examples.each do |e| %>
            <pre><code><%= e %></code></pre>
          <% end %>
          <h3>Returns</h3>
          <p><%= m.returns %></p>
        <% end %>
    </body>
</html>