require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

describe 'LCMS::Transform' do
  subject { LCMS::Transform.new("USWebCoatedSWOP.icc", "AdobeRGB1998.icc") }
  describe "convert" do
    it "should accept CMYK values" do
      rgb = subject.convert 35, 0, 0, 0
      rgb.should_not be_nil
      puts "Inspect convert result"
      puts  rgb
    end
  end
end
