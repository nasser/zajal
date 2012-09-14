module Zajal
	class Sketch
		include Zajal::Graphics
		include Zajal::Version
		include Math

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
			@code = open(file).read
			instance_eval @code
		end
	end
end