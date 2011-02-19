require "util/tomdoc"

class CDoc < TomDoc::TomDoc
  def tomdoc
    raw.split("\n").map do |line|
      line =~ /^(\s*\* ?)/ ? line.sub($1, '') : nil
    end.compact.join("\n")
  end
  
  def signatures
    sig_string = sections[1] =~ /^(Examples|Returns)/ ? nil : sections[1]
    arg_string = sections[1] =~ /^(Examples|Returns)/ ? nil : sections[2]
    
    if sig_string.nil? and arg_string.nil?
      return []
    elsif (not sig_string.nil?) and arg_string.nil?
      raise "Signatures given, but no argument lists found!"
    end
    
    # build hash of args
    last_arg = nil
    args = {}
    arg_string.split("\n").each do |line|
      # next if not line =~ /^[^\s]+\s\-\s/ or line.strip.empty?
      next if line.strip.empty?
      
      if line =~ /^[^\s]+\s\-\s/
        param, desc = line.split(" - ")
        args[param.strip] = TomDoc::Arg.new(param.strip, desc.strip)
        last_arg = args[param.strip]
      else
        last_arg.description += line.squeeze(" ")
      end
    end
    
    # tie signatures to args
    sig_string.split("\n").reduce([]) do |sigs, line|
      sigs << line[/[^\s]+\s*(.*)/, 1].split(", ").map do |arg|
        if args[arg].nil?
          raise "unknown argument `#{arg}' used in signature `#{line}', but not found in argument list!"
        else
          args[arg];
        end
      end
    end
    
  end
  
  def examples
    if tomdoc =~ /(\s*Examples\n+(.+?)\n+(?:Returns|Raises))/m
      $2.split("\n\n").each do |e|
        # determine leading line's indent and adjust accordingly
        i = e[/^(\s*)[^\s]/, 1].length
        e.gsub! /^\s{#{i}}/, ""
      end
    else
      []
    end
  end
  
  def examples?
    examples.size > 0
  end
  
end