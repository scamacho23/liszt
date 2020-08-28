class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.0.18.tar.gz"
  sha256 "35ced0121ff589b41c0aa5278174047e23e41a57ad366dca2f19f4c331cf9c17"
  license "GNU GPL v3"
  version "1.0.19"

  bottle do
    sha256 "4053e304e58e0306bbcda36aa0475676b797d8fafbcb811dab79db3e763e3fc8" => :catalina  
  end

  def install
    bin.install "lst"
  end

end
