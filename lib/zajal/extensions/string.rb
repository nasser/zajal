class String
  # Converts strings to UpperCamelCase.
  #
  # Examples:
  #   "named_color".camelize                # => "ActiveModel"

  # Taken partially from ActiveSupport::Inflections, but dramatically simplified.
  def camelize
    self.sub(/^[a-z\d]*/) { $&.capitalize }
  end
end
