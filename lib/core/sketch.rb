module Zajal
	class Sketch
		include Math
		include Zajal
		include Graphics
		include Version

		attr_reader :file

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
			@file = open(file)
			@file_last_modified = @file.mtime
			instance_eval @file.read
		end

		def stale?
			@file.mtime > @file_last_modified
		end
	end
end