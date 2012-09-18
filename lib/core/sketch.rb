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

		def refresh_continue
			sk = Sketch.new @file.path
			sk.copy_instance_variables_from self, [:@setup_proc, :@draw_proc, :@update_proc, :@file_last_modified]
			sk
		end

		def refresh_restart
			Sketch.new @file.path
		end

		# http://apidock.com/rails/Object/copy_instance_variables_from
		def copy_instance_variables_from object, exclude = []
			vars = object.instance_variables.map(&:to_s) - exclude.map(&:to_s)
			vars.each { |name| instance_variable_set(name, object.instance_variable_get(name)) }
		end
	end
end