require_relative '../../spec_helper'
require_relative '../../../lib/core/color'

describe Color::HSV do
  subject {Color::HSV.new(0, 255, 255, 40)} # Red, at 40/255 opacity
  describe "#to_a" do
    it "should return the HSV values in an array" do
      subject.to_a.should == [0, 255, 255, 40]
    end
  end

  describe "#to_hash" do
    it "should return the HSV values in a hash" do
      subject.to_hash.should == {h: 0, s: 255, v: 255, a: 40}
    end
  end

  describe "#to_rgb" do
    it "should create a new Color::RGB instance at an accurate HSV value" do
      subject.to_rgb.to_a.should == [255, 0, 0, 40]
    end
  end
end
