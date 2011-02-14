# S-Exp Traversal Methods

class Array
  def fetch exp
    exp = exp.split("/").map { |e| e.to_sym }
    arr = self
    
    until arr.empty? or exp.empty? do
      arr = arr.select { |e| e.respond_to? :first and e.first == exp.first }.map { |e| e.drop 1 }.flatten 1
      exp.shift
    end

    arr
  end
end