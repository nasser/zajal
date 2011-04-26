def init
  if object
    case object
    when '_index.html'
      @page_title = options[:title]
      sections :layout, [:index, [:listing, [:files, :objects]]]
    when CodeObjects::Base
      @page_title = format_object_title(object)
      type = object.root? ? :module : object.type
      sections :layout, [T(type)]
    end
  else
    sections :layout, [:contents]
  end
  
  # sections :layout
end