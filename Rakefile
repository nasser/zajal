require_relative 'lib/zajal'

namespace :docs do
  DocsDirectory = "docs"
  OutputDirectory = "#{DocsDirectory}/out"
  StaticDirectory = "#{DocsDirectory}/static"
  SourceDirectory = "lib"
  
  DocsURL = "docs.zajal.cc"

  desc "Remove generated documentation"
  task :clean do
    rm_rf OutputDirectory
  end

  desc "Build the documentation"
  task :build, :file do |t, args|
    require_relative 'docs/lib/yard-zajal'

    log.show_progress = true
    d = Dir.pwd
    YARD.parse(args[:file] ? args[:file] : SourceDirectory)
    Dir.chdir d
    FileUtils.mkpath "#{OutputDirectory}"
    log.capture("Writing index") { File.open("#{OutputDirectory}/index.html", 'w') { |f| f.write Index.render } }
    YARD::Registry.all(:method).each do |methobj|
      if methobj.tag(:api) and methobj.tag(:api).text == "zajal"
        log.capture("Writing #{methobj.file_path}") do
          FileUtils.mkpath "#{OutputDirectory}/#{methobj.file_path}/"
          File.open("#{OutputDirectory}/#{methobj.file_path}/index.html", 'w') { |f| f.write Mathod.new(methobj).render }
        end
      end
    end

    cp_r FileList["#{StaticDirectory}/*"], OutputDirectory
  end

  task :build => :clean

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
