# frozen_string_literal: true

require 'test_helper'

class TestContextParams < Minitest::Test
  def setup
    @params = LLaMACpp::ContextParams.new
  end

  def test_default_values
    assert_equal(512, @params.n_ctx)
    assert_equal(-1, @params.seed)
    refute(@params.logits_all)
    refute(@params.embedding)
  end

  def test_setter_and_getter
    @params.n_ctx = 1024
    @params.seed = 1
    @params.logits_all = true
    @params.embedding = true

    assert_equal(1024, @params.n_ctx)
    assert_equal(1, @params.seed)
    assert(@params.logits_all)
    assert(@params.embedding)
  end
end
