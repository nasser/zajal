typewriter = ""

setup do
  size 500, 100
end

draw do
  text "Type normally, press enter to speak"
  text "==="
  text typewriter
end

key_down do |key|
  case key
  when :enter, :return
    `say #{typewriter}`
    typewriter = ""
  when :backspace
    typewriter.slice! typewriter.length-1
  else
    typewriter += key if key.printable?
  end
end
