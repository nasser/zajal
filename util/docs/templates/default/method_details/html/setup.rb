def init
  super
end

def source_location
  case object.file
  when /\.(c|cc|cpp)$/
    "/* File '#{h object.file}'#{" line " + object.line.to_s if object.line} */"
  when /\.(rb)$/
    "# File '#{h object.file}'#{" line " + object.line.to_s if object.line}"
  end
end