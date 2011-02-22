YARD::Templates::Engine.register_template_path "/Users/nasser/Workspace/zajal/util/docs/templates"

module YARD::Templates::Helpers
  module MethodHelper
    # alias :old_format_args :format_args
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
  end
end