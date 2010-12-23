# attr-away, logic to make all instance variables public by default

# make all instance variables effectively public. is this stupid?
class Object
  def method_missing meth, arg=nil
    meth = meth.to_s
    if meth =~ /=$/ and instance_variable_defined? "@#{meth.reject '='}" then
      self.class.class_eval { attr_writer meth.reject("=").to_sym }
      self.send meth, arg
    elsif meth =~ /[a-z_][a-zA-Z0-9_]*/ and instance_variable_defined? "@#{meth}" # TODO can method names be capitalized?
      self.class.class_eval { attr_reader meth.to_sym }
      self.send meth
    else
      raise NoMethodError, "undefined method `#{meth}' for #{self.inspect}"
    end
  end
  
  alias :old_respond_to? :respond_to?
  def respond_to? sym, include_private=false
    meth = sym.to_s
    if meth =~ /=$/ and instance_variable_defined? "@#{meth[0...meth.length-1]}"
      true
    elsif instance_variable_defined? "@#{meth}"
      true
    else
      old_respond_to? sym, include_private
    end
  end
end
