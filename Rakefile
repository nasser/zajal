namespace :docs do
	DocsDirectory = "docs"
	OutputDirectory = "#{DocsDirectory}/out"
	StaticDirectory = "#{DocsDirectory}/static"
	SourceDirectory = "src"
	
	DocsURL = "docs.zajal.cc"

	desc "Remove generated documentation"
	task :clean do
		rm_rf OutputDirectory
	end

	file OutputDirectory do
		require_relative 'docs/lib/yard-zajal'

		log.show_progress = true
		YARD.parse("src/*.cc")
		FileUtils.mkpath "#{OutputDirectory}"
		log.capture("Writing index") { File.open("#{OutputDirectory}/index.html", 'w') { |f| f.write Index.render } }
		YARD::Registry.all(:method).each do |methobj|
			log.capture("Writing #{methobj.file_path}") do
				FileUtils.mkpath "#{OutputDirectory}/#{methobj.file_path}/"
				File.open("#{OutputDirectory}/#{methobj.file_path}/index.html", 'w') { |f| f.write Mathod.new(methobj).render }
			end
		end

		cp_r FileList["#{StaticDirectory}/*"], OutputDirectory
	end
	
	desc "Build the documentation"
	task :build => OutputDirectory

	desc "Deploy documentation to http://#{DocsURL}"
	task :deploy => :build do
		require "aws/s3"
		include AWS::S3

		require "yard"

		log.show_progress = true
		log.capture("Connecting to Amazon") do
			Base.establish_connection!(
				:access_key_id => ENV['AMAZON_ACCESS_KEY_ID'],
				:secret_access_key => ENV['AMAZON_SECRET_ACCESS_KEY']
			)
		end

		Bucket.find(DocsURL).each { |obj| log.capture("Deleting #{obj.key}") { obj.delete } }

		# upload new documentation
		cd OutputDirectory
		Dir["**/*"].select { |f| f =~ /\.(html|css|js)$/ }.each do |filename|
			log.capture("Storing #{filename}") { S3Object.store(filename, open(filename), 'docs.zajal.cc', :access => :public_read) }
		end

	end
end
