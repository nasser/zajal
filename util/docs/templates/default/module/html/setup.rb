def init
  sections :header, :pre_docstring, T('docstring'),
    :children, [:item_summary],
    :constant_summary, [T('docstring')], :inherited_constants, 
    :attribute_summary, [:item_summary], 
    :method_summary, [:item_summary], :inherited_methods,
    :methodmissing, [T('method_details')],
    :attribute_details, [T('method_details')], 
    :method_details_list, [T('method_details')]
end

def children_hash obj
  children = {}
  
  obj.children.each do |child|
    children[child.type] ||= []
    children[child.type] << child
  end
  
  children
end