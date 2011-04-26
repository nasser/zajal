module Hardware
  class Arduino
    def method_missing meth, *args
      if pin = @digital_pin_names[meth.to_s]
        self.digital pin, *args
      elsif pin = @analog_pin_names[meth.to_s]
        self.analog pin, *args
      end
    end
  end
  
  module Internals
    # remove ids of recycled arduinos from arduino_ary
    cleanup_arduino_ary_hook = proc {
      arduino_ary.reject! do |ard_id|
        begin
          ard_id.to_ref
          false
        rescue RangeError
          true
        end
      end
    }
    
    # update all arduinos videos
    update_arduinos_hook = proc {
      arduino_ary.each do |ard_id|
        ard_id.to_ref.update
      end
    }
    
    # Events::Internals.update_prehooks.push cleanup_arduino_ary_hook
    # Events::Internals.update_prehooks.push update_arduinos_hook
  end
end
    
