require 'yard'

# link generating and parsing methods
module Linkify
	def self.href str, nspace
		return str if str =~ /:\/\//
		linked_object = YARD::Registry.resolve(nspace, str)
		linked_object = YARD::Registry.resolve(nil, str) unless linked_object

		"/#{linked_object.file_path}/" if linked_object
	end

	def self.linkify str, nspace
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
	# directive for common zajal settings idiom
	class SettingDirective < Directive
		def call
			getter = SyntaxTag.new :syntax, "#{object.name} -> current_#{object.name}"
			setter = SyntaxTag.new :syntax, "#{object.name} new_#{object.name}"
			param = Tag.new :param, "The new value for #{object.name}", tag.text, "new_#{object.name}"
			rturn = Tag.new :return, "The current value of #{object.name}", tag.text, "current_#{object.name}"

			parser.tags << setter << getter << param << rturn
		end
	end

	class SeeTag < Tag
		attr_reader :name, :text

		def initialize(tagname, text)
			@tag_name = tagname
			@name = text.split.first
			@text = text.split[1..-1].join ' '
		end

		def href
			Linkify.href(@name, object.namespace)
		end
	end

	class SyntaxTag < Tag
		attr_reader :signature, :name, :params, :return

		def initialize(tagname, text)
			@tag_name = tagname
			@signature = text[/[^-]+/].strip
			@name = text[/[^\s]+/].strip
			@params = text.sub(/\->.*$/, '').sub(@name, '').strip # TODO do we need the array?
			@return = text["->"] ? text[/[^>]+$/].strip : nil
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

			log.capture("Rendering example '#{@title}'") do
				codefile = Tempfile.new "zajal-example"
				codefile.write @code
				codefile.rewind
				shotpath = File.dirname(codefile.path) + "-shot.png"

				`zajal --width=100 --height=100 --screenshot=#{shotpath} #{codefile.path}`

				@image_b64 = Base64.encode64 open(shotpath).read

				codefile.close true
				File.unlink(shotpath)
			end
		end
	  end


	Library.define_tag "Example", :example, ExampleTag
	Library.define_tag "Syntax", :syntax, SyntaxTag
	Library.define_tag "Return", :return, :with_types_and_name
	Library.define_tag "See Also", :see, SeeTag
	Library.define_directive :setting, SettingDirective
end

require 'mustache'

class YARD::Tags::Tag
	def clean_types; types.join ',' if types end
	def linkified_text; Linkify.linkify(text, object.namespace) end
	def linkified_name; Linkify.linkify(name, object.namespace) end
end

module YARD::CodeObjects
	class Base
		def file_path; path.gsub(/(::|#)/, "/").sub("Zajal/", "").downcase  end
		def summary; Linkify.linkify(docstring.summary, namespace) end
		def elaboration; docstring.chomp('.') == summary.chomp('.') ? nil : Linkify.linkify(docstring.sub(docstring.summary, ""), namespace) end
		def related; tags(:see) end
		def short_file; file.sub(/.*zajal\//, "") end # TODO kind of hard coded, no? 
	end
	
	class MethodObject
		alias method_name name
		def syntaxes; tags(:syntax) end
		def example; tag(:example) end
		def examples; tags(:example) + tags(:screenshot) end
		def params; tags(:param) end
		def returns; tags(:return) end
	end

	class ClassObject
		alias class_name name
		def class_methods; methods.select { |meth| meth.scope == :class } end
		def instance_methods; methods.select { |meth| meth.scope == :instance } end
	end

	class ModuleObject
		alias module_name name
	end

	class NamespaceObject
		def methods; meths.sort { |a, b| a.name <=> b.name } end
		def classes; children.select { |obj| obj.type == :class } end
	end
end

class Index < Mustache
	self.template_path = 'docs/templates/'
	def modules
		YARD::Registry.all(:module)
	end
end

class Mathod < Index
	self.template_path = 'docs/templates/'
	self.template_file = 'docs/templates/method.mustache'
	def initialize codeobject
		@object = codeobject
	end

	def method
		@object
	end
end