module Hardware
  class Arduino
    attr_reader :ran_setup_proc

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
      ((2..13).to_a + (16..21).to_a).each { |pin| set_pin_mode pin, :input }
      self.instance_eval &@setup_proc
      @ran_setup_proc = true
    end

    def digital
      DigitalPinArray.new self
    end

    def analog
      AnalogPinArray.new self
    end

    class PinArray
      def initialize arduino, read_msg=nil, write_msg=nil
        @arduino = arduino
        @read_message = read_msg
        @write_message = write_msg
      end

      def [] i
        arduino.send(@read_message, i)
      end

      def []= i, v
        arduino.send(@write_message, i, v)
      end
    end

    class DigitalPinArray < PinArray
      def initialize arduino
        super arduino, :read_digital, :write_digital
      end
    end

    class AnalogPinArray < PinArray
      def initialize arduino
        super arduino, :read_analog
      end
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
    
