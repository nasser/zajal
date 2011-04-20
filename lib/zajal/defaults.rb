module Zajal
  module Events
    module Internals
      # FIXME this is a kludge. Get this into the language properly soon.
      @current_event = nil
      
      def self.reset_defaults
        @defaults = {
          size: [500, 500],
          title: ["Zajal"],
          fullscreen: [false],
          cursor: [true],
          framerate: [30],
          vertical_sync: [true],
          smoothing: [false],
          alpha_blending: [false],
          color: [240],
          background: [32],
          background_auto: [true],
          circle_resolution: [32],
          rectangle_mode: [:corner],
          line_width: [1.0],
          fill: [true]
        }
      end
      
      reset_defaults
      
      @defaults_proc = Proc.new do
        # FIXME size and background are problematic, removed!
        %w(background title fullscreen cursor framerate vertical_sync smoothing
           size alpha_blending color background_auto circle_resolution
           rectangle_mode line_width fill).each do |meth|
             eval "#{meth}(*@defaults[:#{meth}])"
           end
           
      end
      
    end
  end
end