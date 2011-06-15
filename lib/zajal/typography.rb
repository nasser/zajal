module Typography
  module Internals
    # TODO this should be a Point when that gets implemented
    @stacked_text_initial_x = 1
    @stacked_text_initial_y = 11
    @stacked_text_line_height = 13
    @stacked_text_x = 10
    @stacked_text_y = @stacked_text_initial_y
    
    # get a font file from a css-style name/array
    def self.get_font_file css_name
      # build input array
      if css_name.respond_to? :each
        fonts = css_name
      else
        fonts = [css_name]
      end
      
      # iterate through each font, directory and extension, return first hit
      fonts.each do |fnt|
        %w{.ttf .otf .dfont .ttc .TTF .OTF .DFONT .TTC}.each do |ext|
          [App::Internals.data_path, "/System/Library/Fonts/", Dir.home + "/Library/Fonts/"].each do |dir|
            if File.exists? dir + fnt + ext
              return dir + fnt + ext
            end
          end
        end
      end
    
      return nil
    end
  end
end