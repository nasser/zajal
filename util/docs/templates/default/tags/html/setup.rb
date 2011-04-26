def init
  tags = [:param] + (Tags::Library.visible_tags - [:abstract, :deprecated, :note, :todo, :param])
  create_tag_methods(tags - [:example, :option, :overload, :see])
  sections :index, tags
  sections.any(:overload).push(T('docstring'))
end