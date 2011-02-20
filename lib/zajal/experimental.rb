# Framework for highly experimental features
module Zajal
  module Experimental
    module Internals; @experiments = {}; end
    
    private
    # Enable an experiment. Experiments cannot be disabled, so you'll have to
    # restart the interpreter if anything breaks.
    # 
    # sym - The name of the experiment to enable
    # 
    # Returns something
    def experiment! sym
      unless Internals.experiments[sym].nil?
        Internals.experiments[sym].call
        Internals.experiments[sym] = nil
      end
    end
    
    def self.make_experiment sym, &blk
      Internals.experiments[sym] = blk
    end
    
    
    # Experimental float division -- this might break a lot of of things, but
    # makes a lot of syntax super clean. Dropping .to_f everywhere is a pain,
    # and this kind of division is extremely common in creative code
    make_experiment :integer_division do
      class ::Fixnum
        def / other
          fdiv other
        end
      end
    end
    
  end
end

include Experimental