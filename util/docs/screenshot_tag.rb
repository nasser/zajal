require 'tempfile'
require 'base64'

module YARD::Tags
  class ScreenshotTag < Tag
    attr_reader :title, :code, :code_base64
    
    def initialize(tagname, text)
      text_lines = text.each_line.to_a
      @tag_name = tagname
      @title = text_lines.shift.strip
      @code = text_lines.join
      @code_base64 = ScreenshotTag.base64 @code
    end
    
    # converts code to the base64 representation of a screenshot of that code
    def self.base64 code, w=100, h=100
      # prepare screenshot file
      shotpath = "shot.png"

      # append screenshot command and write incoming code to a temp file
      # TODO zajal should support piped input and a screenshot-output switch
      injected_code = <<-CODE
      #{code}
      if frame > 2 then
        grab_screen.save '#{shotpath}'
        exit
      end
      CODE
      codefile = Tempfile.new "zajal_code"
      codefile.write injected_code
      codefile.rewind

      # generate the screenshot
      `zajal --width=#{w} --height=#{h} #{codefile.path}`

      # locate the screenshot based on the folder of the temporary code
      shotpath = File.dirname(codefile.path) + "/" + shotpath
      codefile.close
      codefile.unlink

      # load in screenshot as a string
      shotfile = File.open(shotpath)
      shotcontent = shotfile.read
      shotfile.close
      File.unlink(shotfile.path)

      # base64 encode the screenshot and return it
      Base64.encode64 shotcontent
    end
  end
end

YARD::Tags::Library.define_tag("Screenshot Example", :screenshot, YARD::Tags::ScreenshotTag)