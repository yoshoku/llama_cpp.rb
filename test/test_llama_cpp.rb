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

  def test_module_functions
    assert_equal(1, ::LLaMACpp.token_bos)
    assert_equal(2, ::LLaMACpp.token_eos)
    assert_instance_of(String, ::LLaMACpp.print_system_info)
    assert_match(/AVX = \d{1} | AVX2 = \d{1} | AVX512 = \d{1}/, ::LLaMACpp.print_system_info)
  end
end
