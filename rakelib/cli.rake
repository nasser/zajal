namespace :cli do
  desc "Make CLI binary"
  task :bin => BINARY do
    puts "Built Zajal #{ZAJAL_GIT_SHORT_HASH} CLI binary to #{BINARY}"
  end
  
  file BINARY => ZAJAL_OBJ do
    directory BIN_DIR
    sh "#{CXX} #{CXXFLAGS} #{OF_INCLUDES} #{RUBY_INCLUDES} #{ZAJAL_INCLUDES} #{OF_FRAMEWORKS} #{ZAJAL_LIBRARIES} #{ZAJAL_OBJ.join " "} -o #{BINARY}"
  end
  
  rule ".o" => ".cc" do |t|
    sh "#{CXX} #{CXXFLAGS} #{OF_INCLUDES} #{RUBY_INCLUDES} #{ZAJAL_INCLUDES} -c -o #{t.name} #{t.source}"
  end
end