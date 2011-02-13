# S-Exp Traversal Methods

class Array
  def fetch exp
    # puts ""
    # puts "#{exp}"
    
    exp = exp.split("/").map { |e| e.to_sym }
    arr = self
    
    until arr.empty? or exp.empty? do
      # pp arr
      arr = arr.select { |e| e.respond_to? :first and e.first == exp.first }.map { |e| e.drop 1 }.flatten 1
      exp.shift
    end

    arr
  end
  
  def match? exp
    not fetch(exp).empty?
  end
end