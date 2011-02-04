require "util/tomdoc"

class CDoc < TomDoc::TomDoc
  def tomdoc
    raw.split("\n").map do |line|
      line =~ /^(\s*\* ?)/ ? line.sub($1, '') : nil
    end.compact.join("\n")
  end
  
  def signatures
    sigs = []
    args_string = tomdoc.match(/\n\n(.*?)(Returns|Examples)/m)[1].strip
    
    args_string.split("\n\n").each do |variation|
      args = []
      
      variation.split("\n").each do |line|
        next if not line =~ /^[^\s]\s\-\s/ or line.strip.empty?
        
        if line =~ /^[^\s]/
          param, desc = line.split(" - ")
          args << TomDoc::Arg.new(param.strip, desc.strip)
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