module Zajal
  module Frontends
    # @api internal
    class Frontend
      # The sketch to render
      # 
      # A sketch must be set before {#run} is called.
      attr_accessor :sketch
    end
  end
end