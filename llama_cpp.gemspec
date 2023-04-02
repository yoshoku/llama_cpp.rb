# frozen_string_literal: true

require_relative 'lib/llama_cpp/version'

Gem::Specification.new do |spec|
  spec.name = 'llama_cpp'
  spec.version = LLaMACpp::VERSION
  spec.authors = ['yoshoku']
  spec.email = ['yoshoku@outlook.com']

  spec.summary = 'Ruby bindings for the llama.cpp.'
  spec.description = 'llama_cpp.rb provides Ruby bindings for the llama.cpp.'
  spec.homepage = 'https://github.com/yoshoku/llama_cpp.rb'
  spec.license = 'MIT'

  spec.metadata['homepage_uri'] = spec.homepage
  spec.metadata['source_code_uri'] = spec.homepage
  spec.metadata['changelog_uri'] = "#{spec.homepage}/blob/main/CHANGELOG.md"
  spec.metadata['documentation_uri'] = 'https://yoshoku.github.io/llama_cpp.rb/doc/'

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files = Dir.chdir(__dir__) do
    `git ls-files -z`.split("\x0").reject do |f|
      (f == __FILE__) || f.match(%r{\A(?:(?:bin|test|spec|features)/|\.(?:git|circleci)|appveyor)})
    end
    `git ls-files -z`.split("\x0")
                     .reject { |f| f.match(%r{\A(?:(?:bin|doc|test|spec|node_modules|pkg|tmp|\.git|\.github|\.husky|sig)/)}) }
                     .select { |f| f.match(/\.(?:rb|rbs|h|hpp|c|cpp|md|txt)$/) }
  end
  spec.files.delete('ext/llama_cpp/dummy.rb')
  spec.files.append('ext/llama_cpp/src/LICENSE')

  spec.bindir = 'exe'
  spec.executables = spec.files.grep(%r{\Aexe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions = ['ext/llama_cpp/extconf.rb']

  # Uncomment to register a new dependency of your gem
  # spec.add_dependency "example-gem", "~> 1.0"

  # For more information and examples about making a new gem, check out our
  # guide at: https://bundler.io/guides/creating_gem.html
  spec.metadata['rubygems_mfa_required'] = 'true'
end
