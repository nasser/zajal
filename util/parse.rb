#!/usr/bin/env ruby
# Zajal Documentation Generator
# Ramsey Nasser, January 2011
require "rubygems"
require "mustache"

require "util/cdoc"

class String
  def titlecase
    sub(/\b\w/) { $&.upcase }
  end
end

source = open(ARGV[0]).read

module_doc = Mustache.new

# get module name from source file
module_doc[:name] = ARGV[0][/.*\/([^\.]+).c/, 1].titlecase

# module comment is the second comment in the file
module_doc[:description] = source.scan(/\/\*(.*?)\*\//m)[0].first.strip.gsub!(/[^a-zA-Z\n]*\*[^a-zA-Z\n]*/m, "")

# remove one line comments
source.gsub! /\/\*.*\*\//, ""
# slice everything above the first include
source.slice! 0, source.index("#include")

module_doc[:meths] = []

# for documentation coverage
total_examples = 0
total_methods = source.scan("rb_define_method").length

# scan for function comments, parse
source.scan(/\s+\/\*(.*?)\*+\/\s+?VALUE\s+([^(]+)/m).each do |s|
  new_meth = {}
  
  comment, c_name = s
  
  comment.gsub! /^\s*/, ""
  rb_name = source.scan(/rb_define_method\([^,]+,\s*"([^"]+)"\s*,\s*[^(]*\(?\b#{c_name}\b\)?/).first.first
  
  method_doc = CDoc.new comment
  
  new_meth[:name] = rb_name
  new_meth[:description] = method_doc.description
  
  new_meth[:sigs] = method_doc.signatures.map do |arg_list|
    { :arg_list => arg_list.map { |a| a.name }.join(", "),
      :args => arg_list.map { |a| {:name => a.name, :description => a.description} } }
  end
  
  new_meth[:examples] = method_doc.examples.map { |e| {:content => e} }
  total_examples += 1 if new_meth[:examples].size > 0
  new_meth[:returns] = method_doc.returns.join[/^Returns (.*)/, 1].titlecase
  
  module_doc[:meths] << new_meth
end

puts module_doc.render DATA.read

$stderr.puts "#{module_doc[:meths].size}/#{total_methods} = #{(100*module_doc[:meths].size/total_methods).round}% documented"
$stderr.puts "#{total_examples}/#{total_methods} = #{(100*total_examples/total_methods).round}% with examples"

__END__
# {{{name}}}
{{{description}}}

{{#meths}}
# {{{name}}}
{{{description}}}

**Usage**

{{#sigs}}
`{{{name}}} {{{arg_list}}}`

{{#args}}
  * `{{{name}}}` - {{{description}}}
{{/args}}

{{/sigs}}

**Examples**

{{#examples}}
```ruby
{{{content}}}
```

{{/examples}}
{{^examples}}

**No Examples**

{{/examples}}

**Returns**

{{{returns}}}

{{/meths}}