module Zajal
	class Sketch
		include Math
		include Zajal
		include Graphics
		include Version

		def self.support_event event
			module_eval <<-EVENT
				def #{event} *args, &blk
					@#{event}_proc = blk unless blk.nil?
					@#{event}_proc.call(*args) if blk.nil? and not @#{event}_proc.nil?
				end
			EVENT
		end

		%w[setup update draw].each { |event| support_event event }
		def initialize file
			@background_color = {r: 160, g: 37, b: 37}

			@code = open(file).read
			instance_eval @code
		end
	end
end