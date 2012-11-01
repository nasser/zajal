module Zajal
  # The representation of user code.
  # 
  # A {Sketch} knows how to load a user's +.zj+ file, refresh it live, and
  # expose its contents to the rest of Zajal to interact with.
  # 
  # @example
  #   # in user.zj
  #   setup do
  #     puts "Starting sketch!"
  #   end
  #   
  #   draw do
  #     circle 50, 50, 10
  #   end
  #   
  #   # inside Zajal
  #   sketch = Zajal::Sketch.new "user.zj"
  #   sketch.setup # => "Starting sketch!"
  #   sketch.draw  # => draws circle
  # 
  # @api internal
  class Sketch
    # The {File} this sketch is watching
    attr_reader :file, :code, :bare
    attr_accessor :frontend

    @@pre_hooks = {}
    @@post_hooks = {}

    def self.before_event event, &blk
      @@pre_hooks[event] << blk
    end

    def self.after_event event, &blk
      @@post_hooks[event] << blk
    end

    # Support a named event in user code
    # 
    # Allow an event block named +event+ in user code. This allows
    # frontends and gems to expose their own events to user code.
    # Frontends and gems call the event methods when appropriate to make
    # up Zajal's run loop.
    # 
    # @example Basic setup/update/draw loop
    #   # in user.zj
    #   foo = 0
    #   setup do
    #     puts "Setting up!"
    #   end
    #   
    #   update do
    #     foo += 1
    #     puts foo
    #   end
    #   
    #   draw do
    #     circle width/2, height/2, sin(foo) * 100
    #   end
    #   
    #   # in interpreter
    #   Sketch.support_event :setup
    #   Sketch.support_event :update
    #   Sketch.support_event :draw
    #   
    #   sketch = Sketch.new "user.zj"
    #   
    #   sketch.setup # => Setting up!
    #   while true do
    #     sketch.update # => 1, 2, 3, 4, 5...
    #     Native.do_graphics_setup
    #     sketch.draw # => draws pulsating circle
    #     Native.do_graphics_cleanup
    #   end
    # 
    # @param event [#to_s] name of the event to support
    # 
    # @note This documents incomplete functionality
    # @todo Iron out custom events
    def self.support_event *events
      events.each do |event|
        @@supported_events ||= []
        @@supported_events += events.map { |e| e.to_sym }
        @@pre_hooks[event.to_sym] = []
        @@post_hooks[event.to_sym] = []

        module_eval <<-EVENT
          def #{event} *args, &blk
            if not blk.nil?
              @#{event}_proc = blk
            elsif blk.nil?
              @@pre_hooks[:#{event}].each { |hook| instance_eval &hook }
              @#{event}_proc.call(*args) unless @#{event}_proc.nil?
              @@post_hooks[:#{event}].each { |hook| instance_eval &hook }
            end
          end
        EVENT
      end
    end

    %w[setup update draw].each { |event| support_event event }

    # Create a new {Sketch} object watching +file+
    # 
    # The file's contents are loaded into the returned {Sketch} object.
    # The event blocks in the file are exposed as instance methods as
    # described in {Sketch.support_event}.
    # 
    # @param file [#to_s] the file to watch
    # 
    # @note This documents incomplete functionality
    # @todo Iron out custom events
    # 
    # @see Sketch.support_event
    def initialize code_or_file=nil, &blk
      if blk
        instance_eval &blk
      else
        if code_or_file.is_a? File
          @file = code_or_file
          @file_last_modified = @file.mtime
          @code = @file.read

        elsif code_or_file.is_a? String
          @code = code_or_file

        else
          raise ArgumentError, "Can't create sketch!"
        end

        @bare = true
        # look for :call, nil, :setup/:draw/:update in the sexp
        @code.to_sexp.flatten.each_cons(3) { |a, b, c| @bare = false if a == :call and @@supported_events.member? c }
        
        if @bare
          instance_eval "draw do; #{@code}\nend"
        else
          instance_eval @code
        end
      end
    end

    # @return [Boolean] has the watched file has been updated?
    def stale?
      @file.nil? ? false : @file.mtime > @file_last_modified
    end

    # Refresh sketch and keep the sketch running going
    def refresh_continue
      return nil if @file.nil?

      sk = self.class.new @file.path
      sk.copy_instance_variables_from self, [:@setup_proc, :@draw_proc, :@update_proc, :@file_last_modified]
      sk
    end

    # Reload the file and start the sketch over
    def refresh_restart
      return nil if @file.nil?

      self.class.new @file.path
    end

    # @see http://apidock.com/rails/Object/copy_instance_variables_from
    # @api private
    def copy_instance_variables_from object, exclude = []
      vars = object.instance_variables.map(&:to_s) - exclude.map(&:to_s)
      vars.each { |name| instance_variable_set(name, object.instance_variable_get(name)) }
    end

    include Math
    include Zajal
    include App
    include Graphics
    include Images
    include Typography
    include Mathematics
    include Time
    include Version
  end
end