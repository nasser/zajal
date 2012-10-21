require_relative '../spec_helper'
require_relative '../../lib/extensions/object'

describe Object do
  describe "#blank?" do
    it "returns true when object is nil" do
      nil.blank? == true
    end
    it "returns true when object is an empty array" do
      [].blank? == true
    end
    it "returns true when object is an empty string" do
      "".blank? == true
    end
    it "returns false when object is 0" do
      0.blank? == false
    end
    it "returns false when object is a non-empty string" do
      "frothy".blank? == false
    end
    it "returns false when object is a non-empty array" do
      [4, 8, 15, 16, 23, 42].blank? == false
    end
  end
  
  describe "#present?" do
    it "returns false when object is nil" do
      nil.present? == false
    end
    it "returns false when object is an empty array" do
      [].present? == false
    end
    it "returns false when object is an empty string" do
      "".present? == false
    end
    it "returns true when object is 0" do
      0.present? == true
    end
    it "returns true when object is a non-empty string" do
      "frothy".present? == true
    end
    it "returns true when object is a non-empty array" do
      [4, 8, 15, 16, 23, 42].present? == true
    end
  end
end
