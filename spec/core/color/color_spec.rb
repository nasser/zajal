require_relative '../../spec_helper'
require_relative '../../../lib/core/color'

describe Color do
  describe "#new" do
    it "should create a new Color::Rgb instance given RGBA values" do
      Color.new(:rgb, 1, 2, 3, 4).should be_kind_of(Color::Rgb)
    end
  end
end
