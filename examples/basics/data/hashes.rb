# Ramsey Nasser - Apr 2011
# Play around with the code to see how it changes

# a hash is a like an array, except where arrays can only use integers as
# indexes (e.g. ary[5]) hashes can use anything (e.g. hsh["hello"])

# they are created using curly braces. this is an empty hash.
hsh = {}

# you can store elements in it like this
hsh["language"] = "zajal"

# and get them back like this
text hsh["language"]

# again, just like an array but with the ability to use anything as an index

# to create a hash with predefined contents, do this
other_hsh = {"language" => "zajal", "awesome" => true, "age" => 187}

# you can store more elements
other_hsh["school"] = "parsons"

# and get it all back
text other_hsh["awesome"]
text other_hsh["age"]
text other_hsh["school"]