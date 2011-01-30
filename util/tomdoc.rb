# Copyright (c) 2010 Tom Preston-Werner, Chris Wanstrath
# originally from https://github.com/defunkt/tomdoc 60fd7389ba0eabf97c93
module TomDoc
  class InvalidTomDoc < RuntimeError
    def initialize(doc)
      @doc = doc
    end

    def message
      @doc
    end

    def to_s
      @doc
    end
  end
  
  class Arg
    attr_accessor :name, :description

    def initialize(name, description = '')
      @name = name.to_s
      @description = description
    end

    def optional?
      @description.downcase.include? 'optional'
    end
  end
  
  class TomDoc
    attr_accessor :raw, :name

    def initialize(name, text)
      @name = name
      @raw = text.to_s.strip
      
      validate
    end

    def to_s
      @raw
    end

    def self.valid?(text)
      new(text).valid?
    end

    def valid?
      validate
    rescue InvalidTomDoc
      false
    end

    def validate
      if !raw.include?('Returns')
        raise InvalidTomDoc.new("Method `#{@name}' has no `Returns' statement.")
      end

      if tomdoc.split("\n\n").size < 2
        raise InvalidTomDoc.new("Method `#{@name}' has no description section.")
      end

      true
    end

    def tomdoc
      raw.split("\n").map do |line|
        line =~ /^(\s*\* ?)/ ? line.sub($1, '') : nil
      end.compact.join("\n")
    end

    def sections
      tomdoc.split("\n\n")
    end

    def description
      sections.first
    end

    def signatures
      sigs = []
      args_string = tomdoc.match(/\n\n(.*?)(Returns|Examples)/m)[1].strip
      
      args_string.split("\n\n").each do |variation|
        args = []
        
        variation.split("\n").each do |line|
          next if line =~ /^#{@name}/ or line.strip.empty?
          
          if line =~ /^[^\s]/
            param, desc = line.split(" - ")
            args << Arg.new(param.strip, desc.strip)
          else
            args.last.description += line.squeeze(" ")
          end
        end
        
        def args.takes_block?
          self.any? { |a| a.name =~ /^&/ }
        end
        
        sigs << args
      end

      sigs
    end

    def examples?
      examples.size > 0
    end
    
    def examples
      if tomdoc =~ /(\s*Examples\s*(^\s*.+?)\s*(?:Returns|Raises))/m
        $2.split("\n\n").each do |e|
          # determine leading line's indent and adjust accordingly
          i = e.match(/^(\s*)[^\s]/).captures.first.length
          e.gsub! /^\s{#{i}}/, ""
        end
      else
        []
      end
    end

    def returns
      if tomdoc =~ /^\s*(Returns.+)/m
        lines = $1.split("\n")
        statements = []

        lines.each do |line|
          next if line =~ /^\s*Raises/
          if line =~ /^\s+/
            statements.last << line.squeeze(' ')
          else
            statements << line
          end
        end

        statements
      else
        []
      end
    end

    def raises
      if tomdoc =~ /^\s*(Raises.+)/m
        lines = $1.split("\n")
        statements = []

        lines.each do |line|
          if line =~ /^\s+/
            statements.last << line.squeeze(' ')
          else
            statements << line
          end
        end

        statements
      else
        []
      end
    end
  end
end
