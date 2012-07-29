class TrueClass
  def to_i; 1 end
end

class FalseClass
  def to_i; 0 end
end

module Hardware
  class Arduino
    attr_reader :ran_setup_proc

    def setup &blk
      @setup_proc = blk
      self.instance_eval &blk if @ran_setup_proc
    end

    def analog pin
      read_analog pin
    end

    def digital *args
      pin = args.first

      case args.size
      when 1
        # read digital value
        case get_pin_mode pin
        when :input
          return read_digital(pin) == 1
        when :pwm
          return read_pwm pin
        when :servo
          return read_servo pin
        end

      when 2
        # write digital value
        value = args.last.to_i
        case get_pin_mode pin
        when :output
          write_digital pin, value
        when :pwm
          write_pwm pin, value
        when :servo
          write_servo pin, value
        end
      end
    end

    def name_digital pin, name
      @digital_pin_names[name.to_s] = pin
    end

    def name_analog pin, name
      @analog_pin_names[name.to_s] = pin
    end

    def method_missing meth, *args
      if pin = @digital_pin_names[meth.to_s]
        self.digital pin, *args
      elsif pin = @analog_pin_names[meth.to_s]
        self.analog pin, *args
      else
        super meth, *args if ready? and initialized?
      end
    end

    def perform_setup
      (0..13).to_a.each { |pin| set_pin_mode pin, :output }
      self.instance_eval &@setup_proc if @setup_proc
      init_analog_pins
      @ran_setup_proc = true
    end

  end
  
  module Internals
    cleanup_arduino_ary_hook = proc {
      arduino_hash.each_pair do |dev, ard|
        ard.disconnect
      end
    }
    
    setup_arduinos_hook = proc {
      arduino_hash.each_pair do |dev, ard|
        ard.update if ard.ready? and not ard.initialized?
        if ard.ready? and ard.initialized? and !ard.ran_setup_proc then
          ard.perform_setup
        end
      end
    }

    update_arduinos_hook = proc {
      arduino_hash.each_pair do |dev, ard|
        if ard.ready? and ard.initialized?
          ard.update
        end
      end
    }


    Events::Internals.update_prehooks.push setup_arduinos_hook
    Events::Internals.update_prehooks.push update_arduinos_hook
    Events::Internals.exit_posthooks.push cleanup_arduino_ary_hook
  end
end
    
