module Typography
  module Internals
    # TODO this should be a Point when that gets implemented
    @stacked_text_initial_x = 1
    @stacked_text_initial_y = 11
    @stacked_text_line_height = 13
    @stacked_text_x = 10
    @stacked_text_y = @stacked_text_initial_y
  end
  
  # TODO load system fonts by name, css style
  class Font
    alias :__load :load
    def load font, size
      loaded = false
    
      # build input array
      fonts = []
      fonts << font if not font.respond_to? :each
      fonts = fonts | font if font.is_a? Array
    
      # iterate through each font
      fonts.each do |f|
        ["", ".ttf", ".otf", ".TTF", ".OTF"].each do |ext|
          # try to load font with various extensions
          if File.exists? App::Internals.data_path + f + ext
            __load App::Internals.data_path + f + ext, size
            loaded = true
            break
          end
        end
      
        break if loaded
      end
    
      raise "Font not found!" if not loaded
    end
  end
end