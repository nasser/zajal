module Zajal
  class Console < IO
    def initialize
      @buffer = ""
    end
    
    def write s
      @buffer += s
    end
    
    def clear_buffer
      @buffer = ""
    end
    
    def get_buffer
      @buffer.size > 0 ? @buffer : nil
    end
    
    def get_buffer!
      buffer = get_buffer
      clear_buffer
      
      return buffer
    end
    
    def prefix_lines prefix
      @buffer = @buffer.each_line.map { |line| prefix + line }.join "\n"
    end
    
  end
end

$stdout = Zajal::Console.new
$stderr = Zajal::Console.new