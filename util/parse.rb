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

puts "Here we go..."

module_doc = Mustache.new

source = open(ARGV[0]).read
init_func = source[/void Init.*\}/m]
source_body = source[source.index("#include")..source.index(init_func)-1].gsub(/\/\*.*\*\//, "")

# first big comment is the module description
module_doc[:description] = source[0, 1] == "/" ? source[/^\/\*.*?\*\//m].gsub(/^.?\*.?/, "") : ""

# pull declarations out of Init_* function
module_doc[:name] = module_name = init_func[/void Init_([^\(]+)/, 1]
module_var  = init_func[/([^\s=]+)\s*=\s*rb_define_module[^\(]*\([^"]+"#{module_doc[:name]}"/, 1]

# for documentation coverage
total_examples = 0
total_methods = source.scan("rb_define_private_method").length

# extract private module methods
module_doc[:methods] = []
init_func.scan(/rb_define_private_method\(#{module_var}[^"]+"([^"]+)"[^"]+RB_FUNC\(([^\)]+)/).each do |private_method|
  method_hash = {}
  method_hash[:name], c_name = private_method
  
  # diamonds are a hacker's best friend...
  comment = source_body.gsub(/ *(?:\/\*|\*\/)/, "◊").scan(/\s+◊([^◊]+?)◊\s+?VALUE\s+#{c_name}\b/m).first.to_s
  next if comment.empty?
  method_doc = CDoc.new comment

  method_hash[:description] = method_doc.description
  
  p method_doc.signatures

  method_hash[:signatures] = method_doc.signatures.map do |arg_list|
    { :arg_list => arg_list.map { |a| a.name }.join(", "),
      :args => arg_list.map { |a| {:name => a.name, :description => a.description} } }
  end
  
  method_hash[:examples] = method_doc.examples.map { |e| {:content => e} }
  total_examples += 1 if method_hash[:examples].size > 0
  method_hash[:returns] = method_doc.returns.join#[/^Returns (.*)/, 1].titlecase
  
  module_doc[:methods] << method_hash
end

exit
puts module_doc.render DATA.read

# get module name from source file
module_doc[:name] = ARGV[0][/.*\/([^\.]+).c/, 1].titlecase

# module comment is the second comment in the file
module_doc[:description] = source.scan(/\/\*(.*?)\*\//m)[0].first.strip.gsub!(/[^a-zA-Z\n]*\*[^a-zA-Z\n]*/m, "")

# remove one line comments
source.gsub! /\/\*.*\*\//, ""
# slice everything above the first include
source.slice! 0, source.index("#include")

module_doc[:meths] = []

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

{{#methods}}
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

{{/methods}}