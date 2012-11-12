# -*- encoding: utf-8 -*-
$:.push File.expand_path("lib", File.dirname(__FILE__))
require "zajal"

Gem::Specification.new do |s|
  s.name          = "zajal"
  s.version       = Zajal::VERSION
  s.platform      = Gem::Platform::RUBY
  s.authors       = ["Ramsey Nasser"]
  s.email         = ["ram@nas.sr"]
  s.homepage      = "http://zajal.cc/"
  s.summary       = "The creative coding language that lets you code like a poet"
  s.description   = ""

  s.files         = %w[README.md Rakefile LICENSE]
  s.files         += Dir.glob("lib/**/*.rb")
  s.files         += Dir.glob("examples/**/*.rb")
  s.bindir        = "bin"
  s.require_paths = ["lib"]
end
