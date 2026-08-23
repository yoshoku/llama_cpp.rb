# frozen_string_literal: true

require 'test_helper'

class TestLLaMACpp < Minitest::Test
  def test_version_numbers
    refute_nil(::LLaMACpp::VERSION)
  end

  def test_llama_version
    assert_match(/^\d+\.\d+\.\d+$/, LLaMACpp.llama_version)
  end
end
