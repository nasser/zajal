# booleans are true and false values, often used in conditionals.
a = true
b = false

if a then
  text "a is true"
end

if b then
  text "b is true"
end

# everything in zajal evaluates to true except false and nil
c = 90
if c then
  text "c evaluates to true"
end

if nil then
  text "nil is true"
end