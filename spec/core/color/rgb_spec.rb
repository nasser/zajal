require_relative '../../spec_helper'
require_relative '../../../lib/core/color'

describe Color::RGB do
  subject {Color::RGB.new(255, 128, 64, 32)}
  describe "#to_a" do
    it "should return an array of RGBA values" do
      subject.to_a.should == [255, 128, 64, 32]
    end
  end

  describe "#to_hash" do
    it "should return a hash of RGBA values" do
      subject.to_hash.should == {r: 255, g: 128, b: 64, a: 32}
    end
  end

  describe "#to_rgb" do
    it "should create a new Color::RGB instance at an accurate HSV value" do
      Color::RGB.new(255, 0, 0, 40).to_hsv.to_a.should == [0, 255, 255, 40]
    end
  end
end
