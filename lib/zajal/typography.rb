# TODO load system fonts by name, css style
class Font
  alias :c_load :load
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
          c_load App::Internals.data_path + f + ext, size
          loaded = true
          break
        end
      end
      
      break if loaded
    end
    
    raise "Font not found!" if not loaded
  end
end