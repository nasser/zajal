module Events
  module Internals
    @defaults_proc = Proc.new do
      # size 500
      title "Zajal"
      fullscreen false
      cursor true
      framerate 30
      vertical_sync true
      smoothing false
      alpha_blending false
      color 240
      background 32
      background_auto true
      circle_resolution 32
      rectangle_mode :corner
      line_width 1.0
      fill true
    end
  end
end
