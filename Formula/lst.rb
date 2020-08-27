class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.0.18.tar.gz"
  license "GNU GPL v3"
  version "1.0.19"

  bottle do
    sha256 "175d8e525fbcbb59ca1953b402fdcf3714b5d1f8484ed80876b3f4f2377762e0" => :catalina  
end

  def install
    bin.install "lst"
  end

end
