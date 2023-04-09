# frozen_string_literal: true

require 'test_helper'

class TestLLaMACpp < Minitest::Test
  def test_version_numbers
    refute_nil(::LLaMACpp::VERSION)
    refute_nil(::LLaMACpp::LLAMA_CPP_VERSION)
    refute_nil(::LLaMACpp::LLAMA_FILE_VERSION)
    refute_nil(::LLaMACpp::LLAMA_FILE_MAGIC)
    refute_nil(::LLaMACpp::LLAMA_FILE_MAGIC_UNVERSIONED)
  end
end
