require "screenshot_tag"

YARD::Templates::Engine.register_template_path "templates"

# simplified urls
class YARD::Server::Router
  def route
    path = request.path.gsub(%r{//+}, '/').gsub(%r{^/|/$}, '')
    # return route_index if path.empty?
    
    unless path =~ /\.(css|js|ico)$/
      paths = ["Zajal"] + path.split('/')
      library, paths = *parse_library_from_path(paths)
      return unless library
      return route_docs(library, paths)
    end
    
    nil
  end
end

# make all links awesome
module YARD::Templates::Helpers::HtmlHelper
  def url_for(obj, anchor = nil, relative = true)
    return obj.path.gsub("::", "/").gsub("#", ":").gsub("Zajal", "")
  end
  
  def signature(meth, link = :own_page, show_extras = true, full_attr_name = true, bold = true)
    meth = convert_method_to_overload(meth)
    
    name = full_attr_name ? meth.name : meth.name.to_s.gsub(/^(\w+)=$/, '\1')
    blk = format_block(meth)
    args = !full_attr_name && meth.writer? ? "" : format_args(meth)
    extras = []
    extras_text = ''
    if show_extras
      if rw = meth.attr_info
        attname = [rw[:read] ? 'read' : nil, rw[:write] ? 'write' : nil].compact
        attname = attname.size == 1 ? attname.join('') + 'only' : nil
        extras << attname if attname
      end
      extras << meth.visibility if meth.visibility != :public
      extras_text = ' <span class="extras">(' + extras.join(", ") + ')</span>' unless extras.empty?
    end
    title = (bold ? "<strong>%s</strong>%s %s" : "%s %s %s") % [h(name), args, blk]
    if link
      if meth.is_a?(YARD::CodeObjects::MethodObject)
        link_title = "#{h meth.name(true)} (#{meth.scope} #{meth.type})"
      else
        link_title = "#{h name} (#{meth.type})"
      end
      
      href = link == :same_page ? "##{h meth.name}-instance_method" : url_for(meth)
      link_url(href, title, :title => link_title) + extras_text
    else
      title + extras_text
    end
  end
end

# hack CParser to match my coding style, strip out c comments
module YARD
  module Parser
    class CParser < Base
      def find_method_body(object, func_name, content = @content)
        case content
        when %r"((?>/\*.*?\*/\s*))(?:(?:static|SWIGINTERN)\s+)?(?:intern\s+)?VALUE\s+#{func_name}
                \s*(\([^)]*\))([^;]|$)"xm
          comment, params = $1, $2
          body_text = $&

          remove_private_comments(comment) if comment

          # see if we can find the whole body
          re = Regexp.escape(body_text) + '[^(]*\{.*?^\}'
          body_text = $& if /#{re}/m =~ content
          
          # strip comments out
          body_text = body_text[/#{Regexp.escape(comment)}(.*)/m, 1]

          # The comment block may have been overridden with a 'Document-method'
          # block. This happens in the interpreter when multiple methods are
          # vectored through to the same C method but those methods are logically
          # distinct (for example Kernel.hash and Kernel.object_id share the same
          # implementation

          override_comment = find_override_comment(object)
          comment = override_comment if override_comment

          object.docstring = parse_comments(object, comment) if comment
          object.source = body_text
        when %r{((?>/\*.*?\*/\s*))^\s*\#\s*define\s+#{func_name}\s+(\w+)}m
          comment = $1
          find_method_body(object, $2, content)
        else
          # No body, but might still have an override comment
          comment = find_override_comment(object)
          object.docstring = parse_comments(object, comment) if comment
        end
      end
      
    end
  end
end

module YARD::Templates::Helpers::MethodHelper
  # remove parentheses from method arguments
  def format_args(object)
    return if object.parameters.nil?
    params = object.parameters
    if object.has_tag?(:yield) || object.has_tag?(:yieldparam)
      params.reject! do |param|
        param[0].to_s[0,1] == "&" &&
          !object.tags(:param).any? {|t| t.name == param[0][1..-1] }
      end
    end
    
    unless params.empty?
      args = params.map {|n, v| v ? "#{n} = #{v}" : n.to_s }.join(", ")
      h(" #{args} ")
    else
      ""
    end
  end
  
  def format_constant(value)
    p value
    sp = value.split("\n").last[/^(\s+)/, 1]
    num = sp ? sp.size : 0
    html_syntax_highlight value.gsub(/^\s{#{num}}/, '')
  end
end