require 'tempfile'
require 'base64'

# converts code to the base64 representation of a screenshot of that code
def screenshot code
  # prepare screenshot file
  shotpath = "shot.png"
  
  # append screenshot command and write incoming code to a temp file
  # TODO zajal should support piped input and a screenshot-output switch
  injected_code = <<-CODE
  size 100
  #{code}
  if frame > 1 then
    grab_screen.save '#{shotpath}'
    exit
  end
  CODE
  codefile = Tempfile.new "zajal_code"
  codefile.write injected_code
  codefile.rewind
  
  # generate the screenshot
  `zajal #{codefile.path}`
  
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