require 'yard'

# link generating and parsing methods
module Linkify
  def self.href str, nspace=nil
    return str if str =~ /:\/\//
    linked_object = YARD::Registry.resolve(nspace, str)
    linked_object = YARD::Registry.resolve(nil, str) unless linked_object

    linked_object.path if linked_object
  end

  def self.linkify str, nspace=nil
    return str unless str
    str.scan(/\{[^\{\}]+\}/).each do |link|
      value = link[/[^\{\}]+/]
      href = Linkify.href(value, nspace)
      str.gsub! link, "<a href='#{href}'>#{value}</a>" if href
      str.gsub! link, value unless href
    end

    str
  end
end

# TODO uninitialized constant YARD::Tags::Directive (NameError) ?!
YARD::Tags::EndGroupDirective.superclass

require 'tempfile'
require 'base64'

module YARD::Tags
  # # directive for common zajal settings idiom
  # class SettingDirective < Directive
  #   def call
  #     getter = SyntaxTag.new :syntax, "#{object.name} -> current_#{object.name}"
  #     setter = SyntaxTag.new :syntax, "#{object.name} new_#{object.name}"
  #     param = Tag.new :param, "The new value for #{object.name}", tag.text, "new_#{object.name}"
  #     rturn = Tag.new :return, "The current value of #{object.name}", tag.text, "current_#{object.name}"
  #     parser.tags << setter << getter << param << rturn
  #   end
  # end

  class SeeTag < Tag
    attr_reader :name, :text

    def initialize(tagname, text)
      @tag_name = tagname
      @name = text.split.first
      @text = text.split[1..-1].join ' '
    end

    def href
      # Linkify.href(@name, object.namespace)
    end
  end

  class ExampleTag < Tag
    attr_reader :title, :code, :image_b64
    
    def initialize(tagname, text)
      text_lines = text.each_line.to_a
      @tag_name = tagname
      @title = text_lines.shift.strip
      @title = nil if @title.empty?
      @code = text_lines.join.strip
    end
  end

  class ScreenshotTag < ExampleTag
    def initialize tagname, text
      super tagname, text

      log.capture("Rendering example '#{@title}'") do
        codefile = Tempfile.new "zajal-example"
        codefile.write "draw do\n#{@code}\nend"
        codefile.rewind
        shotpath = codefile.path + "-shot.png"

        @@renderer ||= Zajal::Frontends::Headless.new 100, 100
        @@renderer.sketch = Zajal::Frontends::Headless::Sketch.new @code
        @@renderer.run
        @@renderer.fbo.to_pixels.save shotpath

        @image_b64 = Base64.encode64 open(shotpath).read
      end
    end
  end


  Library.define_tag "Example", :example, ExampleTag
  Library.define_tag "Screenshot", :screenshot, ScreenshotTag
  Library.define_tag "See Also", :see, SeeTag
  # Library.define_tag "Return", :return, :with_types_and_name
  # Library.define_directive :setting, SettingDirective
end

require 'mustache'
require 'kramdown'

class String
  def to_html
    Kramdown::Document.new(self.strip).to_html
  end

  def linkify namespace=:root
    self.split(/\{|\}/).map do |str|
      obj = YARD::Registry.resolve(namespace, str)
      obj ? "[#{obj.name}](#{obj.path.sub /^[^:]*::/, '#'})" : str
    end.join
  end
end

module Methodish
  def overloads; tags(:overload) end
  def syntaxes; tags(:syntax) end
  def example; examples.first end
  def examples; tags(:screenshot) + tags(:example) end
  def params; tags(:param) end
  def returns; tags(:return) end
  def useful_returns; returns.select { |t| t.types and not t.types.all? { |y| y == "nil" or y == "Object" } } end
  def clean_parameters; parameters.flatten.select{|a| not a.nil? }.to_a.join(', ') end
end

module YARD::Tags
  class Tag
    def clean_types; types.join ',' if types end
    def linkified_text; text.linkify.to_html end
    def linkified_name; name.linkify.to_html end
  end

  class OverloadTag
    include Methodish
    def summary; object.summary end
    def elaboration; docstring.linkify.to_html end
    def simple_path
      pos = object.tags(:overload).index(self)
      pos == 0 ? object.path.sub("Zajal::", "") : object.path.sub("Zajal::", "") + "-#{pos}"
    end
  end
end

module YARD::CodeObjects
  class Base
    def simple_path; path.sub("Zajal::", "")  end
    def summary; docstring.summary.linkify.to_html end #Linkify.linkify(docstring.summary, namespace) end
    def elaboration; docstring.chomp('.') == docstring.summary.chomp('.') ? nil : docstring.sub(docstring.summary, "").linkify.to_html end
    def related; tags(:see) end
    def short_file; file.sub(/.*zajal\//, "") end # TODO kind of hard coded, no? 
  end
  
  class MethodObject
    include Methodish
  end

  class ClassObject
    alias class_name name
    def class_methods; zajal_methods.select { |meth| meth.scope == :class } end
    def instance_methods; zajal_methods.select { |meth| meth.scope == :instance } end
    def instance_name
      lower_name = name.to_s.downcase
      lower_name[0] + lower_name[1..-2].gsub(/(a|e|i|o|u|y)/, '') + (lower_name[-1] == "e" ? "" : lower_name[-1])
    end
  end

  class NamespaceObject
    def methods; meths.sort { |a, b| a.name <=> b.name } end
    def classes; children.select { |obj| obj.type == :class } end
    def zajal_methods; methods.select { |m| m.tag(:api) and m.tag(:api).text == "zajal" } end
    def elaboration
      if docstring.chomp('.') == docstring.summary.chomp('.')
        nil
      else
        docstring.sub(docstring.summary, "").linkify(self).to_html
      end
    end
  end
end

class Index < Mustache
  self.template_path = 'docs/templates/'
  def modules
    YARD::Registry.all(:module).select { |m| m.tag(:api) and m.tag(:api).text == "zajal" }
  end
end

# class Mathod < Index
#   self.template_path = 'docs/templates/'
#   self.template_file = 'docs/templates/method.mustache'
#   def initialize codeobject
#     @object = codeobject
#   end

#   def method
#     @object
#   end
# end