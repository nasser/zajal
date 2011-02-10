def process_error
  return "" if $!.nil?
  
  case $!
  when SyntaxError
    message = $!.to_s[/^\(eval\):\d*:(.*?)$/m, 1].strip
    line_no = $!.to_s[/^\(eval\):(\d*):.*?$/m, 1].strip
    "#{$0}:#{line_no}\n#{message}"
  else
    message = $!.to_s
    stack_frame = $!.backtrace.select { |bt| bt =~ /^\(eval\)/ }.first
    line_no = stack_frame[/:(\d+):/, 1] if stack_frame
    "#{$0}:#{line_no}\n#{message}"
  end
end
