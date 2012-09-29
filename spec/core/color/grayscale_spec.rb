require_relative '../../spec_helper'
require_relative '../../../lib/core/color/color'
require_relative '../../../lib/core/color/grayscale'
require_relative '../../../lib/core/color/rgb'

describe Color::Grayscale do
  describe "#to_rgb" do
    it "should create a new Color::RGB instance at the right grayscale value" do
      Color::Grayscale.new(100, 40).to_rgb.to_a.should == [100, 100, 100, 40]
    end
  end
end
