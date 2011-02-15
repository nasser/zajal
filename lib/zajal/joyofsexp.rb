# S-Exp Traversal Methods

class Array
  # TODO support non-root paths
  def fetch exp
    if exp[0] == "/" then
      exp = exp.split("/").map { |e| e.to_sym }.drop 1
      arr = self
    
      until arr.empty? or exp.empty? do
        arr = arr.select { |e|
          e.respond_to? :first and e.first == exp.first
        }.map { |e|
          e.drop 1
        }.flatten 1
        
        exp.shift
      end

      arr
    end
  end
end