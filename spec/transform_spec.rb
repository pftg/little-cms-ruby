require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

def get_path_to file_name
  File.join(File.dirname(__FILE__), file_name)
end

describe 'LCMS::Transform' do
  subject { LCMS::Transform.new(get_path_to("USWebCoatedSWOP.icc"), get_path_to("AdobeRGB1998.icc")) }
  describe "convert" do
    it "should accept CMYK values" do
      rgb = subject.convert 35, 0, 0, 0
      rgb.should_not be_nil
      puts "Inspect convert result"
      puts rgb
    end
  end
end
