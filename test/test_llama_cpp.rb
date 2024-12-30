# frozen_string_literal: true

require 'test_helper'

class TestLLaMACpp < Minitest::Test
  def test_version_numbers
    refute_nil(::LLaMACpp::VERSION)
  end
end
