class PrefixArray < Array
  def initialize pfx, *args; @pfx = pfx; super *args end
  def to_s; map { |i| @pfx + i }.join " " end
end

class SuffixArray < Array
  def initialize sfx, *args; @sfx = sfx; super *args end
  def to_s; map { |i| i + @sfx }.join " " end
end